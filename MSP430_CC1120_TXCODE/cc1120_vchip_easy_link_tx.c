/*****************************************************************************/
//  Filename:        cc1120_vchip_easy_link_tx.c
//
//
//  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/****************************************************************************/


/*****************************************************************************
* INCLUDES
*/
#include "msp430.h"
#include "hal_board.h"
#include "cc112x_spi.h"
#include "hal_int_rf_msp_exp430g2.h"
#include "cc1120_vchip_easy_link_reg_config.h"
#include "stdlib.h"
/******************************************************************************
 * CONSTANTS
 */ 

/******************************************************************************
* DEFINES
*/
#define ISR_ACTION_REQUIRED 1
#define ISR_IDLE            0
#define RX_FIFO_ERROR       0x11
//#define PKTLEN              30
/******************************************************************************
* LOCAL VARIABLES
*/
static uint8  packetSemaphore;
//static uint32 packetCounter;

static uint8 pktlen = 0;
static uint8 RX_PC_FLAG = 0;
static uint8 TX_FALG = 0;
static uint8 RX_SL_FLAG = 0;
static uint8 txBuffer[200] = {0};
/******************************************************************************
* STATIC FUNCTIONS
*/
static void registerConfig(void);
static void runTX_RX(void);
static void createPacket(uint8 txBuffer[]);
static void radioRxTxISR(void);
static void manualCalibration(void);
static void serialInit(void);
/******************************************************************************
 * @fn          main
 *
 * @brief       Runs the main routine
 *                
 * @param       none
 *
 * @return      none
 */
void main(void)
{
  //init MCU
  halInitMCU();
  //init LEDs
  halLedInit();
  //init button
  //halButtonInit();
  //halButtonInterruptEnable();
  // init spi
  exp430RfSpiInit();
  // write radio registers
  registerConfig();
  serialInit();
  // run either TX or RX dependent of build define  
  runTX_RX();
 
}
/******************************************************************************
 * @fn          runTX_RX
 *
 * @brief       sends one packet on button push. Updates packet counter and
 *              display for each packet sent.
 *                
 * @param       none
 *
 * @return      none
 */
