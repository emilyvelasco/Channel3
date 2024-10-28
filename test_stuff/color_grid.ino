#include <esp8266channel3lib.h>


// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
   // video_broadcast_clear_frame();
    
   /* int * px = &CNFGPenX;
    int * py = &CNFGPenY;
    *px = 3;
    *py = 4;*/
    //verticals
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( 4, 0, 9, 195 );
    CNFGColor( C3_COL_LIGHT_PINK );
    CNFGTackRectangle( 27, 0, 32, 195 );
    CNFGColor( C3_COL_LIGHT_YELLOW );
    CNFGTackRectangle( 50, 0, 55, 195 );
    CNFGColor( C3_COL_GREEN_2 );
    CNFGTackRectangle( 73, 0, 78, 195 );  
    CNFGColor( C3_COL_GREEN_1 );
    CNFGTackRectangle( 96, 0, 101, 195 );
    CNFGColor(  C3_COL_TURQUOISE );
    CNFGTackRectangle( 119, 0, 124, 195 );  
    CNFGColor( C3_COL_BABYBLUE_1 );
    CNFGTackRectangle( 142, 0, 147, 195 );
    CNFGColor( C3_COL_BABYBLUE_2 );
    CNFGTackRectangle( 165, 0, 170, 195 );
    CNFGColor( C3_COL_LIGHT_BLUE );
    CNFGTackRectangle( 188, 0, 193, 195 );
    CNFGColor( C3_COL_DARK_BLUE );
    CNFGTackRectangle( 211, 0, 216, 195 );

    //horizontals
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( 0, 10, 216, 15 );
    CNFGColor( C3_COL_LIGHT_PINK );
    CNFGTackRectangle( 0, 30, 216, 35 );
    CNFGColor( C3_COL_LIGHT_YELLOW );
    CNFGTackRectangle( 0, 50, 216, 55 );
    CNFGColor( C3_COL_GREEN_2 );
    CNFGTackRectangle( 0, 70, 216, 75 );  
    CNFGColor( C3_COL_GREEN_1 );
    CNFGTackRectangle( 0, 90, 216, 95 );
    CNFGColor(  C3_COL_TURQUOISE );
    CNFGTackRectangle( 0, 110, 216, 115 );  
    CNFGColor( C3_COL_BABYBLUE_1 );
    CNFGTackRectangle( 0, 130, 216, 135 );
    CNFGColor( C3_COL_BABYBLUE_2 );
    CNFGTackRectangle( 0, 150, 216, 155 );
    CNFGColor( C3_COL_LIGHT_BLUE );
    CNFGTackRectangle( 0, 170, 216, 175 );
    CNFGColor( C3_COL_DARK_BLUE );
    CNFGTackRectangle( 0, 190, 216, 195 );

}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  channel3Init(NTSC, &loadFrame);
}

void loop() {

}
