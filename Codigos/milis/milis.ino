#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h> // including both doesn't use more code or ram
#include <GxEPD2_3C.h> // including both doesn't use more code or ram
#include <U8g2_for_Adafruit_GFX.h>

//if you have another microcontroller or another e-ink display module you have to change the following line
GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(GxEPD2_213_B72(/*CS=D8*/ 1, /*DC=D3*/ 2, /*RST=D4*/ 3, /*BUSY=D2*/ 4)); // GDEH0213B72 122x250, SSD1675A (IL3897)

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void setup()
{
  display.init();
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  display.setRotation(1);

  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
  delay(1000);

  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg);

  do{
    display.fillScreen(GxEPD_WHITE);

    u8g2Fonts.setFont(u8g2_font_fub20_tr);   //font is set
    u8g2Fonts.setCursor(20, 80);             //cursor(x,y)
    u8g2Fonts.print("Millis: ");   //print the text
  }while (display.nextPage());
}


void loop() {
  display.setPartialWindow(115, 50, 200, 40);
  display.firstPage();

  do{
    display.fillScreen(GxEPD_WHITE);
    u8g2Fonts.setCursor(120, 80);
    u8g2Fonts.print(millis());
  }while(display.nextPage());
}