static void runTX_RX(void)
{
  uint8 marcStatus;
  P2SEL &= ~0x40; // P2SEL bit 6 (GDO0) set to one as default. Set to zero (I/O)
  // connect ISR function to GPIO0, interrupt on falling edge
  trxIsrConnect(GPIO_0, FALLING_EDGE, &radioRxTxISR);

  // enable interrupt from GPIO_0
  trxEnableInt(GPIO_0);

  // Calibrate radio according to errata
  manualCalibration();

  while(TRUE)
  {
	  if(TX_FALG == 1)//send data to slave module
	  {
		  TX_FALG = 0;

		  trxSpiCmdStrobe(CC112X_SIDLE);

		  //trxIsrConnect(GPIO_0, FALLING_EDGE, &radioRxTxISR);
		  createPacket(txBuffer);
		  // write packet to tx fifo
		  cc112xSpiWriteTxFifo(txBuffer,pktlen+1);
	      // strobe TX to send packet
	      trxSpiCmdStrobe(CC112X_STX);
	      // wait for interrupt that packet has been sent.
	      // (Assumes the GPIO connected to the radioRxTxISR function is set
	      // to GPIOx_CFG = 0x06

	      while(!packetSemaphore);
	      // clear semaphore flag
	      packetSemaphore = ISR_IDLE;

	      halLedToggle(LED1);
	      //__delay_cycles(250000);
	      //halLedToggle(LED1);
	      RX_SL_FLAG = 1 ;  //set revieve form slave module flag
	      trxSpiCmdStrobe(CC112X_SRX);

	      IE2 |= UCA0RXIE;                          // Enable USCI_A0 UART RX interrupt
	  }

	  if(RX_SL_FLAG==1&&packetSemaphore!=ISR_IDLE) //have recieved data from slave module
	  {
		RX_SL_FLAG = 0;
  		// Read number of bytes in rx fifo
  		cc112xSpiReadReg(CC112X_NUM_RXBYTES, &pktlen, 1);

  		// Check that we have bytes in fifo
  		if(pktlen != 0){

			// Read marcstate to check for RX FIFO error
			cc112xSpiReadReg(CC112X_MARCSTATE, &marcStatus, 1);

			// Mask out marcstate bits and check if we have a RX FIFO error
			if((marcStatus & 0x1F) == RX_FIFO_ERROR){
				// Flush RX Fifo
				trxSpiCmdStrobe(CC112X_SFRX);
			}else{
				// Read n bytes from rx fifo
				cc112xSpiReadRxFifo(txBuffer, pktlen);

				if(txBuffer[pktlen-1] & 0x80){
					uint8 i = 0 ;
					for(i=0;i<pktlen;i++)
					{
						IFG2 &= ~UCA0TXIFG;
						UCA0TXBUF = txBuffer[i];;
						while(!(IFG2 & UCA0TXIFG));
						IFG2 &= ~UCA0TXIFG;
					}
				}
				halLedToggle(LED1);
			}
  		}
  	    // Reset packet semaphore
  	    packetSemaphore = ISR_IDLE;
  	    pktlen = 0;

	  }
  }
}
static void serialInit(void)
{
	P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 8;                              // 1MHz 115200
	UCA0BR1 = 0;                              // 1MHz 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

/*******************************************************************************
* @fn          radioRxTxISR
*
* @brief       ISR for packet handling in RX. Sets packet semaphore, puts radio
*              in idle state and clears isr flag.
*
* @param       none
*
* @return      none
*/
static void radioRxTxISR(void) {

  // set packet semaphore
  packetSemaphore = ISR_ACTION_REQUIRED;
  // clear isr flag
  trxClearIntFlag(GPIO_0);
}
/*******************************************************************************
* @fn          registerConfig
*
* @brief       Write register settings as given by SmartRF Studio
*
* @param       none
*
* @return      none
*/
static void registerConfig(void) {
  uint8 writeByte;
  
  // reset radio
  trxSpiCmdStrobe(CC112X_SRES);
  // write registers to radio
  uint16 i = 0;
  for(i = 0; i < (sizeof  preferredSettings/sizeof(registerSetting_t)); i++) {
    writeByte =  preferredSettings[i].data;
    cc112xSpiWriteReg( preferredSettings[i].addr, &writeByte, 1);
  }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  if(RX_PC_FLAG == 1 && UCA0RXBUF != 0xFF)
  {
	  pktlen++;
	  txBuffer[pktlen-1]=UCA0RXBUF;
  }
  if (UCA0RXBUF == 0xFF) //data flag from PC
  {
	  if(RX_PC_FLAG == 0)//begin revieve data from PC
	  {
		  RX_PC_FLAG = 1;
		  pktlen = 0 ;

	  }else // stop revieve
	  {
		  RX_PC_FLAG = 0;

		  if (pktlen !=0) //Do recieve data from PC
		  {
			  TX_FALG =1; //  send data to slave module
			  RX_SL_FLAG = 0;
			  IE2 &= ~UCA0RXIE; //close UCA0RX interrupt
		  }
		  else // recieve nothing
		  {
			  RX_PC_FLAG = 1; //regard the data flag as begining
		  }
	  }
  }
}

/******************************************************************************
 * @fn          createPacket
 *
 * @brief       This function is called before a packet is transmitted. It fills
 *              the txBuffer with a packet consisting of a length byte, two
 *              bytes packet counter and n random bytes.
 *
 *              The packet format is as follows:
 *              |--------------------------------------------------------------|
 *              |           |           |           |         |       |        |
 *              | pktLength | pktCount1 | pktCount0 | rndData |.......| rndData|
 *              |           |           |           |         |       |        |
 *              |--------------------------------------------------------------|
 *               txBuffer[0] txBuffer[1] txBuffer[2]  ......... txBuffer[PKTLEN]
 *                
 * @param       pointer to start of txBuffer
 *
 * @return      none
 */
static void createPacket(uint8 txBuffer[])
{
  uint8 i =3;
  for (i=pktlen;i>0;i--)
  {
	  txBuffer[i]=txBuffer[i-1];
  }
  txBuffer[0] = pktlen;
  /*//txBuffer[0] = PKTLEN;                     // Length byte
  txBuffer[1] = (uint8) packetCounter >> 8; // MSB of packetCounter
  txBuffer[2] = (uint8) packetCounter;      // LSB of packetCounter
  uint8 i =3;
  // fill rest of buffer with random bytes
  for(i =3; i< (PKTLEN+1); i++)
  {
    txBuffer[i] = i;//(uint8)rand();
  }*/
}
/******************************************************************************
 * @fn          manualCalibration
 *
 * @brief       calibrates radio according to CC112x errata
 *                
 * @param       none
 *
 * @return      none
 */
#define VCDAC_START_OFFSET 2
#define FS_VCO2_INDEX 0
#define FS_VCO4_INDEX 1
#define FS_CHP_INDEX 2
static void manualCalibration(void){
  
    uint8 original_fs_cal2;
    uint8 calResults_for_vcdac_start_high[3];
    uint8 calResults_for_vcdac_start_mid[3];
    uint8 marcstate;
    uint8 writeByte;
    
    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    
    // 2) Start with high VCDAC (original VCDAC_START + 2):
    cc112xSpiReadReg(CC112X_FS_CAL2, &original_fs_cal2, 1);
    writeByte = original_fs_cal2 + VCDAC_START_OFFSET;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    
    // 3) Calibrate and wait for calibration to be done (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);
    
    do 
    {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);
    
    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with high VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_high[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_high[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_high[FS_CHP_INDEX], 1);
    
    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    writeByte = 0x00;
    cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    
    // 6) Continue with mid VCDAC (original VCDAC_START):
    writeByte = original_fs_cal2;
    cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    
    // 7) Calibrate and wait for calibration to be done (radio back in IDLE state)
    trxSpiCmdStrobe(CC112X_SCAL);
    
    do 
    {
        cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
    } while (marcstate != 0x41);
    
    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with mid VCDAC_START value
    cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_mid[FS_VCO2_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_mid[FS_VCO4_INDEX], 1);
    cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_mid[FS_CHP_INDEX], 1);
    
    // 9) Write back highest FS_VCO2 and corresponding FS_VCO and FS_CHP result
    if (calResults_for_vcdac_start_high[FS_VCO2_INDEX] > calResults_for_vcdac_start_mid[FS_VCO2_INDEX]) 
    {
        writeByte = calResults_for_vcdac_start_high[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_high[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    }
    else 
    {
        writeByte = calResults_for_vcdac_start_mid[FS_VCO2_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_VCO4_INDEX];
        cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        writeByte = calResults_for_vcdac_start_mid[FS_CHP_INDEX];
        cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
    }
}
