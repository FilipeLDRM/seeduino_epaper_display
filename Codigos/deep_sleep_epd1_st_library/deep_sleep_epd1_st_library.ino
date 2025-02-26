#include <SPI.h>

#include "epd2in13_V4.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1


unsigned char image[1050];
Paint paint(image, 0, 0);
Epd epd;


#include <RTCZero.h>//get the library here > https://github.com/arduino-libraries/RTCZero  
#include "ArduinoLowPower.h"//get library here > https://github.com/arduino-libraries/ArduinoLowPower

RTCZero rtc;//Create an RTCZero object

int currentSeconds ;
int currentMinutes;
int currentHours;
int totalSeconds;
int currentMinutes2 ;
int currentSeconds2;
char currentTime[6]; // Array para armazenar a string (mm:ss)

void loop()
{
    currentSeconds = rtc.getSeconds();
    currentMinutes = rtc.getMinutes();
    currentHours = rtc.getHours();

    totalSeconds = currentHours * 3600 + currentMinutes * 60 + currentSeconds;
    totalSeconds += 56; // Incrementa x segundos + 4  segundos
    currentHours = totalSeconds / 3600;
    currentMinutes = (totalSeconds % 3600) / 60;
    currentSeconds = totalSeconds % 60;
    rtc.setAlarmTime(currentHours, currentMinutes, currentSeconds);
    rtc.attachInterrupt(alarmMatch);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);

    LowPower.deepSleep();
  
    rtc.disableAlarm();
}

void alarmMatch(){
  epd.Init(FULL);
  Paint paint(image, epd.bufwidth*8, epd.bufheight);    //width should be the multiple of 8
  
  currentMinutes2 = rtc.getMinutes();
  currentSeconds2 = rtc.getSeconds();
  
  paint.Clear(UNCOLORED);
  sprintf(currentTime, "%02d:%02d", currentMinutes2, currentSeconds2);
  paint.DrawStringAt(20,10, currentTime, &Font24, COLORED);
  
  epd.Display1(image);//1
  paint.Clear(UNCOLORED);
  epd.Display1(image);//1
  paint.Clear(UNCOLORED);
  epd.Display1(image);//1
  paint.Clear(UNCOLORED);
  epd.Display1(image);//1
  
  epd.Sleep();
}



void setup()
{ 
  rtc.begin(); //initialize RTC 24H format
  rtc.setDate(8, 1, 24);
  rtc.setTime(10, 45, 0);
  alarmMatch();
}
