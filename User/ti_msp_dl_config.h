/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for MotorBPWM */
#define MotorBPWM_INST                                                     TIMG7
#define MotorBPWM_INST_IRQHandler                               TIMG7_IRQHandler
#define MotorBPWM_INST_INT_IRQN                                 (TIMG7_INT_IRQn)
#define MotorBPWM_INST_CLK_FREQ                                          8000000
/* GPIO defines for channel 0 */
#define GPIO_MotorBPWM_C0_PORT                                             GPIOA
#define GPIO_MotorBPWM_C0_PIN                                     DL_GPIO_PIN_28
#define GPIO_MotorBPWM_C0_IOMUX                                   (IOMUX_PINCM3)
#define GPIO_MotorBPWM_C0_IOMUX_FUNC                  IOMUX_PINCM3_PF_TIMG7_CCP0
#define GPIO_MotorBPWM_C0_IDX                                DL_TIMER_CC_0_INDEX

/* Defines for MotorAPWM */
#define MotorAPWM_INST                                                    TIMG12
#define MotorAPWM_INST_IRQHandler                              TIMG12_IRQHandler
#define MotorAPWM_INST_INT_IRQN                                (TIMG12_INT_IRQn)
#define MotorAPWM_INST_CLK_FREQ                                          8000000
/* GPIO defines for channel 0 */
#define GPIO_MotorAPWM_C0_PORT                                             GPIOB
#define GPIO_MotorAPWM_C0_PIN                                     DL_GPIO_PIN_20
#define GPIO_MotorAPWM_C0_IOMUX                                  (IOMUX_PINCM48)
#define GPIO_MotorAPWM_C0_IOMUX_FUNC                IOMUX_PINCM48_PF_TIMG12_CCP0
#define GPIO_MotorAPWM_C0_IDX                                DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (12499U)
/* Defines for TIMER_PID */
#define TIMER_PID_INST                                                   (TIMA0)
#define TIMER_PID_INST_IRQHandler                               TIMA0_IRQHandler
#define TIMER_PID_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define TIMER_PID_INST_LOAD_VALUE                                        (6249U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMA1)
#define TIMER_1_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                          (6249U)




/* Defines for I2C_MPU6050 */
#define I2C_MPU6050_INST                                                    I2C1
#define I2C_MPU6050_INST_IRQHandler                              I2C1_IRQHandler
#define I2C_MPU6050_INST_INT_IRQN                                  I2C1_INT_IRQn
#define I2C_MPU6050_BUS_SPEED_HZ                                          100000
#define GPIO_I2C_MPU6050_SDA_PORT                                          GPIOB
#define GPIO_I2C_MPU6050_SDA_PIN                                   DL_GPIO_PIN_3
#define GPIO_I2C_MPU6050_IOMUX_SDA                               (IOMUX_PINCM16)
#define GPIO_I2C_MPU6050_IOMUX_SDA_FUNC                IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_MPU6050_SCL_PORT                                          GPIOB
#define GPIO_I2C_MPU6050_SCL_PIN                                   DL_GPIO_PIN_2
#define GPIO_I2C_MPU6050_IOMUX_SCL                               (IOMUX_PINCM15)
#define GPIO_I2C_MPU6050_IOMUX_SCL_FUNC                IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOA)

/* Defines for LED: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_LED_LED_PIN                                        (DL_GPIO_PIN_14)
#define GPIO_LED_LED_IOMUX                                       (IOMUX_PINCM36)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOA)

/* Defines for PIN_SCL: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_OLED_PIN_SCL_PIN                                   (DL_GPIO_PIN_12)
#define GPIO_OLED_PIN_SCL_IOMUX                                  (IOMUX_PINCM34)
/* Defines for PIN_SDA: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_OLED_PIN_SDA_PIN                                   (DL_GPIO_PIN_13)
#define GPIO_OLED_PIN_SDA_IOMUX                                  (IOMUX_PINCM35)
/* Port definition for Pin Group GPIO_Trace */
#define GPIO_Trace_PORT                                                  (GPIOA)

