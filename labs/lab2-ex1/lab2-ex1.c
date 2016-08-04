#include <avr/io.h>
#include "system.h"
#include "led.h"

#define DELAY 0.5
#define F_CLOCK 7812
#define TICKS (DELAY * F_CLOCK)
  
void delay_ms(int delay){
	//timer_wait(TICKS);
	timer_wait(39);
}

void timer_wait(int ticks){
	TCNT1 = 0;
    while(TCNT1 < ticks){
		continue;
	}
}

int main (void)
{
    system_init ();
    led_init ();
    
    /* TODO: Initialise timer/counter1.  */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    TCNT1 = 0;
    
    while (1)
    {
        /* Turn LED on.  */
        led_set (LED1, 1);
       
        /* TODO: wait for 500 milliseconds.  */
        timer_wait(40);
                
        /* Turn LED off.  */
        led_set (LED1, 0);
        
        //timer_wait(3900);
        timer_wait(40);
        /* TODO: wait for 500 milliseconds.  */
    }   
}
