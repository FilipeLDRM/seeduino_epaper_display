// include library, include base class, make path known
#include <GxEPD.h>

#include <RTCZero.h>


#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

//#include GxEPD_BitmapExamples
#include "imagedata.h"



GxIO_Class io(SPI, /*CS=*/ 1, /*DC=*/ 2, /*RST=*/ 3); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=*/ 3, /*BUSY=*/ 4); // default selection of (9), 7


const uint32_t partial_update_period_s = 10;
const uint32_t full_update_period_s = 3;

uint32_t start_time;
uint32_t next_time;
uint32_t previous_time;
uint32_t previous_full_update;

uint32_t total_seconds = 0;

RTCZero rtc; // Criação de uma instância RTCZero

void setup(void)
{
  rtc.begin();
  // Configurar a data/hora apenas uma vez ou quando necessário
  /*
   rtc.setHours(15);
   rtc.setMinutes(2);
   rtc.setSeconds(0);
   rtc.setDay(4);
   rtc.setMonth(1);
   rtc.setYear(2024);
   */
  Serial.begin(115200);
  display.init(); // disable diagnostic output on Serial
  Serial.println("setup done");
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(0);
  // draw background
  display.drawExampleBitmap(IMAGE_DATA2, sizeof(IMAGE_DATA2));
  display.setFont(&FreeMonoBold9pt7b);
  // partial update to full screen to preset for partial update of box window
  // (this avoids strange background effects)
  display.drawExampleBitmap(IMAGE_DATA2, sizeof(IMAGE_DATA2), GxEPD::bm_default | GxEPD::bm_partial_update);
  start_time = next_time = previous_time = previous_full_update = rtc.getEpoch();

  display.setRotation(3);
}

void loop()
{
  uint32_t actual = rtc.getEpoch();
  while (actual < next_time)
  {
    // the "BlinkWithoutDelay" method works also for overflowed millis
    if ((actual - previous_time) > (partial_update_period_s))
    {
      //Serial.print(actual - previous_time); Serial.print(" > "); Serial.println(partial_update_period_s * 1000);
      break;
    }
    delay(100);
    actual = rtc.getEpoch();
  }
  //Serial.print("actual: "); Serial.print(actual); Serial.print(" previous: "); Serial.println(previous_time);
  if ((actual - previous_full_update) > full_update_period_s * 1000)
  {
    display.drawExampleBitmap(IMAGE_DATA2, sizeof(IMAGE_DATA2));
    display.drawExampleBitmap(IMAGE_DATA2, sizeof(IMAGE_DATA2), GxEPD::bm_default | GxEPD::bm_partial_update);
    previous_full_update = actual;
  }
  previous_time = actual;
  next_time += uint32_t(partial_update_period_s);
  total_seconds += partial_update_period_s;
  showPartialUpdate_AVR();
}

void print02d(uint32_t d)
{
  if (d < 10) display.print("0");
  display.print(d);
}

void drawCallback()
{
  uint16_t box_x = 40;
  uint16_t box_y = 40;
  uint16_t box_w = 170;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + 16;
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
  display.setCursor(box_x, cursor_y);
  display.print(rtc.getDay()); display.print("d "); print02d(rtc.getHours()); display.print(":"); print02d(rtc.getMinutes()); display.print(":"); print02d(rtc.getSeconds());
}

void showPartialUpdate_AVR()
{
  uint16_t box_x = 40;
  uint16_t box_y = 40;
  uint16_t box_w = 170;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + 14;
  display.drawPagedToWindow(drawCallback, box_x, box_y, box_w, box_h);
}
