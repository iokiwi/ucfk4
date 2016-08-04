#include "system.h"
#include "pio.h"
#include "pacer.h"

#define ROCK_BITMAP {0x18, 0x3C, 0x3E, 0x7F, 0x3E}
#define PAPER_BITMAP {0x7E, 0x45, 0x47, 0x41, 0x7F}
#define SCISSORS_BITMAP {0x67, 0x35, 0x1A, 0x35, 0x67}
#define LIZARD_BITMAP {0x36, 0x5D, 0x7F, 0x41, 0x3E}
#define SPOCK_BITMAP {0x3B, 0x46, 0x54, 0x46, 0x3B}

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


//Rock
static const uint8_t ROCK[] =
{
   0x18, 0x3C, 0x3E, 0x7F, 0x3E
};

//Paper
static const uint8_t PAPER[] =
{
   0x7E, 0x45, 0x47, 0x41, 0x7F
};

//Scissors
static const uint8_t SCISSORS[] =
{
   0x67, 0x35, 0x1A, 0x35, 0x67
};

//Lizard
static const uint8_t LIZARD[] =
{ 
	0x36, 0x5D, 0x7F, 0x41, 0x3E
};

//Spock
static const uint8_t SPOCK[] =
{ 
	0x3B, 0x46, 0x54, 0x46, 0x3B
};

static void display_column (uint8_t row_pattern, uint8_t current_column)
{
    /* TODO */
    int i = 0;
    //set
    for(i = 0; i < 8;i++){
		if((row_pattern & (1 << i)) == 0){
			pio_output_high(rows[i]);
		} else {
			pio_output_low(rows[i]);
		}
	}
	
	//Set all columns off
	for(i = 0; i < 5; i++){
		pio_output_high(cols[i]);
	}
	pio_output_low(cols[current_column]);
}

void ledmat_init(void){
	int i;
	for(i = 0; i < 5; i++){
		pio_config_set(cols[i],PIO_OUTPUT_HIGH);
	}
	for(i = 0; i < 7; i++){
		pio_config_set(rows[i],PIO_OUTPUT_HIGH);
	}
}

int main (void)
{    
	uint16_t current_column = 0;
	
    system_init ();
    pacer_init (500);
    ledmat_init(); 
    
    while (1) 
	{
		pacer_wait();
        display_column(ROCK[current_column], current_column);
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1)){
            current_column = 0;
        }           
    }
}
