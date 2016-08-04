#include "tetris.h"
#include "button.h"
#include "system.h"
#include "led.h"
#include "ledmat.h"

int toggle(int state){
  return (state == 1) ? 0 : 1;
}

int main(void){
  system_init();
  led_init();
  button_init();
  
  while(1){
    button_update();
    if(button_down_p(BUTTON1)){
      led_set(LED1, ON);
    }
  }
  
  return 0;
}