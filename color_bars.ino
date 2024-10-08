#include <esp8266channel3lib.h>

uint32_t frameCount = 0;
int ball1Xposition=10;
int ball1Yposition=10;

int fieldHeight=150;
int fieldWidth=200;

int delta1X=1;
int delta1Y=1;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
   // video_broadcast_clear_frame();
    
   /* int * px = &CNFGPenX;
    int * py = &CNFGPenY;
    *px = 3;
    *py = 4;*/
    //top row
    CNFGColor( C3_COL_DD_WHITE );
    CNFGTackRectangle( 0, 0, 64, 130);
    CNFGColor( C3_COL_LIGHT_YELLOW );
    CNFGTackRectangle( 32, 0, 64, 130);
    CNFGColor( C3_COL_TURQUOISE );
    CNFGTackRectangle( 64, 0, 96, 130);
    CNFGColor( C3_COL_GREEN_1 );
    CNFGTackRectangle( 96, 0, 128, 130);
    
    CNFGColor( C3_COL_DARK_BLUE );
    CNFGTackRectangle( 128, 0, 160, 130);
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( 160, 0, 192, 130);
    CNFGColor( C3_COL_LIGHT_BLUE );
    CNFGTackRectangle( 192, 0, 224, 130);
    
    //middle row
    CNFGColor( C3_COL_LIGHT_BLUE );
    CNFGTackRectangle( 0, 130, 32, 150);
    CNFGColor( C3_COL_BLACK );
    CNFGTackRectangle( 32, 130, 64, 150);
    CNFGColor( C3_COL_DARK_BLUE );
    CNFGTackRectangle( 64, 130, 96, 150);
    CNFGColor( C3_COL_BLACK );
    CNFGTackRectangle( 96, 130, 128, 150);
    
    CNFGColor( C3_COL_TURQUOISE );
    CNFGTackRectangle( 128, 130, 160, 150);
    CNFGColor(C3_COL_BLACK );
    CNFGTackRectangle( 160, 130, 192, 150);
    CNFGColor( C3_COL_STRIPED_GRAY_1 );
    CNFGTackRectangle( 192, 130, 224, 150);

    //bottom row
    CNFGColor(C3_COL_DARK_BLUE );
    CNFGTackRectangle( 0, 150, 37, 190);
    CNFGColor( C3_COL_DD_WHITE );
    CNFGTackRectangle( 74, 150, 148, 190);
    /*CNFGColor( C3_COL_DARK_BLUE );
    CNFGTackRectangle( 74, 150, 111, 190);*/

 





    
   // *py = 190;
    //CNFGColor( C3_COL_GREEN_1 );
   // char content[255];
   // sprintf(content, "Frames: %u", frameCount++);
   // CNFGDrawText(content, 2 );
}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  channel3Init(NTSC, &loadFrame);
}

void loop() {
/*  ball1Xposition=ball1Xposition+delta1X;
  ball1Yposition=ball1Yposition+delta1Y;

  
if (ball1Xposition>=(fieldWidth-6)){
   delta1X=delta1X*-1;
}

if (ball1Xposition<=5){
   delta1X=delta1X*-1;
}

if (ball1Yposition>=(fieldHeight-5)){
   delta1Y=delta1Y*(-1);
}

if (ball1Yposition<=5){
   delta1Y=delta1Y*(-1);
  
}
delay(10);*/
}
