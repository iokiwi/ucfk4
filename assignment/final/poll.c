/** @file   poll.c
    @author K. W. McCall & S. O. Merrick
    @date   9 October
    @brief  Polling events library
*/
#include "poll.h"
#include "tinygl.h"
#include "button.h"
#include "led.h"
#include "ir_uart.h"
#include "timer.h"
#include "pacer.h"
#include "navswitch.h"
#include "../fonts/font3x5_1.h"

void poll_init(void)
{
    uint16_t i = 0;
    navswitch_init();
    button_init();
    
    // UCFK4 event flags
    poll_t.num_flags = 6;
    poll_t.flags[0] = NAVSWITCH_EAST;
    poll_t.flags[1] = NAVSWITCH_WEST;
    poll_t.flags[2] = NAVSWITCH_NORTH;
    poll_t.flags[3] = NAVSWITCH_SOUTH;
    poll_t.flags[4] = NAVSWITCH_PUSH;
    poll_t.flags[5] = BUTTON1;

    // Default check for all possible user events
    for (i; i < poll_t.num_flags; i++){
        poll_t.state[i] = 1;
    }
}

void poll_set_event(int event, bool state)
{
    uint16_t i = 0;
    
    for (i; i < poll_t.num_flags; i++){
        if (poll_t.flags[i] == event){
            poll_t.state[i] = state;
        }
    }
}

bool poll_once(void)
{
    uint16_t i = 0;
    navswitch_update();
    button_update();
    for (i; i < 5; i++){
        if (poll_t.state[i] && navswitch_push_event_p(poll_t.flags[i])){
            return 1;
        }
    }
    if (poll_t.state[5] && button_push_event_p(poll_t.flags[5])){
        return 1;
    }
    return 0;
}

void poll_led(void)
{
    timer_tick_t start;
    timer_tick_t blink;
    bool state=0;
    
    pacer_init(1000);
    timer_init();
    
    start = timer_get();
    while (1){
        pacer_wait();
        blink = timer_get();
        
        if (poll_once()){
            led_set(LED1, 0);
            return;
        }
        
        if (blink > (timer_tick_t)(TIMER_RATE)){
            led_set(LED1, state);
            state = !state;
        }
    }
}

void poll_text(char* message, uint16_t pacer_rate, uint16_t message_rate)
{
    pacer_init(pacer_rate);
    tinygl_init(pacer_rate);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (message_rate);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text (message);
    while (1){
        pacer_wait();
        tinygl_update();
        
        if (poll_once()){
            tinygl_clear();
            break;
        }
    }
}

void poll_block_ir(void)
{
    while (!ir_uart_write_finished_p()){
        pacer_wait();
        tinygl_update();
    }
}

void gobble(void){
    if (ir_uart_read_ready_p()){
        ir_uart_getc();
    }
    pacer_wait();
    
    if (ir_uart_read_ready_p()){
        ir_uart_getc();
    }
}

char poll_ir(char outgoing)
{
    char incoming;
    while (1) {

        if (ir_uart_write_ready_p()){
            ir_uart_putc(outgoing);
            poll_block_ir();
        }

        tinygl_update();
        pacer_wait();
        if (ir_uart_read_ready_p()){
            return ir_uart_getc();
        }
    }
}
