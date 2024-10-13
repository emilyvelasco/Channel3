#include <esp8266channel3lib.h>

//rotary switch stuff
int PIN_SWITCH_1 = 12;
int PIN_SWITCH_2 = 13;
int PIN_SWITCH_3 = 14;
int PIN_SWITCH_4 = 4;

int PIN_SWITCH_1_val = 0;
int PIN_SWITCH_2_val = 0;
int PIN_SWITCH_3_val = 0;
int PIN_SWITCH_4_val = 0;

//pirate tv stuff
uint32_t frameCount = 0;
#include "data.h"

uint8_t col[DATA_WIDTH];

int doOnce = 4;
int * px = &CNFGPenX;
int * py = &CNFGPenY;
char content[255];

//bouncing balls stuff
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
const int ball_delay_length = 2;
int ball_delay_count = 0;

//rainbow demo stuff
int n_lines = 10;

uint8_t color_array[] = {
  C3_COL_RED,
  C3_COL_LIGHT_PINK,
  C3_COL_LIGHT_YELLOW,
  C3_COL_GREEN_2,
  C3_COL_GREEN_1,
  C3_COL_TURQUOISE,
  C3_COL_BABYBLUE_1,
  C3_COL_BABYBLUE_2,
  C3_COL_LIGHT_BLUE,
  C3_COL_DARK_BLUE};

int color_offset = 0;
int delay_count = 0;

// number of frames to skip between each color shift
const int delay_length = 2;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {
    
    

    //top row
//color bars demo
if (PIN_SWITCH_1_val == LOW)
     {
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

     }
     //pirate tv demo
     else if (PIN_SWITCH_2_val == LOW)
     {
      if(doOnce){
        for(int i=0; i<DATA_HEIGHT; i++){
          memcpy_P(col, &dataArray[i*DATA_WIDTH], DATA_WIDTH);
          for(int j=0; j<DATA_WIDTH; j++){
            if(col[j])
              video_broadcast_tack_pixel(j+40, i+40, C3_COL_DD_WHITE);
            else
              video_broadcast_tack_pixel(j+40, i+40, C3_COL_DD_BLACK);
          }
        }
        doOnce--;
      }
      *px = 30;
      *py = 10;
      CNFGColor( C3_COL_GREEN_2 );
      CNFGDrawText("You are", 3 );
      *px = 25;
      *py = 30;
      CNFGColor( C3_COL_GREEN_2 );
      CNFGDrawText("Watching", 3 );
    
      *px = 30;
      *py = 150;
      CNFGColor( C3_COL_RED );
      CNFGDrawText("KESP-TV", 3 );
      *px = 20;
      *py = 170;
      CNFGColor( C3_COL_RED );
      CNFGDrawText("at 61.25 Mhz", 2 );
      
      CNFGColor( C3_COL_BLACK );
      CNFGTackRectangle( 50, 195, 200, 210 );
    
      *px = 40;
      *py = 195;
      CNFGColor( C3_COL_DD_WHITE );
      char content[255];
      sprintf(content, "Frames: %u", frameCount++);
      CNFGDrawText(content, 3 );
         }
     //bouncing balls demo
     else if (PIN_SWITCH_3_val == LOW)
     {
        video_broadcast_clear_frame();
        
    
        CNFGColor( C3_COL_RED );
        CNFGTackRectangle( ball1Xposition, ball1Yposition, ball1Xposition+15, ball1Yposition+15);
    
        CNFGColor( C3_COL_GREEN_2 );
        CNFGTackRectangle( ball2Xposition, ball2Yposition, ball2Xposition+20, ball2Yposition+20);
     }
     else if (PIN_SWITCH_4_val == LOW)
     {
 int color_index = color_offset;
 
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 4, 0, 9, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 27, 0, 32, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 50, 0, 55, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 73, 0, 78, 195 );  
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 96, 0, 101, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 119, 0, 124, 195 );  
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 142, 0, 147, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 165, 0, 170, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 188, 0, 193, 195 );
  CNFGColor(color_array[color_index++ % n_lines]);
  CNFGTackRectangle( 211, 0, 216, 195 );

  if (!(delay_count++ % delay_length)){
    color_offset++;
  }

  //horizontals
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 10, 216, 15 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 30, 216, 35 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 50, 216, 55 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 70, 216, 75 );  
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 90, 216, 95 );
  CNFGColor(  color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 110, 216, 115 );  
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 130, 216, 135 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 150, 216, 155 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 170, 216, 175 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 0, 190, 216, 195 );

     }
     else
     {
      video_broadcast_clear_frame();
     }





    

}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  channel3Init(NTSC, &loadFrame);
  pinMode(PIN_SWITCH_1, INPUT_PULLUP);
  pinMode(PIN_SWITCH_2, INPUT_PULLUP);
  pinMode(PIN_SWITCH_3, INPUT_PULLUP);
  pinMode(PIN_SWITCH_4, INPUT_PULLUP);
}

void loop() {
  //reads switch position
PIN_SWITCH_1_val = digitalRead(PIN_SWITCH_1);  
PIN_SWITCH_2_val = digitalRead(PIN_SWITCH_2);  
PIN_SWITCH_3_val = digitalRead(PIN_SWITCH_3);  
PIN_SWITCH_4_val = digitalRead(PIN_SWITCH_4);  



//moves balls around
if (!(ball_delay_count++ % ball_delay_length)){
  ball1Xposition=ball1Xposition+delta1X;
  ball1Yposition=ball1Yposition+delta1Y;


  ball2Xposition=ball2Xposition-delta2X;
  ball2Yposition=ball2Yposition-delta2Y;
}
  
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
}
