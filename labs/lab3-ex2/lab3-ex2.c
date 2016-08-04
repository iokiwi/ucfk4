#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 50

int main (void)
{
    system_init();

   	tinygl_init (PACER_RATE);
	tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_font_set (&font3x5_1);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

	;
    /* TODO: Set the message using tinygl_text().  */
    
    tinygl_text("PRESS TO BEGIN\0"); 	//30
    //tinygl_text("RPSLS\0"); 			//15
    //tinygl_text("BEATS\0");			//25
    //tinygl_text("WIN\0");				//25
    //tinygl_text("WINNER\0");			//25
    //tinygl_text("LOSE\0");			//25
    //tinygl_text("LOSER\0");			//25
       
    pacer_init (PACER_RATE);
    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
    return 0;
}