/* Defines for TL2: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_Trace_TL2_PIN                                      (DL_GPIO_PIN_22)
#define GPIO_Trace_TL2_IOMUX                                     (IOMUX_PINCM47)
/* Defines for TL1: GPIOA.23 with pinCMx 53 on package pin 24 */
#define GPIO_Trace_TL1_PIN                                      (DL_GPIO_PIN_23)
#define GPIO_Trace_TL1_IOMUX                                     (IOMUX_PINCM53)
/* Defines for TM: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_Trace_TM_PIN                                       (DL_GPIO_PIN_24)
#define GPIO_Trace_TM_IOMUX                                      (IOMUX_PINCM54)
/* Defines for TR1: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_Trace_TR1_PIN                                      (DL_GPIO_PIN_25)
#define GPIO_Trace_TR1_IOMUX                                     (IOMUX_PINCM55)
/* Defines for TR2: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_Trace_TR2_PIN                                      (DL_GPIO_PIN_26)
#define GPIO_Trace_TR2_IOMUX                                     (IOMUX_PINCM59)
/* Defines for TL3: GPIOA.21 with pinCMx 46 on package pin 17 */
#define GPIO_Trace_TL3_PIN                                      (DL_GPIO_PIN_21)
#define GPIO_Trace_TL3_IOMUX                                     (IOMUX_PINCM46)
/* Defines for TR3: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_Trace_TR3_PIN                                      (DL_GPIO_PIN_27)
#define GPIO_Trace_TR3_IOMUX                                     (IOMUX_PINCM60)
/* Port definition for Pin Group GPIO */
#define GPIO_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_SCL_PIN                                             (DL_GPIO_PIN_0)
#define GPIO_SCL_IOMUX                                            (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_SDA_PIN                                             (DL_GPIO_PIN_1)
#define GPIO_SDA_IOMUX                                            (IOMUX_PINCM2)
/* Port definition for Pin Group GPIO_Motor */
#define GPIO_Motor_PORT                                                  (GPIOA)

/* Defines for BIN2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_Motor_BIN2_PIN                                     (DL_GPIO_PIN_31)
#define GPIO_Motor_BIN2_IOMUX                                     (IOMUX_PINCM6)
/* Defines for BIN1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_Motor_BIN1_PIN                                     (DL_GPIO_PIN_17)
#define GPIO_Motor_BIN1_IOMUX                                    (IOMUX_PINCM39)
/* Defines for AIN1: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_Motor_AIN1_PIN                                     (DL_GPIO_PIN_16)
#define GPIO_Motor_AIN1_IOMUX                                    (IOMUX_PINCM38)
/* Defines for AIN2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_Motor_AIN2_PIN                                     (DL_GPIO_PIN_15)
#define GPIO_Motor_AIN2_IOMUX                                    (IOMUX_PINCM37)
/* Defines for KEY1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define GPIO_KEY_KEY1_PORT                                               (GPIOA)
#define GPIO_KEY_KEY1_PIN                                        (DL_GPIO_PIN_7)
#define GPIO_KEY_KEY1_IOMUX                                      (IOMUX_PINCM14)
/* Defines for KEY2: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_KEY_KEY2_PORT                                               (GPIOB)
#define GPIO_KEY_KEY2_PIN                                       (DL_GPIO_PIN_18)
#define GPIO_KEY_KEY2_IOMUX                                      (IOMUX_PINCM44)
/* Defines for KEY3: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_KEY_KEY3_PORT                                               (GPIOB)
#define GPIO_KEY_KEY3_PIN                                       (DL_GPIO_PIN_19)
#define GPIO_KEY_KEY3_IOMUX                                      (IOMUX_PINCM45)
/* Port definition for Pin Group GPIO_Encoder */
#define GPIO_Encoder_PORT                                                (GPIOA)

/* Defines for MotorB: GPIOA.8 with pinCMx 19 on package pin 54 */
// pins affected by this interrupt request:["MotorB","MotorA"]
#define GPIO_Encoder_INT_IRQN                                   (GPIOA_INT_IRQn)
#define GPIO_Encoder_INT_IIDX                   (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_Encoder_MotorB_IIDX                             (DL_GPIO_IIDX_DIO8)
#define GPIO_Encoder_MotorB_PIN                                  (DL_GPIO_PIN_8)
#define GPIO_Encoder_MotorB_IOMUX                                (IOMUX_PINCM19)
/* Defines for MotorA: GPIOA.9 with pinCMx 20 on package pin 55 */
#define GPIO_Encoder_MotorA_IIDX                             (DL_GPIO_IIDX_DIO9)
#define GPIO_Encoder_MotorA_PIN                                  (DL_GPIO_PIN_9)
#define GPIO_Encoder_MotorA_IOMUX                                (IOMUX_PINCM20)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_MotorBPWM_init(void);
void SYSCFG_DL_MotorAPWM_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_PID_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_I2C_MPU6050_init(void);
void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
