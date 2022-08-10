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
}

void loop()
{
    // display clearing
    Serial.println("Clearing the screen");
    ePaperObject.clear();
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // display single pixel at (10, 10)
    Serial.println("Drawing a single pixel at (10, 10)");
    ePaperObject.drawPixel(10, 10, EPD_COLOUR_BLACK);
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing lines on the display
    Serial.println("Drawing lines on the display");
    ePaperObject.clearDisplay(); // Clear display buffer
    for (i = 0; i < ePaperObject.width(); i += 4)
    {
        ePaperObject.drawLine(0, 0, i, ePaperObject.height() - 1, EPD_COLOUR_GREEN);
    }
    for (i = 0; i < ePaperObject.height(); i += 4)
    {
        ePaperObject.drawLine(0, 0, ePaperObject.width() - 1, i, EPD_COLOUR_BLUE);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    //drawing rectangles on the display
    Serial.println("Drawing rectangles on the display");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < ePaperObject.height() / 2; i += 2)
    {
        ePaperObject.drawRect(i, i, ePaperObject.width() - 2 * i, ePaperObject.height() - 2 * i, EPD_COLOUR_RED);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    //drawing a filled rectangle
    Serial.println("Drawing filled rectangle on the display. You will only see 1 though");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < ePaperObject.height() / 2; i += 3)
    {
        // The INVERSE color is used so rectangles alternate white/black
        ePaperObject.fillRect(i, i, ePaperObject.width() - i * 2, ePaperObject.height() - i * 2, EPD_COLOUR_YELLOW);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    Serial.println("Done");
}
