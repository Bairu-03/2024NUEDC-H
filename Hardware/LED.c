#include "ti_msp_dl_config.h"
#include "board.h"


/**
 * @brief  打开LED和蜂鸣器。
 * @param  无
 * @retval 无
 */
void LED_BEEP_On(void)
{
    DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_PIN);
}

/**
 * @brief  关闭LED和蜂鸣器。
 * @param  无
 * @retval 无
 */
void LED_BEEP_Off(void)
{
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_PIN);
}
