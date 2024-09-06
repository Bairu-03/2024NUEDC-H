/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gMotorBPWMBackup;
DL_TimerA_backupConfig gTIMER_PIDBackup;
DL_TimerA_backupConfig gTIMER_1Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_MotorBPWM_init();
    SYSCFG_DL_MotorAPWM_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_TIMER_PID_init();
    SYSCFG_DL_TIMER_1_init();
    SYSCFG_DL_I2C_MPU6050_init();
    SYSCFG_DL_UART_0_init();
    /* Ensure backup structures have no valid state */
	gMotorBPWMBackup.backupRdy 	= false;
	gTIMER_PIDBackup.backupRdy 	= false;
	gTIMER_1Backup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(MotorBPWM_INST, &gMotorBPWMBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_PID_INST, &gTIMER_PIDBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_1_INST, &gTIMER_1Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(MotorBPWM_INST, &gMotorBPWMBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_PID_INST, &gTIMER_PIDBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_1_INST, &gTIMER_1Backup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(MotorBPWM_INST);
    DL_TimerG_reset(MotorAPWM_INST);
    DL_TimerG_reset(TIMER_0_INST);
    DL_TimerA_reset(TIMER_PID_INST);
    DL_TimerA_reset(TIMER_1_INST);
    DL_I2C_reset(I2C_MPU6050_INST);
    DL_UART_Main_reset(UART_0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(MotorBPWM_INST);
    DL_TimerG_enablePower(MotorAPWM_INST);
    DL_TimerG_enablePower(TIMER_0_INST);
    DL_TimerA_enablePower(TIMER_PID_INST);
    DL_TimerA_enablePower(TIMER_1_INST);
    DL_I2C_enablePower(I2C_MPU6050_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_MotorBPWM_C0_IOMUX,GPIO_MotorBPWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_MotorBPWM_C0_PORT, GPIO_MotorBPWM_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_MotorAPWM_C0_IOMUX,GPIO_MotorAPWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_MotorAPWM_C0_PORT, GPIO_MotorAPWM_C0_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_MPU6050_IOMUX_SDA,
        GPIO_I2C_MPU6050_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_MPU6050_IOMUX_SCL,
        GPIO_I2C_MPU6050_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_MPU6050_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_MPU6050_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutputFeatures(GPIO_LED_LED_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_OLED_PIN_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_PIN_SDA_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TL2_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TL1_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TM_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TR1_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TR2_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TL3_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_Trace_TR3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SDA_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_BIN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_Motor_AIN2_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_KEY1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_KEY2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_KEY3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Encoder_MotorB_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_Encoder_MotorA_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_clearPins(GPIOA, GPIO_LED_LED_PIN |
		GPIO_OLED_PIN_SCL_PIN |
		GPIO_OLED_PIN_SDA_PIN |
		GPIO_Motor_BIN2_PIN |
		GPIO_Motor_BIN1_PIN |
		GPIO_Motor_AIN1_PIN |
		GPIO_Motor_AIN2_PIN);
    DL_GPIO_setPins(GPIOA, GPIO_SCL_PIN |
		GPIO_SDA_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_LED_LED_PIN |
		GPIO_OLED_PIN_SCL_PIN |
		GPIO_OLED_PIN_SDA_PIN |
		GPIO_SCL_PIN |
		GPIO_SDA_PIN |
		GPIO_Motor_BIN2_PIN |
		GPIO_Motor_BIN1_PIN |
		GPIO_Motor_AIN1_PIN |
		GPIO_Motor_AIN2_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_8_EDGE_RISE |
		DL_GPIO_PIN_9_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_Encoder_MotorB_PIN |
		GPIO_Encoder_MotorA_PIN);
    DL_GPIO_enableInterrupt(GPIOA, GPIO_Encoder_MotorB_PIN |
		GPIO_Encoder_MotorA_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_enableMFCLK();

}


/*
 * Timer clock configuration to be sourced by  / 4 (8000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   8000000 Hz = 8000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gMotorBPWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gMotorBPWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_MotorBPWM_init(void) {

    DL_TimerG_setClockConfig(
        MotorBPWM_INST, (DL_TimerG_ClockConfig *) &gMotorBPWMClockConfig);

    DL_TimerG_initPWMMode(
        MotorBPWM_INST, (DL_TimerG_PWMConfig *) &gMotorBPWMConfig);

    DL_TimerG_setCaptureCompareOutCtl(MotorBPWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(MotorBPWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(MotorBPWM_INST, 1000, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(MotorBPWM_INST);


    
    DL_TimerG_setCCPDirection(MotorBPWM_INST , DL_TIMER_CC0_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 4 (8000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   8000000 Hz = 8000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gMotorAPWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gMotorAPWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_MotorAPWM_init(void) {

    DL_TimerG_setClockConfig(
        MotorAPWM_INST, (DL_TimerG_ClockConfig *) &gMotorAPWMClockConfig);

    DL_TimerG_initPWMMode(
        MotorAPWM_INST, (DL_TimerG_PWMConfig *) &gMotorAPWMConfig);

    DL_TimerG_setCaptureCompareOutCtl(MotorAPWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(MotorAPWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(MotorAPWM_INST, 1000, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(MotorAPWM_INST);


    
    DL_TimerG_setCCPDirection(MotorAPWM_INST , DL_TIMER_CC0_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 32000000 Hz / (1 * (255 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (100 ms * 125000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_0_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 32000000 Hz / (1 * (255 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_PIDClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_PID_INST_LOAD_VALUE = (50 ms * 125000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_PIDTimerConfig = {
    .period     = TIMER_PID_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_PID_init(void) {

    DL_TimerA_setClockConfig(TIMER_PID_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_PIDClockConfig);

    DL_TimerA_initTimerMode(TIMER_PID_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_PIDTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_PID_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_PID_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   125000 Hz = 32000000 Hz / (1 * (255 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_1ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_1_INST_LOAD_VALUE = (50 ms * 125000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_1TimerConfig = {
    .period     = TIMER_1_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_1_init(void) {

    DL_TimerA_setClockConfig(TIMER_1_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_1ClockConfig);

    DL_TimerA_initTimerMode(TIMER_1_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_1TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_1_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_1_INST);





}


static const DL_I2C_ClockConfig gI2C_MPU6050ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_MPU6050_init(void) {

    DL_I2C_setClockConfig(I2C_MPU6050_INST,
        (DL_I2C_ClockConfig *) &gI2C_MPU6050ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_MPU6050_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_MPU6050_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_MPU6050_INST);
    /* Set frequency to 100000 Hz*/
    DL_I2C_setTimerPeriod(I2C_MPU6050_INST, 31);
    DL_I2C_setControllerTXFIFOThreshold(I2C_MPU6050_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_MPU6050_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_MPU6050_INST);

    /* Configure Interrupts */
    DL_I2C_enableInterrupt(I2C_MPU6050_INST,
                           DL_I2C_INTERRUPT_CONTROLLER_ARBITRATION_LOST |
                           DL_I2C_INTERRUPT_CONTROLLER_NACK |
                           DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_TRIGGER |
                           DL_I2C_INTERRUPT_CONTROLLER_RX_DONE |
                           DL_I2C_INTERRUPT_CONTROLLER_TX_DONE);


    /* Enable module */
    DL_I2C_enableController(I2C_MPU6050_INST);


}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_9600_BAUD, UART_0_FBRD_32_MHZ_9600_BAUD);



    DL_UART_Main_enable(UART_0_INST);
}

