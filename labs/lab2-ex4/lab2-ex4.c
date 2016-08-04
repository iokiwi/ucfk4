#include "system.h"
#include "pio.h"
#include "pacer.h"

void my_ledmat_init(void);

int main (void)
{
	int state = 0;
    system_init ();
    /* TODO: Initialise the pins of the LED matrix.  */  
    my_ledmat_init();
    /* Set up pacer with a frequency of 50 Hz.  */
    pacer_init (100);

    while (1)
    {
        /* Pace the loop.  */
        pacer_wait ();       
        /* TODO: Drive the LED matrix using the pio functions,
           displaying only three corner LEDs.  */
        if(state == 0){
			pio_output_high(LEDMAT_COL5_PIO);
			pio_output_low(LEDMAT_COL1_PIO);
			pio_output_low(LEDMAT_ROW7_PIO);
			pio_output_low(LEDMAT_ROW1_PIO);
		} else {
			pio_output_high(LEDMAT_COL1_PIO);
			pio_output_high(LEDMAT_ROW7_PIO);
			pio_output_low(LEDMAT_COL5_PIO);
			pio_output_low(LEDMAT_ROW1_PIO);
		
		}
		state ^= 1;
    }
}

void my_ledmat_init(void){
	pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
}

void ledmat_flush(){
	pio_output_high(LEDMAT_COL1_PIO);
	pio_output_high(LEDMAT_COL2_PIO);
	pio_output_high(LEDMAT_COL3_PIO);
	pio_output_high(LEDMAT_COL4_PIO);
	pio_output_high(LEDMAT_COL5_PIO);
	pio_output_high(LEDMAT_ROW1_PIO);
	pio_output_high(LEDMAT_ROW2_PIO);
	pio_output_high(LEDMAT_ROW3_PIO);
	pio_output_high(LEDMAT_ROW4_PIO);
	pio_output_high(LEDMAT_ROW5_PIO);
	pio_output_high(LEDMAT_ROW6_PIO);
	pio_output_high(LEDMAT_ROW7_PIO);
}
