#include "ti_msp_dl_config.h"
#include "board.h"

void LED_BEEP_On(void)
{
    DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_PIN);
}

void LED_BEEP_Off(void)
{
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_PIN);
}

uint8_t LED_BEEP_Toggle(void)
{
    LED_BEEP_On();
    return 1;
}
