#include <esp8266channel3lib.h>

int PIN_SWITCH_1 = 5;
int PIN_SWITCH_2 = 6;
int PIN_SWITCH_3 = 7;
int PIN_SWITCH_4 = 8;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
   // video_broadcast_clear_frame();
    

    //top row
 
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( 160, 0, 192, 130);
    
    

}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
     pinMode(PIN_SWITCH_1, INPUT); 
     pinMode(PIN_SWITCH_2, INPUT); 
     pinMode(PIN_SWITCH_3, INPUT); 
     pinMode(PIN_SWITCH_4, INPUT); 


if (digitalRead(PIN_SWITCH_1) == HIGH)
     {
         CNFGColor( C3_COL_RED );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_2) == HIGH)
     {
         CNFGColor( C3_COL_GREEN_2 );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_3) == HIGH)
     {
         CNFGColor( C3_COL_LIGHT_YELLOW );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else if (digitalRead(PIN_SWITCH_4) == HIGH)
     {
         CNFGColor( C3_COL_DARK_BLUE );
         CNFGTackRectangle( 160, 0, 192, 130);
     }
     else
     {
         // Keep default value
     }
 }




void loop() {

}
