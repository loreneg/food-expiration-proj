################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./Drivers/Lcd/Crystalfontz128x128_ST7735.obj" \
"./Drivers/Lcd/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" \
"./Drivers/init.obj" \
"./Logic/Graphics/addFoodGraphics.obj" \
"./Logic/Graphics/foodListGraphics.obj" \
"./Logic/Graphics/menuGraphics.obj" \
"./Logic/Interrupts/ADCinterrupts.obj" \
"./Logic/Interrupts/RTCinterrupts.obj" \
"./Logic/Interrupts/buttonsInterrupts.obj" \
"./Logic/logic.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/Users/MACHCREATOR/workspace_v12/simplelink_msp432p4_sdk_3_40_01_02/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-l"C:/Users/MACHCREATOR/workspace_v12/simplelink_msp432p4_sdk_3_40_01_02/simplelink_msp432p4_sdk_3_40_01_02/source/ti/grlib/lib/ccs/m4f/grlib.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Drivers/Lcd/subdir_vars.mk
-include Drivers/subdir_vars.mk
-include Logic/Graphics/subdir_vars.mk
-include Logic/Interrupts/subdir_vars.mk
-include Logic/subdir_vars.mk
-include subdir_rules.mk
-include Drivers/Lcd/subdir_rules.mk
-include Drivers/subdir_rules.mk
-include Logic/Graphics/subdir_rules.mk
-include Logic/Interrupts/subdir_rules.mk
-include Logic/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MSP432ProjectFridge.out \

EXE_OUTPUTS__QUOTED += \
"MSP432ProjectFridge.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "MSP432ProjectFridge.out"

# Tool invocations
MSP432ProjectFridge.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"MSP432ProjectFridge.map" --heap_size=1024 --stack_size=512 -i"C:/ti/ccs1250/ccs/ccs_base/arm/include" -i"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="MSP432ProjectFridge_linkInfo.xml" --rom_model -o "MSP432ProjectFridge.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "Drivers\Lcd\Crystalfontz128x128_ST7735.obj" "Drivers\Lcd\HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" "Drivers\init.obj" "Logic\Graphics\addFoodGraphics.obj" "Logic\Graphics\foodListGraphics.obj" "Logic\Graphics\menuGraphics.obj" "Logic\Interrupts\ADCinterrupts.obj" "Logic\Interrupts\RTCinterrupts.obj" "Logic\Interrupts\buttonsInterrupts.obj" "Logic\logic.obj" 
	-$(RM) "main.d" "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "Drivers\Lcd\Crystalfontz128x128_ST7735.d" "Drivers\Lcd\HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" "Drivers\init.d" "Logic\Graphics\addFoodGraphics.d" "Logic\Graphics\foodListGraphics.d" "Logic\Graphics\menuGraphics.d" "Logic\Interrupts\ADCinterrupts.d" "Logic\Interrupts\RTCinterrupts.d" "Logic\Interrupts\buttonsInterrupts.d" "Logic\logic.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

