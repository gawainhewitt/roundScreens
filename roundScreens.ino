#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "NotoSansMonoSCB20.h"
#include "birdFacts.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36
#define AA_FONT_MONO  NotoSansMonoSCB20 // NotoSansMono-SemiCondensedBold 20pt

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


#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI    tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite class needs to be invoked

void setup(void) {

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

void loop() {

  writeScreen(currentElement);

  lastElement = currentElement;
  currentElement = (currentElement + 1) % NUMBER_OF_ELEMENTS;

  Serial.print("element is ");
  Serial.println(currentElement);
    
  delay(1000);
  
  
}

void writeScreen(int element) {
  int width = tft.width(); // Half the screen width
  int height = tft.height();
  int spriteHeight = 100;
  String factToDisplay = birdFacts[currentElement];

  spr.loadFont(AA_FONT_LARGE); // Load another different font into the sprite instance

  int sentanceLength = spr.textWidth(factToDisplay); // in pixels

  spr.createSprite(width, spriteHeight);   // Create a sprite 100 pixels wide and 50 high
 
  spr.setTextColor(YELLOW, REDDISHPURPLE); // Set the font colour and the background colour

  spr.setTextDatum(ML_DATUM); // Middle left datum

  spr.setTextWrap(false);

  digitalWrite(Screen1_CS, SCREENON);
  digitalWrite(Screen2_CS, SCREENOFF);

  spr.fillSprite(REDDISHPURPLE);
  spr.drawString("screen 1", 20, spriteHeight/2); // Make sure text fits in the Sprite!
  spr.pushSprite(0, height/2 - (spriteHeight/2));         // Push to TFT screen coord x, y

  digitalWrite(Screen1_CS, SCREENOFF);
  digitalWrite(Screen2_CS, SCREENON);

  for(int i = width; i > 0 - sentanceLength; i--) {
    spr.fillSprite(REDDISHPURPLE);
    spr.drawString(factToDisplay, i, spriteHeight/2); // Make sure text fits in the Sprite!
    spr.pushSprite(0, height/2 - (spriteHeight/2));         // Push to TFT screen coord x, y
  }
  
  spr.unloadFont(); // Remove the font to recover memory used

  spr.deleteSprite(); // Recover memory
}