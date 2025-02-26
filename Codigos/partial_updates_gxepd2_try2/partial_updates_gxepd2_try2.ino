#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h> // including both doesn't use more code or ram
#include <GxEPD2_3C.h> // including both doesn't use more code or ram
#include <U8g2_for_Adafruit_GFX.h>

//if you have another microcontroller or another e-ink display module you have to change the following line
GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(GxEPD2_213_B72(/*CS=D8*/ 1, /*DC=D3*/ 2, /*RST=D4*/ 3, /*BUSY=D2*/ 4)); // GDEH0213B72 122x250, SSD1675A (IL3897)

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

#include <RTCZero.h>//get the library here > https://github.com/arduino-libraries/RTCZero  
#include "ArduinoLowPower.h"//get library here > https://github.com/arduino-libraries/ArduinoLowPower

RTCZero rtc;//Create an RTCZero object

int currentSeconds ;
int currentMinutes;
int currentHours;
int totalSeconds;


void setup()
{
 
    display.init(0, true, 2,false); // inicialização total mais completa do display
    display.setTextColor(GxEPD_BLACK);
    display.firstPage();
    display.setRotation(3);

    u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX

  
    uint16_t bg = GxEPD_WHITE;
    uint16_t fg = GxEPD_BLACK;
    u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts.setBackgroundColor(bg);

  rtc.begin(); //initialize RTC 24H format
  rtc.setDate(8, 1, 24);
  rtc.setTime(10, 45, 0);

 
   display.fillScreen(GxEPD_WHITE);

   u8g2Fonts.setFont(u8g2_font_fub20_tr);   //font is set
   u8g2Fonts.setCursor(20, 80);             //cursor(x,y)
   u8g2Fonts.print("Horas: ");   //print the text
   display.nextPage();
    
}


void loop() {

    currentSeconds = rtc.getSeconds();
    currentMinutes = rtc.getMinutes();
    currentHours = rtc.getHours();

    totalSeconds = currentHours * 3600 + currentMinutes * 60 + currentSeconds;
    totalSeconds += 15; // Incrementa 15 segundos + 4 
    currentHours = totalSeconds / 3600;
    currentMinutes = (totalSeconds % 3600) / 60;
    currentSeconds = totalSeconds % 60;
    rtc.setAlarmTime(currentHours, currentMinutes, currentSeconds);
    rtc.attachInterrupt(alarmMatch);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);
  
  display.end();
  LowPower.deepSleep();
  
  rtc.disableAlarm();
 
  }
  

void alarmMatch()
{
   display.init(0, true, 2,false);
   display.setPartialWindow(115, 50, 200, 40);
   display.firstPage();
   display.fillScreen(GxEPD_WHITE);
   u8g2Fonts.setCursor(120, 80);
   u8g2Fonts.print(rtc.getHours());
   u8g2Fonts.print(" : ");
   u8g2Fonts.print(rtc.getMinutes());
   u8g2Fonts.print(" : ");
   u8g2Fonts.print(rtc.getSeconds());
   display.nextPage(); 
   display.hibernate();
}
