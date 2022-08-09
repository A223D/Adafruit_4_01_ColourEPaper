#include <Adafruit_4_01_ColourEPaper.h>

#include <Fonts/FreeSansBold24pt7b.h>

#define RST_PIN         26
#define DC_PIN          27
#define BUSY_PIN        25

#define HOWMUCH   71

#define WIDTH           640
#define HEIGHT          400

#define HSPI_MISO   12
#define HSPI_COPI   13
#define HSPI_SCLK   14
#define HSPI_SS     15

//SPIClass* hspi = NULL;

Adafruit_4_01_ColourEPaper ePaperObject(WIDTH, HEIGHT, RST_PIN, DC_PIN, BUSY_PIN, false);

void setup() {
  //hspi = new SPIClass(HSPI);
  //hspi->begin();
  pinMode(HSPI_SS, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  pinMode(DC_PIN, OUTPUT);
  pinMode(BUSY_PIN, INPUT);
  Serial.begin(115200);
  ePaperObject.begin(HSPI_SCLK, HSPI_COPI, HSPI_SS);
  Serial.println("Let's print a line");
  ePaperObject.display();
  ePaperObject.waitForScreenBlocking();
  Serial.println("Blank Screen now");
  delay(10000);
  apparentlyFunction();

  ePaperObject.display();
  ePaperObject.waitForScreenBlocking();
  Serial.println("Done!");
}

void loop() {
  // put your main code here, to run repeatedly:

}


void apparentlyFunction() {
  ePaperObject.setFont(&FreeSansBold24pt7b);
  ePaperObject.setTextSize(1);           // Normal 1:1 pixel scale
  ePaperObject.setTextColor(EPD_COLOUR_BLACK);        // Draw white text
  ePaperObject.setCursor(52, 33);            // Start at top-left corner
  ePaperObject.println("Apparently this works...");

  ePaperObject.setTextColor(EPD_COLOUR_GREEN);        // Draw white text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 1));        // Start at top-left corner
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_BLUE);        // Draw white text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 2));        // Start at top-left corner
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_RED);        // Draw white text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 3));        // Start at top-left corner
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_YELLOW);        // Draw white text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 4));        // Start at top-left corner
  ePaperObject.println("And this...");

  ePaperObject.setTextColor(EPD_COLOUR_ORANGE);        // Draw white text
  ePaperObject.setCursor(358, 33 + (HOWMUCH * 5));        // Start at top-left corner
  ePaperObject.println("And this...");

}