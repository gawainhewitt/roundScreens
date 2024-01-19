#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "NotoSansMonoSCB20.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36
#define AA_FONT_MONO  NotoSansMonoSCB20 // NotoSansMono-SemiCondensedBold 20pt

#define Screen1_CS 21 
#define Screen2_CS 22

#define screenOff 1
#define screenOn 0

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

  tft.fillScreen(TFT_BLACK);
}

const int NUMBER_OF_ELEMENTS = 16;
const int MAX_SIZE = 102;

char birdFacts [NUMBER_OF_ELEMENTS] [MAX_SIZE] = { 
 { "There are over 11,000 known species of birds in the world." }, 
 { "The Ostrich is the largest bird and cannot fly, but it is an excellent runner." }, 
 { "Hummingbirds are the only birds that can fly backward." }, 
 { "Penguins are birds but are unable to fly. They are exceptional swimmers." }, 
 { "The Arctic Tern has the longest migratory journey, covering about 18,641 miles (30,000 km) annually." }, 
 { "The smallest bird in the world is the Bee Hummingbird, weighing around 1.6 to 2 grams." }, 
 { "Falcons are among the fastest birds, reaching speeds of up to 240 mph (386 km/h) in a dive." }, 
 { "The Lyrebird is known for its incredible ability to mimic natural and artificial sounds." }, 
 { "The Kakapo, a nocturnal parrot from New Zealand, is the heaviest parrot and is critically endangered." }, 
 { "Crows are highly intelligent birds and can solve complex problems." }, 
 { "Birds are descendants of dinosaurs." },
 { "The kiwi bird is native to New Zealand and is the only bird with nostrils at the tip of its beak." },
 { "Albatrosses have the longest wingspan of any living bird, reaching up to 9 ft 10in feet (3 meters)." },
 { "The African Grey Parrot is known for its exceptional ability to mimic human speech." },
 { "Some birds, like the Common Swift, can spend almost their entire lives in the air." },
 { "The Hoatzin chick has claws on its wings, a feature retained from its dinosaur ancestors." }
 };

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
 
  spr.setTextColor(TFT_BLACK, TFT_GREEN); // Set the font colour and the background colour

  spr.setTextDatum(ML_DATUM); // Middle left datum

  spr.setTextWrap(false);

  digitalWrite(Screen1_CS, screenOn);
  digitalWrite(Screen2_CS, screenOff);

  spr.fillSprite(TFT_GREEN);
  spr.drawString("screen 1", 20, spriteHeight/2); // Make sure text fits in the Sprite!
  spr.pushSprite(0, height/2 - (spriteHeight/2));         // Push to TFT screen coord x, y

  digitalWrite(Screen1_CS, screenOff);
  digitalWrite(Screen2_CS, screenOn);

  for(int i = width; i > 0 - sentanceLength; i--) {
    spr.fillSprite(TFT_GREEN);
    spr.drawString(factToDisplay, i, spriteHeight/2); // Make sure text fits in the Sprite!
    spr.pushSprite(0, height/2 - (spriteHeight/2));         // Push to TFT screen coord x, y
  }
  
  spr.unloadFont(); // Remove the font to recover memory used

  spr.deleteSprite(); // Recover memory
}