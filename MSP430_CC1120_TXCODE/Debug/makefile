################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/TI/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./cc1120_vchip_easy_link_tx.obj" \
"./cc112x_spi.obj" \
"./hal_board.obj" \
"./hal_digio2.obj" \
"./hal_int.obj" \
"./hal_int_rf_msp_exp430g2.obj" \
"./hal_msp_exp430g2_spi.obj" \
"../lnk_msp430g2553.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MSP430_CC1120_TXCODE.out \

EXE_OUTPUTS__QUOTED += \
"MSP430_CC1120_TXCODE.out" \

BIN_OUTPUTS += \
MSP430_CC1120_TXCODE.hex \

BIN_OUTPUTS__QUOTED += \
"MSP430_CC1120_TXCODE.hex" \


# All Target
all: MSP430_CC1120_TXCODE.out

# Tool invocations
MSP430_CC1120_TXCODE.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"E:/TI/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi --use_hw_mpy=none --advice:power=all -g --define=__MSP430G2553__ --define=MSP_EXP430G2 --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal -z -m"MSP430_CC1120_TXCODE.map" --heap_size=80 --stack_size=80 -i"E:/TI/ccsv6/ccs_base/msp430/include" -i"E:/TI/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/lib" -i"E:/TI/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="MSP430_CC1120_TXCODE_linkInfo.xml" --use_hw_mpy=none --rom_model -o "MSP430_CC1120_TXCODE.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

MSP430_CC1120_TXCODE.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"E:/TI/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/hex430" --memwidth=8 --romwidth=8 -o "MSP430_CC1120_TXCODE.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "cc1120_vchip_easy_link_tx.pp" "cc112x_spi.pp" "hal_board.pp" "hal_digio2.pp" "hal_int.pp" "hal_int_rf_msp_exp430g2.pp" "hal_msp_exp430g2_spi.pp" 
	-$(RM) "cc1120_vchip_easy_link_tx.obj" "cc112x_spi.obj" "hal_board.obj" "hal_digio2.obj" "hal_int.obj" "hal_int_rf_msp_exp430g2.obj" "hal_msp_exp430g2_spi.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

