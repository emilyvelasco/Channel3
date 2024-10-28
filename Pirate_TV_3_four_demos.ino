/*This sketch runs on an ESP8266 and generates an analog TV
  signal that is transmitted over the air via a wire attached
  to the RX pin of the ESP8266. It has four virtual "channels"
  that can be selected by turning a rotary switch.

  The library that makes this possible was adapted for the
  Arduino build environment by Schlarmann and Alexander12827
  from a library developed by Charles Lohr. See Charles'
  repository for an in-depth explanation for how it works.

  Schlarmann's library:
  https://github.com/schlarmann/esp8266channel3lib

  Alexander12827's library:
  https://github.com/Alexander12827/chlib

  Charles Lohr's library:
  https://github.com/cnlohr/channel3
*/

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

int switchState = 0;
int lastSwitchState = 0;

//pirate tv demo graphic stuff
uint32_t frameCount = 0;
#include "data.h"

uint8_t col[DATA_WIDTH];

int doOnce = 4;
int * px = &CNFGPenX;
int * py = &CNFGPenY;
char content[255];

//bouncing balls stuff
int ball1Xposition = 30;
int ball1Yposition = 30;
int ball2Xposition = 20;
int ball2Yposition = 33;

int fieldHeight = 190;
int fieldWidth = 224;

//change this to change speed of balls
float delta1X = .003;
float delta1Y = .003;

float delta2X = .004;
float delta2Y = .0035;

float realBall1Xposition = 30;
float realBall1Yposition = 30;
float realBall2Xposition = 30;
float realBall2Yposition = 30;

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
  C3_COL_DARK_BLUE
};

float color_offset = 0;
int delay_count = 0;

// number of frames to skip between each color shift
const int delay_length = 2;

// Clear both buffers
int buffer_clear_to_do = 0;

// This callback gets called automatically every frame
void ICACHE_FLASH_ATTR loadFrame() {

  //this clears both buffers when the "channel" is changed
  if (buffer_clear_to_do > 0)
  {
    video_broadcast_clear_frame();
    buffer_clear_to_do -= 1;
  }

  //play demo 1 (color bars demo) if switch is in position 1
  if (PIN_SWITCH_1_val == LOW)
  {
    //records position of the switch
    switchState = 1;
    if (switchState != lastSwitchState) {
      //clears the screen of the last demo when switching to a new demo
      buffer_clear_to_do = 2;
      //stores position of rotary switch for later checking
      lastSwitchState = switchState;
    }
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
  //play demo 2 (pirate tv demo) if switch is in position 2
  /*this code for displaying a bitmap was adapted from
    some code that can be found in Schlarmann's ESPong
    repository. Also found there is a Python script
    for converting a bitmap into a byte array that is
    stored in data.h*/

  else if (PIN_SWITCH_2_val == LOW)
  {
    //records position of the switch
    switchState = 2;
    if (switchState != lastSwitchState) {
      //clears the screen of the last demo when switching to a new demo
      buffer_clear_to_do = 2;
      //this resets doOnce logic so the skull is redrawn every time the channel is selected
      doOnce = 4;
      //stores position of rotary switch for later checking
      lastSwitchState = switchState;
    }
    if (doOnce) {
      for (int i = 0; i < DATA_HEIGHT; i++) {
        memcpy_P(col, &dataArray[i * DATA_WIDTH], DATA_WIDTH);
        for (int j = 0; j < DATA_WIDTH; j++) {
          if (col[j])
            video_broadcast_tack_pixel(j + 40, i + 40, C3_COL_DD_WHITE);
          else
            video_broadcast_tack_pixel(j + 40, i + 40, C3_COL_DD_BLACK);
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
  //play demo 3 (bouncing balls) if switch is in position 3
  else if (PIN_SWITCH_3_val == LOW)
  {
    switchState = 3;
    if (switchState != lastSwitchState) {
      //clears the screen of the last demo when switching to a new demo
      buffer_clear_to_do = 2;
      //stores position of rotary switch for later checking
      lastSwitchState = switchState;
    }
    video_broadcast_clear_frame();
    CNFGColor( C3_COL_RED );
    CNFGTackRectangle( ball1Xposition, ball1Yposition, ball1Xposition + 15, ball1Yposition + 15);

    CNFGColor( C3_COL_GREEN_2 );
    CNFGTackRectangle( ball2Xposition, ball2Yposition, ball2Xposition + 20, ball2Yposition + 20);
  }
  //play demo 4 (rainbow cycle) if switch is in position 4

  else if (PIN_SWITCH_4_val == LOW)
  {
    switchState = 4;
    if (switchState != lastSwitchState) {
      //clears the screen of the last demo when switching to a new demo
      buffer_clear_to_do = 2;
      //stores position of rotary switch for later checking
      lastSwitchState = switchState;
    }
     int color_index = color_offset;
 

  color_offset=color_offset+.5;


  //horizontals
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 10, 216, 15 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 30, 216, 35 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 50, 216, 55 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 70, 216, 75 );  
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 90, 216, 95 );
  CNFGColor(  color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 110, 216, 115 );  
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 130, 216, 135 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 150, 216, 155 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 170, 216, 175 );
  CNFGColor( color_array[color_index++ % n_lines] );
  CNFGTackRectangle( 10, 190, 216, 195 );
  }
  else
  {
    //do nothing
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



  /*moves balls around by incrementing a a float by
    small amounts and setting an int to equal the
    float. avoids using a delay to slow the
    ball speed*/
  realBall1Xposition = realBall1Xposition + delta1X;
  realBall1Yposition = realBall1Yposition + delta1Y;
  ball1Xposition = realBall1Xposition;
  ball1Yposition = realBall1Yposition;


  realBall2Xposition = realBall2Xposition + delta2X;
  realBall2Yposition = realBall2Yposition + delta2Y;
  ball2Xposition = realBall2Xposition;
  ball2Yposition = realBall2Yposition;


  if (ball1Xposition >= (fieldWidth - 12)) {
    delta1X = delta1X * -1;
  }

  if (ball1Xposition <= 12) {
    delta1X = delta1X * -1;
  }

  if (ball1Yposition >= (fieldHeight - 12)) {
    delta1Y = delta1Y * (-1);
  }

  if (ball1Yposition <= 22) {
    delta1Y = delta1Y * (-1);

  }

  //ball 2 logic below

  if (ball2Xposition >= (fieldWidth - 12)) {
    delta2X = delta2X * -1;
  }

  if (ball2Xposition <= 5) {
    delta2X = delta2X * -1;
  }

  if (ball2Yposition >= (fieldHeight - 12)) {
    delta2Y = delta2Y * (-1);
  }

  if (ball2Yposition <= 5) {
    delta2Y = delta2Y * (-1);
  }
}
