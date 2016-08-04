#include <avr/io.h>
#include "timer.h"

#define MS_PER_SEC 1000
#define CLOCK_DIV 1024
/* Initialise timer.  */
void timer_init (void)
{
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    TCNT1 = 0;
}


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds)
{
   
    /* TODO: Calculate the timer/counter value needed 
       for the given number of milliseconds. */
	uint16_t ticks = 0;
    ticks = milliseconds * (F_CPU/MS_PER_SEC/CLOCK_DIV);
    
    /* TODO: Wait for the timer/couter to reach the 
       value calculated above.  */
    TCNT1 = 0;
    while(TCNT1 < ticks){
		continue;
	}
}
