// GxEPD_Hello World Example by Jean-Marc Zingg


// include library, include base class, make path known
#include <GxEPD.h>

// select the display class to use, only one
//#include <GxDEPG0150BN/GxDEPG0150BN.h>    // 1.50" b/w
//#include <GxGDEP015OC1/GxGDEP015OC1.h>    // 1.54" b/w
//#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w 200x200, SSD1681
//#include <GxGDEW0154T8/GxGDEW0154T8.h>    // 1.54" b/w 152x152 UC8151 (IL0373)
//#include <GxGDEW0154M09/GxGDEW0154M09.h>  // 1.54" b/w 200x200 JD79653A
//#include <GxGDEW0154M10/GxGDEW0154M10.h>  // 1.54" b/w 152x152 UC8151D
//#include <GxGDEW0154Z04/GxGDEW0154Z04.h>  // 1.54" b/w/r 200x200
//#include <GxGDEW0154Z17/GxGDEW0154Z17.h>  // 1.54" b/w/r 152x152
//#include <GxGDEH0154Z90/GxGDEH0154Z90.h>  // 1.54" b/w/r 200x200 SSD1681
//#include <GxGDEW0213I5F/GxGDEW0213I5F.h>  // 2.13" b/w 104x212 flexible
//#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w                          funcionou mais ou menos
#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel                funcionou bem
//#include <GxGDEH0213B73/GxGDEH0213B73.h>  // 2.13" b/w newer panel
//#include <GxGDEM0213B74/GxGDEM0213B74.h>  // 2.13" b/w 128x250 SSD1680           funcionou bem
//#include <GxGDEW0213Z16/GxGDEW0213Z16.h>  // 2.13" b/w/r
//#include <GxGDEH0213Z19/GxGDEH0213Z19.h>  // 2.13" b/w/r UC8151D
//#include <GxGDEW0213T5D/GxGDEW0213T5D.h>  // 2.13" b/w 104x212 UC8151D
//#include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w 128x250, SSD1680, TTGO T5 V2.4.1, V2.3.1
//#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
//#include <GxGDEW029T5/GxGDEW029T5.h>      // 2.9" b/w UC8151 (IL0373)
//#include <GxGDEW029T5D/GxGDEW029T5D.h>    // 2.9" b/w UC8151D
//#include <GxGDEM029T94/GxGDEM029T94.h>    // 2.9" b/w
//#include <GxDEPG0290BS/GxDEPG0290BS.h>    // 2.9" b/w Waveshare variant, TTGO T5 V2.4.1 2.9"
//#include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
//#include <GxGDEH029Z13/GxGDEH029Z13.h>    // 2.9" b/w/r UC8151D
//#include <GxGDEW026T0/GxGDEW026T0.h>      // 2.6" b/w
//#include <GxDEPG0266BN/GxDEPG0266BN.h>      // 2.66" b/w 152x296, SSD1680, TTGO T5 V2.66, TTGO T5 V2.4.1
//#include <GxGDEW027C44/GxGDEW027C44.h>    // 2.7" b/w/r
//#include <GxGDEW027W3/GxGDEW027W3.h>      // 2.7" b/w
//#include <GxGDEY027T91/GxGDEY027T91.h>    // 2.7" b/w
//#include <GxGDEW0371W7/GxGDEW0371W7.h>    // 3.7" b/w
//#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
//#include <GxGDEW042Z15/GxGDEW042Z15.h>    // 4.2" b/w/r
//#include <GxGDEW0583T7/GxGDEW0583T7.h>    // 5.83" b/w
//#include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
//#include <GxGDEW075T7/GxGDEW075T7.h>      // 7.5" b/w 800x480
//#include <GxGDEW075Z09/GxGDEW075Z09.h>    // 7.5" b/w/r
//#include <GxGDEW075Z08/GxGDEW075Z08.h>    // 7.5" b/w/r 800x480

#include GxEPD_BitmapExamples

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=*/ 1, /*DC=*/ 2, /*RST=*/ 3);
GxEPD_Class display(io, /*RST=*/ 3, /*BUSY=*/ 4); 



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  display.init(115200); // enable diagnostic output on Serial


  display.drawPaged(drawHelloWorld);

  //display.update();
  //display.powerDown();

  Serial.println("setup done");
}

void loop() {};

const char HelloWorld[] = "Hello World!";

void drawHelloWorld()
{
  //Serial.println("drawHelloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.print(HelloWorld);
  //Serial.println("drawHelloWorld done");
}

void drawHelloWorldForDummies()
{
  // This example function/method can be used with full buffered graphics AND/OR paged drawing graphics
  // for paged drawing it is to be used as callback function
  // it will be executed once or multiple times, as many as needed,
  // in case of full buffer it can be called directly, or as callback
  // IMPORTANT: each iteration needs to draw the same, to avoid strange effects
  // use a copy of values that might change, don't read e.g. from analog or pins in the loop!
  //Serial.println("drawHelloWorldForDummies");
  const char text[] = "Hello World!";
  // most e-papers have width < height (portrait) as native orientation, especially the small ones
  // in GxEPD rotation 0 is used for native orientation (most TFT libraries use 0 fix for portrait orientation)
  // set rotation to 1 (rotate right 90 degrees) to have enough space on small displays (landscape)
  display.setRotation(1);
  // select a suitable font in Adafruit_GFX
  display.setFont(&FreeMonoBold9pt7b);
  // on e-papers black on white is more pleasant to read
  display.setTextColor(GxEPD_BLACK);
  // Adafruit_GFX has a handy method getTextBounds() to determine the boundary box for a text for the actual font
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
  display.setCursor(x, y); // set the postition to start printing text
  display.print(text); // print some text
  //Serial.println("drawHelloWorldForDummies done");
}
