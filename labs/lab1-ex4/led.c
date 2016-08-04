#include "pio.h"
#include "led.h"

#define LED_PIO PIO_DEFINE(PORT_C, 2)

int state = 0;

void led_toggle (void) {
	if(state == 0){
		led_on();
	} else {
		led_off();
	}
}

/** Turn LED1 on.  */
void led_on (void)
{
	state = 1;
	pio_output_high(LED_PIO);
}

/** Turn LED1 off.  */
void led_off (void)
{
    state = 0;
    pio_output_low(LED_PIO);
}

/** Initialise LED1.  */
void led_init (void)
{
	pio_config_set(LED_PIO, PIO_OUTPUT_LOW);
}
