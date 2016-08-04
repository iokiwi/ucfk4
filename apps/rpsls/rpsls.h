#include "system.h"
#include "navswitch.h"
#include "ledmat.h"
#include "pacer.h"
#include "pio.h"
#include "led.h"
#include "tinygl.h"
#include "pacer.h"
#include <stdlib.h>

#define ROCK_BITMAP {0x18, 0x3C, 0x3E, 0x7F, 0x3E}
#define PAPER_BITMAP {0x7E, 0x45, 0x47, 0x41, 0x7F}
#define SCISSORS_BITMAP {0x67, 0x35, 0x1A, 0x35, 0x67}
#define LIZARD_BITMAP {0x36, 0x5D, 0x7F, 0x41, 0x3E}
#define SPOCK_BITMAP {0x3B, 0x46, 0x54, 0x46, 0x3B}

#define WRAP5(I) ((I) < 0 ? 4 : ((I) > 4 ? 0 : (I)))

typedef struct _character Character;
struct _character {
    char* name;
    char value;
    char inferior1;
    char inferior2;
    uint8_t bitmap[5];
};

enum {ROCK='A', PAPER='B', SCISSORS='C', LIZARD='D', SPOCK='E'};
