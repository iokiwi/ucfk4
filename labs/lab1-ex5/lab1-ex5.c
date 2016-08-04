#include "pio.h"
#include "system.h"

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

void flush(){
  int i,j;
  for(i = 0; i < 5; i++){
    pio_output_high(cols[i]);
    for(j = 0; j < 7; j++){
      pio_output_high(rows[j]);
    }
  }
}

void draw(int bitmap[5][7]){
  int i,j;
  for(i = 0; i < 5; i++){
    flush();
    pio_output_low(cols[i]);
    for(j = 0; j < 7; j++){
      if(bitmap[i][j] == 1){
        pio_output_low(rows[j]);
      }
    }
  }
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

int main (void){
  system_init ();
	ledmat_init();
  
  int bitmap1[5][7] = {
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1},
  };
  
  int bitmap2[5][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
  };
  
  int bitmap3[5][7] = {
    {1,1,1,1,1,1,1},
    {0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1},
  };
  
  int bitmap4[5][7] = {
    {1,1,1,1,1,0,0},
    {0,0,1,0,0,1,0},
    {0,0,1,0,0,0,1},
    {0,0,1,0,0,1,0},
    {1,1,1,1,1,0,0},
  };
  
  int bitmap5[5][7] = {
    {1,0,0,1,1,0,0},
    {1,1,0,0,1,1,0},
    {1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {1,1,1,1,0,0,0},
  };
  
  while(1){
    draw(bitmap5);
  }
  
  draw(bitmap1);
  draw(bitmap2);
  draw(bitmap3);
  draw(bitmap4);
  draw(bitmap5);
  
  
  return 0;
}