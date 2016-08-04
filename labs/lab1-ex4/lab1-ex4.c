#include "button.h"
#include "led.h"
#include "system.h"

int main (void)
{
    system_init ();
    led_init ();
    button_init ();

	int prev_state = 0, cur_state = 0;
    
    while (1) {
		cur_state = button_pressed_p();
		if(cur_state)
		{
			if(prev_state != cur_state)
			{
				led_toggle();
			}
		}
		prev_state = cur_state;	
	}
    return 0;
}
