/** @file   game.c
    @author K. W. McCall & S. O. Merrick
    @date   9 October
    @brief  Main Game Library
    
    An implementation of 'Rock, Paper, Scissors, Lizzard, Spock', 
    inspired by 'The Big Bang Theory'. Credit to M. P. Hayes, UCECE
    for the provided drivers and libraries used in this implementaion
    and a big thanks to  A. Stockdill for his contribution to the
    bitching graphics. Live long and prosper.
*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "task.h"
#include "led.h"
#include "ledmat.h"
#include "button.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "poll.h"

// Is X inferior to Y?
#define INFERIOR(X, Y) ((Y).inferior1 == (X).value || (Y).inferior2 == (X).value)

// Does A win? 1 - yes, 0 - draw, -1 - loss
#define CMP(A, B) (INFERIOR((A), (B)) ? -1 : INFERIOR((B), (A)))

// Wraps a value to be in the range 0 to 4
#define WRAP5(I) ((I) < 0 ? 4 : ((I) > 4 ? 0 : (I)))

// Bitmap Definitions
#define ROCK_BITMAP {0x18, 0x3C, 0x3E, 0x7F, 0x3E}
#define PAPER_BITMAP {0x7E, 0x45, 0x47, 0x41, 0x7F}
#define SCISSORS_BITMAP {0x67, 0x35, 0x1A, 0x35, 0x67}
#define LIZARD_BITMAP {0x36, 0x5D, 0x7F, 0x41, 0x3E}
#define SPOCK_BITMAP {0x3B, 0x46, 0x54, 0x46, 0x3B}

// Program configurations
#define PACER_RATE 500
#define MESSAGE_RATE 40
enum {ROCK='A', PAPER='B', SCISSORS='C', LIZARD='D', SPOCK='E'};

// Internal structure definition of character
typedef struct _character Character;
struct _character {
    char* name;
    char value;
    char inferior1;
    char inferior2;
    uint8_t bitmap[5];
};
