/** @file   poll.h
    @author K. W. MCCALL & S. O. MERRICK
    @date   9 October 2013
    @brief  Polling for events module
    
    The polling events module provides the ability to prompt the user
    * for input from an idle state. It allows for led flashing and
    * text scrolling prompts as well as the ability to determine what
    * user events are waited for.
*/
#include "system.h"

typedef uint16_t timeout;

struct {
    uint8_t num_flags;
    bool state[6];
    int flags[6];
} poll_t;

/** Initializes the polling module
 * */
void poll_init(void);

/** Sets whether or not an event is polled
 * @param the event to modify and its new value
 * */
void poll_set_event(int event, bool state);

/** Scrolls text until event occurs
 * @param the message to be scrolls, pacer rate and message rate
 * */
void poll_text(char* message, uint16_t pacer_rate, uint16_t message_rate);

/** Blink the led until an event occurs 
 * */
void poll_led(void);

/** Blocks until ir has finished transmitting
 * */
 void poll_block_ir(void);

/** Send a signal until an ir signal is received
 * @param the outgoing signal character
 * @return the received signal character
 * */
char poll_ir(char outgoing);

/** Check if any event has occured
 * @return whether an event has occured
 * */
bool poll_once(void);

/** Eats the first 2 characters in the buffer, if they exist
 * */
 void gobble(void);
