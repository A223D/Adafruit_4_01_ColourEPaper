#include <Adafruit_4_01_ColourEPaper.h>

#define RST_PIN 26
#define DC_PIN 27
#define BUSY_PIN 25

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

  ePaperObject.test();
  while (ePaperObject.checkBusy())
    ;
  ePaperObject.sendPOFandLeaveSPI();

  Serial.println("Done!");
}

void loop()
{

  // Nothing here
}
