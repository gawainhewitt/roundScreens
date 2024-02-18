
#include <LovyanGFX.hpp>
#include "lgfx_setup.h"
#include "NotoSansBold36.h"
#include "birdFacts.h"
#include "stewartImages.h"

#define AA_FONT_LARGE NotoSansBold36

#define Screen1_CS 21 
#define Screen2_CS 22

#define SCREENOFF 1
#define SCREENON 0

#define BLACK 0x0000
#define ORANGE 0xE4E0
#define SKYBLUE 0x55BD
#define BLUISHGREEN 0x04EE
#define YELLOW 0xF728
#define BLUE 0x0396
#define VERMILLION 0xD2E0
#define REDDISHPURPLE 0xCBD4

LGFX tft;
LGFX_Sprite spr(&tft);

void setup(void)
{
  tft.init();

  Serial.begin(250000);

  pinMode(Screen1_CS, OUTPUT);
  pinMode(Screen2_CS, OUTPUT);

  tft.begin();

  tft.setRotation(1);

  spr.setColorDepth(16); // 16 bit colour needed to show antialiased fonts

  tft.fillScreen(REDDISHPURPLE);
}

int currentElement = 0;
int lastElement = NUMBER_OF_ELEMENTS;

void loop(void)
{
  int width = tft.width(); 
  int height = tft.height();
  int waitTime = 5000;

  for(int i = 0; i < 4; i++) {

    spr.createSprite(width -1, height -1);   // Create a sprite - must be smaller than the screen size? certainly not working on the drawing unless smaller

    spr.drawBitmap(-3, 0, epd_bitmap_allArray[i], 239, 239, BLUISHGREEN);
    // spr.drawRect(0, 0, 65, 65, YELLOW);

    digitalWrite(Screen1_CS, SCREENON);
    digitalWrite(Screen2_CS, SCREENOFF);

    spr.pushSprite(0, 0);         // Push to TFT screen coord x, y

    spr.deleteSprite(); // Recover memory

    delay(waitTime);
  }

  // for(int i = 0; i < 4; i++) {
  //   tft.clearDisplay();

  //   tft.drawBitmap(-3, 3, epd_bitmap_allArray[i], 240, 240, BLUISHGREEN);

  //   tft.display();

  //   delay(2000);
  // }

  
}

void writeScreen(int element) {
  int width = tft.width(); // Half the screen width
  int height = tft.height();
  int spriteHeight = 100;
  String factToDisplay = birdFacts[currentElement];

  spr.loadFont(AA_FONT_LARGE); // Load another different font into the sprite instance

  int sentanceLength = spr.textWidth(factToDisplay); // in pixels

  spr.createSprite(width, spriteHeight);   // Create a sprite 
 
  spr.setTextColor(YELLOW, REDDISHPURPLE); // Set the font colour and the background colour

  spr.setTextDatum(ML_DATUM); // Middle left datum

  spr.setTextWrap(false);

  digitalWrite(Screen1_CS, SCREENON);
  digitalWrite(Screen2_CS, SCREENOFF);

  spr.fillSprite(REDDISHPURPLE);
  spr.drawString("screen 1", 20, spriteHeight/2); // Make sure text fits in the Sprite!
  spr.pushSprite(0, height/2 - (spriteHeight/2));         // Push to TFT screen coord x, y

  spr.deleteSprite(); // Recover memory

  digitalWrite(Screen1_CS, SCREENOFF);
  digitalWrite(Screen2_CS, SCREENON);

  spr.createSprite(width, spriteHeight);   // Create a sprite 100 pixels wide and 50 high

  for(int i = width; i > 0 - sentanceLength; i--) {
    spr.fillSprite(REDDISHPURPLE);
    spr.drawString(factToDisplay, i, spriteHeight/2); // Make sure text fits in the Sprite!
    spr.pushSprite(0, height/2 - (spriteHeight/2) + 1);  // ok on this library it doesn't seem to be able to cope with the same number twice with two screens so this is a hack
  }
  
  spr.unloadFont(); // Remove the font to recover memory used

  spr.deleteSprite(); // Recover memory
}