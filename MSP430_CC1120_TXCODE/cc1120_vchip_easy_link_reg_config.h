/*****************************************************************************/
//  Filename: cc1120_vchip_easy_link_reg_config.h  
//    
//  Description: Template for CC1120 register export from SmartRF Studio 
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
#ifndef CC1120_VCHIP_EASY_LINK_REG_CONFIG_H
#define CC1120_VCHIP_EASY_LINK_REG_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * INCLUDES
 */
#include "cc112x_spi.h"
#include "hal_msp_exp430g2_spi.h"

  
/******************************************************************************
 * FUNCTIONS
 */  
// RX filter BW = 25.000000 
// Address config = No address check 
// Packet length = 255 
// Symbol rate = 1.2 
// PA ramping = true 
// Performance mode = High Performance 
// Carrier frequency = 434.000000 
// Bit rate = 1.2 
// Packet bit length = 0 
// Whitening = false 
// Manchester enable = false 
// Modulation format = 2-FSK 
// Packet length mode = Variable 
// Device address = 0 
// TX power = 15 
// Deviation = 3.997803 
/*
static const registerSetting_t preferredSettings[]= 
{
  {CC112X_IOCFG3,            0xB0}, //未使用
  {CC112X_IOCFG2,            0x06}, //PKT_CRC_OK
  {CC112X_IOCFG1,            0xB0}, //
  {CC112X_IOCFG0,            0x06}, //PKT_SYNC_RXTX
  {CC112X_SYNC_CFG1,         0x0B}, //SYNC_THR

  {CC112X_DCFILT_CFG,        0x1C}, //0x1c}, //ti//0x15},
  {CC112X_PREAMBLE_CFG1,     0x18},//2bytes preamble, 0x55
  {CC112X_IQIC,              0xC6},
  {CC112X_CHAN_BW,           0x08},
  {CC112X_MDMCFG0,           0x05},
  {CC112X_AGC_REF,           0x20},
  {CC112X_AGC_CS_THR,        0x19},
  {CC112X_AGC_CFG1,          0xA9},
  {CC112X_AGC_CFG0,          0xCF},
  {CC112X_FIFO_CFG,          0x00},

  {CC112X_SETTLING_CFG,      0x03},

  {CC112X_FS_CFG,            0x14},
  {CC112X_PKT_CFG0,          0x20},
  {CC112X_PKT_LEN,           0xFF},
  {CC112X_IF_MIX_CFG,        0x00},
  {CC112X_FREQOFF_CFG,       0x22},

  {CC112X_FREQ2,             0x6C},
  {CC112X_FREQ1,             0x80},
  {CC112X_FS_DIG1,           0x00},
  {CC112X_FS_DIG0,           0x5F},
  {CC112X_FS_CAL1,           0x40},
  {CC112X_FS_CAL0,           0x0E},
  {CC112X_FS_DIVTWO,         0x03},
  {CC112X_FS_DSM0,           0x33},
  {CC112X_FS_DVC0,           0x17},
  {CC112X_FS_PFD,            0x50},
  {CC112X_FS_PRE,            0x6E},
  {CC112X_FS_REG_DIV_CML,    0x14},
  {CC112X_FS_SPARE,          0xAC},
  {CC112X_FS_VCO0,           0xB4},
  {CC112X_XOSC5,             0x0E},
  {CC112X_XOSC1,             0x03},
};

*/

/******************************************************************************
 * VARIABLES
 */
// RX filter BW = 100kHz
// Address config = No address check  ??
// Packet length =
// Symbol rate = 50ksps
// PA ramping = true
// Performance mode = Low Power
// Carrier frequency = 434.119995MHz(434.12MHz)
// Bit rate = 50kbps
// Packet bit length =
// Whitening = false
// Manchester enable = false
// Modulation format = 2-GFSK
// Packet length mode =
// Device address = 0
// TX power = 15
// Deviation = 24.963379kHz

