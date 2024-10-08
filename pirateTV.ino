#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <esp8266channel3lib.h>

// PAL only! you need to adjust the height in convert.py to 220 to use this with NTSC!
#include "data.h"

uint8_t col[DATA_WIDTH];
uint32_t frameCount = 0;
int doOnce = 4;
int * px = &CNFGPenX;
int * py = &CNFGPenY;
char content[255];

// This callback gets called automatically every frame
void loadFrame(){
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
  CNFGDrawText("ESP8266", 3 );
  *px = 20;
  *py = 170;
  CNFGColor( C3_COL_RED );
  CNFGDrawText("Pirate TV", 3 );
  
  CNFGColor( C3_COL_BLACK );
  CNFGTackRectangle( 50, 195, 200, 210 );

  *px = 40;
  *py = 195;
  CNFGColor( C3_COL_DD_WHITE );
  char content[255];
  sprintf(content, "Frames: %u", frameCount++);
  CNFGDrawText(content, 3 );

}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  Serial.begin(115200);
  Serial.println("Starting ESP-EtchASketch!");
  WiFi.softAP("EtchaSketchP", "EtchaSketchP");

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("EtchaSketchP");

  ArduinoOTA.onStart([]() {
    channel3Deinit();
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {   
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {    
    Serial.printf("Progress: %u%%\r\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  
  channel3Init(NTSC, &loadFrame);
  Serial.printf("Update via %s:8266\n", WiFi.softAPIP().toString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  // Handle OTA requests
  ArduinoOTA.handle();
}
