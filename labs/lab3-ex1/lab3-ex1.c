#include "system.h"
#include "button.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"

#define PACER_RATE 250
#define DISPLAY_RATE 250
#define TIMER_RATE 100

static bool run;

void button_task_init(void){
	button_init ();
}

void button_task(void){
	button_update ();
    if (button_push_event_p (BUTTON1))
    {
        run = !run;
    }
}

void display_task_init (void){
	tinygl_init(DISPLAY_RATE);
	tinygl_font_set (&font3x5_1);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
	tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}

void display_task(void){
	tinygl_update();
}

void timer_task_init(void){
	tinygl_text("00");
}

void timer_task (void)
{
    static uint16_t time;
    char str[3];

    if (!run)
    {
        time = 0;
        return;
    }

    str[0] = ((time / 10) % 10) + '0';
    str[1] = (time % 10) + '0';
    str[2] = 0;

    tinygl_text (str);

    time++;
}

int main (void)
{   
    system_init();
    
    /* TODO: Initialise the button driver, tinygl, and the pacer.  */
    pacer_init(PACER_RATE);	
	display_task_init ();
    button_task_init ();
    timer_task_init ();

    while(1)
    {
        pacer_wait();

		/* TODO: Implement the functionality of the tasks in the
        stopwatch1 program.  */
		display_task();
		button_task();
		timer_task();
    }
    return 0;
}