static const registerSetting_t preferredSettings[]=
{
  {CC112X_IOCFG3,              0xB0},  //未使用，高阻
  {CC112X_IOCFG2,              0xB0},  //PKT_CRC_OK
  {CC112X_IOCFG1,              0xB0},  //未使用，高阻
  {CC112X_IOCFG0,              0x06},  //PKT_SYNC_RXTX

  {CC112X_SYNC_CFG1,           0x08},  //SYNC_THR
  {CC112X_DEVIATION_M,         0x99}, //deviation
  {CC112X_MODCFG_DEV_E,        0x0D},  //0x0B},  //2-GFSK
  {CC112X_DCFILT_CFG,          0x15},  //0x1c}, //ti//0x15},
  {CC112X_PREAMBLE_CFG1,       0x18},  //2bytes preamble, 0x55

  {CC112X_FREQ_IF_CFG,         0x3A},   //??
  {CC112X_IQIC,                0x00},//0xc6}, //ti//0x00},  ??
  {CC112X_CHAN_BW,             0x02},//0x42}, //0x08}, //ti//0x02},

  {CC112X_MDMCFG0,             0x05},
  {CC112X_SYMBOL_RATE2,        0x99},
  {CC112X_SYMBOL_RATE1,        0x99},
  {CC112X_SYMBOL_RATE0,        0x99}, //0x9A},  //0x99},  //0x9A},
  {CC112X_AGC_REF,             0x3C},  //0x20},  //ti//0x3C},
  {CC112X_AGC_CS_THR,          0xEF},  //0x19},  //ti//0xEF},

  {CC112X_AGC_CFG1,            0xA9},
  {CC112X_AGC_CFG0,            0xC0}, //0xcf},  //ti//0xC0},  ??
  {CC112X_FIFO_CFG,            0x00},  //ti//0x80},  //RX FIFO  auto flush when crc error

  {CC112X_FS_CFG,              0x14},

  {CC112X_PKT_CFG0,            0x20},  //variable package length mode, Packet length configured by the first byte received after sync word.
  {CC112X_PA_CFG0,             0x79},  //0x7B},  //0x79},  //0x7B},
  {CC112X_PKT_LEN,             0xFF},  //in variable length packet mode, this value indicates the maximum allowed length packets.
  {CC112X_IF_MIX_CFG,          0x00},
  {CC112X_TOC_CFG,             0x0A},

  {CC112X_SETTLING_CFG,        0x03},

  {CC112X_FREQ2,             0x6C},
  {CC112X_FREQ1,             0x80},
  {CC112X_FS_DIG1,           0x00},
  {CC112X_FS_DIG0,           0x5F},
  {CC112X_FS_CAL1,           0x40},
  {CC112X_FS_CAL0,           0x0E},
  {CC112X_FS_DIVTWO,         0x03},
  {CC112X_FS_DSM0,           0x33},
  {CC112X_FS_DVC0,           0x17},
  {CC112X_FS_PFD,            0x50},
  {CC112X_FS_PRE,            0x6E},
  {CC112X_FS_REG_DIV_CML,    0x14},
  {CC112X_FS_SPARE,          0xAC},
  {CC112X_FS_VCO0,           0xB4},
  {CC112X_XOSC5,             0x0E},
  {CC112X_XOSC1,             0x03}

		/*
// SMART RF
  {CC112X_IOCFG3,              0xB0},  //未使用，高阻
  {CC112X_IOCFG2,              0x06},  //PKT_CRC_OK
  {CC112X_IOCFG1,              0xB0},  //未使用，高阻
  {CC112X_IOCFG0,              0x06},  //PKT_SYNC_RXTX
  {CC112X_SYNC3,               0x93},  //未使用
  {CC112X_SYNC2,               0x0B},  //未使用
  {CC112X_SYNC1,               0x51},  //同步字
  {CC112X_SYNC0,               0xDE},  //同步字
  {CC112X_SYNC_CFG1,           0x08},  //SYNC_THR
  {CC112X_SYNC_CFG0,           0x17},  //16bits(SYNC1,SYNC0)
  {CC112X_DEVIATION_M,         0x99},
  {CC112X_MODCFG_DEV_E,        0x0D},  //0x0B},  //2-GFSK
  {CC112X_DCFILT_CFG,          0x15},  //0x1c}, //ti//0x15},
  {CC112X_PREAMBLE_CFG1,       0x18},  //2bytes preamble, 0x55
  {CC112X_PREAMBLE_CFG0,       0x2A},
  {CC112X_FREQ_IF_CFG,         0x3A},
  {CC112X_IQIC,                0x00},//0xc6}, //ti//0x00},
  {CC112X_CHAN_BW,             0x02},//0x42}, //0x08}, //ti//0x02},
  {CC112X_MDMCFG1,             0x46}, //0x06}, //ti//0x46},
  {CC112X_MDMCFG0,             0x05},
  {CC112X_SYMBOL_RATE2,        0x99},
  {CC112X_SYMBOL_RATE1,        0x99},
  {CC112X_SYMBOL_RATE0,        0x99}, //0x9A},  //0x99},  //0x9A},
  {CC112X_AGC_REF,             0x3C},  //0x20},  //ti//0x3C},
  {CC112X_AGC_CS_THR,          0xEF},  //0x19},  //ti//0xEF},
  {CC112X_AGC_GAIN_ADJUST,     0x00},
  {CC112X_AGC_CFG3,            0x91},
  {CC112X_AGC_CFG2,            0x20},
  {CC112X_AGC_CFG1,            0xA9},
  {CC112X_AGC_CFG0,            0xC0}, //0xcf},  //ti//0xC0},
  {CC112X_FIFO_CFG,            0x00},  //ti//0x80},  //RX FIFO  auto flush when crc error
  {CC112X_DEV_ADDR,            0x00}, //netID, optional
  {CC112X_SETTLING_CFG,        0x03},
  {CC112X_FS_CFG,              0x14},  //0x12},  //0x14},
  {CC112X_WOR_CFG1,            0x08},
  {CC112X_WOR_CFG0,   		   0X21},
  {CC112X_WOR_EVENT0_MSB,	   0X00},
  {CC112X_WOR_EVENT0_LSB,	   0X00},
  {CC112X_PKT_CFG2,            0x04},  //
  {CC112X_PKT_CFG1,            0x05}, //0x00}, //ti//0x05},  //data whitening disabled, no address check, CRC check, data byte swap disabled, status byte appended.
  {CC112X_PKT_CFG0,            0x20},  //fixed package length, Packet length configured by the first byte received after sync word.
  {CC112X_RFEND_CFG1,		   0X0F},
  {CC112X_RFEND_CFG0,		   0X00},
  {CC112X_PA_CFG2,             0x7F}, //ti//0x74},
  {CC112X_PA_CFG1,             0x56},
  {CC112X_PA_CFG0,             0x79},  //0x7B},  //0x79},  //0x7B},
  {CC112X_PKT_LEN,             0xFF},  //in variable length packet mode, this value indicates the maximum allowed length packets.
  {CC112X_IF_MIX_CFG,          0x00},
  {CC112X_FREQOFF_CFG,         0x20},  //0x22}, //ti//0x20},
  {CC112X_TOC_CFG,             0x0A},
  {CC112X_MARC_SPARE,		   0X00},
  {CC112X_ECG_CFG,			   0X00},
  {CC112X_CFM_DATA_CFG,        0x00}, //ti//0x00},
  {CC112X_EXT_CTRL,			   0X01},
  {CC112X_RCCAL_FINE,		   0X00},
  {CC112X_RCCAL_COARSE,		   0X00},
  {CC112X_RCCAL_OFFSET,  	   0X00},
  {CC112X_FREQOFF1,			   0X00},
  {CC112X_FREQOFF0,			   0X00},
  {CC112X_FREQ2,               0x6C},
  {CC112X_FREQ1,               0x80}, //0x80}, //ti//0x87},  //0x80},  //0x87},
  {CC112X_FREQ0,               0x00},  //0x00},  //0xAE},
  {CC112X_IF_ADC2,			   0X02},
  {CC112X_IF_ADC1,			   0XA6},
  {CC112X_IF_ADC0,			   0X04},
  {CC112X_FS_DIG1,             0x00},
  {CC112X_FS_DIG0,             0x5f}, //ti//0x50},  //0x5F},  //0x50},
  {CC112X_FS_CAL3,             0x00},
  {CC112X_FS_CAL2,             0x20},
  {CC112X_FS_CAL1,             0x40},
  {CC112X_FS_CAL0,             0x0E},
  {CC112X_FS_CHP,              0x28},
  {CC112X_FS_DIVTWO,           0x03},
  {CC112X_FS_DSM1,			   0X00},
  {CC112X_FS_DSM0,             0x33},
  {CC112X_FS_DVC1,			   0XFF},
  {CC112X_FS_DVC0,             0x17},//ti//0x13},
  {CC112X_FS_PFD,              0x50}, //ti//0x50},
  {CC112X_FS_PRE,              0x6E},
  {CC112X_FS_REG_DIV_CML,      0x14},
  {CC112X_FS_SPARE,            0xAC},
  {CC112X_FS_VCO4,             0x14},
  {CC112X_FS_VCO3,             0x00},
  {CC112X_FS_VCO2,             0x00},
  {CC112X_FS_VCO1,             0x00},
  {CC112X_FS_VCO0,             0xB4}, //ti//0xB8},
  {CC112X_GBIAS6,			   0X00},
  {CC112X_GBIAS5,			   0X02},
  {CC112X_GBIAS4,			   0X00},
  {CC112X_GBIAS3,			   0X00},
  {CC112X_GBIAS2,			   0X10},
  {CC112X_GBIAS1,			   0X00},
  {CC112X_GBIAS0,			   0X00},
  {CC112X_IFAMP,			   0X01},
  {CC112X_LNA,				   0X01},
  {CC112X_RXMIX,			   0X01},
  {CC112X_XOSC5,               0x0E},
  {CC112X_XOSC4,               0xA0},
  {CC112X_XOSC3,               0x03},
  {CC112X_XOSC2,               0x04},
  {CC112X_XOSC1,               0x03}, //ti//0x01},
  {CC112X_ANALOG_SPARE,		   0X00},
  {CC112X_PA_CFG3,			   0X00},
  {CC112X_BIST,				   0X00},
  {CC112X_DCFILTOFFSET_I1,     0x00},
  {CC112X_DCFILTOFFSET_I0,     0x00},
  {CC112X_DCFILTOFFSET_Q1,     0x00},
  {CC112X_DCFILTOFFSET_Q0,     0x00},
  {CC112X_IQIE_I1,             0x00},
  {CC112X_IQIE_I0,             0x00},
  {CC112X_IQIE_Q1,             0x00},
  {CC112X_IQIE_Q0,             0x00},
  {CC112X_AGC_GAIN2,           0xD1},
  {CC112X_AGC_GAIN1,           0x00},
  {CC112X_AGC_GAIN0,           0x3F}
*/
};
#ifdef  __cplusplus
}
#endif

#endif
