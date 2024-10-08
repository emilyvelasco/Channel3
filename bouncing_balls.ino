#include <esp8266channel3lib.h>

uint32_t frameCount = 0;
int ball1Xposition=10;
int ball1Yposition=10;
int ball2Xposition=20;
int ball2Yposition=33;

int fieldHeight=190;
int fieldWidth=224;

int delta1X=1;
int delta1Y=1;

int delta2X=1;
int delta2Y=2;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
    video_broadcast_clear_frame();
    
   /* int * px = &CNFGPenX;
    int * py = &CNFGPenY;
    *px = 3;
    *py = 4;*/
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( ball1Xposition, ball1Yposition, ball1Xposition+15, ball1Yposition+15);

    CNFGColor( C3_COL_GREEN_2 );
    CNFGTackRectangle( ball2Xposition, ball2Yposition, ball2Xposition+20, ball2Yposition+20);




    
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
  ball1Xposition=ball1Xposition+delta1X;
  ball1Yposition=ball1Yposition+delta1Y;


  ball2Xposition=ball2Xposition-delta2X;
  ball2Yposition=ball2Yposition-delta2Y;

  
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

//ball 2 logic below

if (ball2Xposition>=(fieldWidth-10)){
   delta2X=delta2X*-1;
}

if (ball2Xposition<=5){
   delta2X=delta2X*-1;
}

if (ball2Yposition>=(fieldHeight-5)){
   delta2Y=delta2Y*(-1);
}

if (ball2Yposition<=5){
   delta2Y=delta2Y*(-1);
}
delay(10);
}
