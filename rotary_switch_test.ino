#include <esp8266channel3lib.h>

int PIN_SWITCH_1 = 5;
int PIN_SWITCH_2 = 6;
int PIN_SWITCH_3 = 7;
int PIN_SWITCH_4 = 8;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
   // video_broadcast_clear_frame();
    

if (digitalRead(PIN_SWITCH_1) == LOW)
     {
         CNFGColor( C3_COL_RED );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_2) == LOW)
     {
         CNFGColor( C3_COL_GREEN_2 );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_3) == LOW)
     {
         CNFGColor( C3_COL_LIGHT_YELLOW );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_4) == LOW)
     {
         CNFGColor( C3_COL_DARK_BLUE );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else
     {
         // Keep default value
     }
    
    

}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
     pinMode(PIN_SWITCH_1, INPUT_PULLUP); 
     pinMode(PIN_SWITCH_2, INPUT_PULLUP); 
     pinMode(PIN_SWITCH_3, INPUT_PULLUP); 
     pinMode(PIN_SWITCH_4, INPUT_PULLUP); 


 }




void loop() {

}
