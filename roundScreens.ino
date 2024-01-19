/*
  This sketch is the same as the Font_Demo_1 example, except the fonts in this
  example are in a FLASH (program memory) array. This means that processors
  such as the STM32 series that are not supported by a SPIFFS library can use
  smooth (anti-aliased) fonts.
*/

/*
  There are four different methods of plotting anti-aliased fonts to the screen.

  This sketch uses method 1, using tft.print() and tft.println() calls.

  In some cases the sketch shows what can go wrong too, so read the comments!
  
  The font is rendered WITHOUT a background, but a background colour needs to be
  set so the anti-aliasing of the character is performed correctly. This is because
  characters are drawn one by one.
  
  This method is good for static text that does not change often because changing
  values may flicker. The text appears at the tft cursor coordinates.

  It is also possible to "print" text directly into a created sprite, for example using
  spr.println("Hello"); and then push the sprite to the screen. That method is not
  demonstrated in this sketch.
  
*/

//  A processing sketch to create new fonts can be found in the Tools folder of TFT_eSPI
//  https://github.com/Bodmer/TFT_eSPI/tree/master/Tools/Create_Smooth_Font/Create_font

//  This sketch uses font files created from the Noto family of fonts:
//  https://www.google.com/get/noto/

#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

#define Screen1_CS 21
#define Screen2_CS 22

#define screenOff 1
#define screenOn 0

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();


void setup(void) {

  Serial.begin(250000);

  pinMode(Screen1_CS, OUTPUT);
  pinMode(Screen2_CS, OUTPUT);

  tft.begin();

  tft.setRotation(0);
}


void loop() {

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour AND the background colour
                                          // so the anti-aliasing works

  tft.setCursor(0, 0); // Set cursor at top left of screen


  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // Small font
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  Serial.println("Loading font");

  tft.loadFont(AA_FONT_SMALL);    // Must load the font first

  tft.setCursor(120, 120);

  tft.setTextDatum(MC_DATUM); // these two lines are about centreing the text

  digitalWrite(Screen1_CS, screenOn);
  digitalWrite(Screen2_CS, screenOff);

  tft.drawString("celebrate that", tft.width() / 2, tft.height() / 2); // drawstring("string", x, y);

  digitalWrite(Screen1_CS, screenOff);
  digitalWrite(Screen2_CS, screenOn);

  tft.drawString("which you have achieved", tft.width() / 2, tft.height() / 2); // drawstring("string", x, y);


  // tft.println(); // New line

  // tft.print("ABC"); // print leaves cursor at end of line

  // tft.setTextColor(TFT_CYAN, TFT_BLACK);
  // tft.println("1234"); // Added to line after ABC

  // tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  // // print stream formatting can be used,see:
  // // https://www.arduino.cc/en/Serial/Print
  // int ivalue = 1234;
  // tft.println(ivalue);       // print as an ASCII-encoded decimal
  // tft.println(ivalue, DEC);  // print as an ASCII-encoded decimal
  // tft.println(ivalue, HEX);  // print as an ASCII-encoded hexadecimal
  // tft.println(ivalue, OCT);  // print as an ASCII-encoded octal
  // tft.println(ivalue, BIN);  // print as an ASCII-encoded binary

  // tft.println(); // New line
  // tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  // float fvalue = 1.23456;
  // tft.println(fvalue, 0);  // no decimal places
  // tft.println(fvalue, 1);  // 1 decimal place
  // tft.println(fvalue, 2);  // 2 decimal places
  // tft.println(fvalue, 5);  // 5 decimal places

  delay(5000);

  
  // // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // // Large font text wrapping
  // // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // tft.fillScreen(TFT_BLACK);
  
  // tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Change the font colour and the background colour

  // tft.setCursor(0, 0); // Set cursor at top left of screen

  // tft.println("Large font!");

  // tft.setTextWrap(true); // Wrap on width
  // tft.setTextColor(TFT_CYAN, TFT_BLACK);
  // tft.println("Long lines wrap to the next line");

  // tft.setTextWrap(false, false); // Wrap on width and height switched off
  // tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  // tft.println("Unless text wrap is switched off");

  // tft.unloadFont(); // Remove the font to recover memory used

  // delay(8000);
}
