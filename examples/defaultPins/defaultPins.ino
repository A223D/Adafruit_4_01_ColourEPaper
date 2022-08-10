#include <Adafruit_4_01_ColourEPaper.h>

#include <Fonts/FreeSansBold24pt7b.h>

#define RST_PIN 26
#define DC_PIN 27
#define BUSY_PIN 25

#define HOWMUCH 71

#define WIDTH 640
#define HEIGHT 400

Adafruit_4_01_ColourEPaper ePaperObject(WIDTH, HEIGHT, RST_PIN, DC_PIN, BUSY_PIN, false);

void setup()
{
  Serial.begin(115200);
  if (!ePaperObject.begin())
  {
    Serial.println("Something went wrong. Enable debugging and check");
  }

  Serial.println("Let's clear the screen");
  ePaperObject.display();
  ePaperObject.waitForScreenBlocking();

  Serial.println("Blank Screen now");
  delay(10000); // wait for 10 seconds

  apparentlyFunction();
  ePaperObject.display();
  while (ePaperObject.checkBusy())
    ;
  ePaperObject.sendPOFandLeaveSPI();

  Serial.println("Done!");
}

void loop()
{

  // Nothing here
}

void apparentlyFunction()
{
  ePaperObject.setFont(&FreeSansBold24pt7b);
  ePaperObject.setTextSize(1);                 // Normal 1:1 pixel scale
  ePaperObject.setTextColor(EPD_COLOUR_BLACK); // Draw black text
  ePaperObject.setCursor(52, 33);              // Start at top-left corner
  ePaperObject.println("Apparently this works...");

  ePaperObject.setTextColor(EPD_COLOUR_GREEN); // Draw green text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 1));
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_BLUE); // Draw blue text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 2));
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_RED); // Draw red text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 3));
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_YELLOW); // Draw yellow text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 4));
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_ORANGE); // Draw orange text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 5));
  ePaperObject.println("And this...");
}
