#include <Adafruit_4_01_ColourEPaper.h>

#define RST_PIN 26
#define DC_PIN 27
#define BUSY_PIN 25

#define WIDTH 640
#define HEIGHT 400

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char logo_bmp[] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};

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
    ePaperObject.clearDisplay();
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
    for (int16_t i = 0; i < ePaperObject.width(); i += 4)
    {
        ePaperObject.drawLine(0, 0, i, ePaperObject.height() - 1, EPD_COLOUR_GREEN);
    }
    for (int16_t i = 0; i < ePaperObject.height(); i += 4)
    {
        ePaperObject.drawLine(0, 0, ePaperObject.width() - 1, i, EPD_COLOUR_BLUE);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing rectangles on the display
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

    // drawing a filled rectangle
    Serial.println("Drawing a filled rectangle on the display. You will only see 1 though");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < ePaperObject.height() / 2; i += 3)
    {
        ePaperObject.fillRect(i, i, ePaperObject.width() - i * 2, ePaperObject.height() - i * 2, EPD_COLOUR_YELLOW);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing circles
    Serial.println("Drawing circles on the display");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < max(ePaperObject.width(), ePaperObject.height()) / 2; i += 2)
    {
        ePaperObject.drawCircle(ePaperObject.width() / 2, ePaperObject.height() / 2, i, EPD_COLOUR_ORANGE);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing a filled circle
    Serial.println("Drawing a filled circle on the display. You will only see 1 though");
    ePaperObject.clearDisplay();
    for (int16_t i = max(ePaperObject.width(), ePaperObject.height()) / 2; i > 0; i -= 3)
    {
        ePaperObject.fillCircle(ePaperObject.width() / 2, ePaperObject.height() / 2, i, EPD_COLOUR_BLACK);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing round rectangles
    Serial.println("Drawing round rectangles on the display.");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < ePaperObject.height() / 2 - 2; i += 2)
    {
        ePaperObject.drawRoundRect(i, i, ePaperObject.width() - 2 * i, ePaperObject.height() - 2 * i,
                                   ePaperObject.height() / 4, EPD_COLOUR_GREEN);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing a filled round rectangle
    Serial.println("Drawing a filled round rectangle on the display. You will only see 1 though");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < ePaperObject.height() / 2 - 2; i += 2)
    {
        ePaperObject.fillRoundRect(i, i, ePaperObject.width() - 2 * i, ePaperObject.height() - 2 * i,
                                   ePaperObject.height() / 4, EPD_COLOUR_BLUE);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing triangles
    Serial.println("Drawing triangles on the display.");
    ePaperObject.clearDisplay();
    for (int16_t i = 0; i < max(ePaperObject.width(), ePaperObject.height()) / 2; i += 5)
    {
        ePaperObject.drawTriangle(
            ePaperObject.width() / 2, ePaperObject.height() / 2 - i,
            ePaperObject.width() / 2 - i, ePaperObject.height() / 2 + i,
            ePaperObject.width() / 2 + i, ePaperObject.height() / 2 + i, EPD_COLOUR_RED);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // drawing a filled triangle
    Serial.println("Drawing a filled triangle on the display. You will only see 1 though");
    ePaperObject.clearDisplay();
    for (int16_t i = max(ePaperObject.width(), ePaperObject.height()) / 2; i > 0; i -= 5)
    {
        ePaperObject.fillTriangle(
            ePaperObject.width() / 2, ePaperObject.height() / 2 - i,
            ePaperObject.width() / 2 - i, ePaperObject.height() / 2 + i,
            ePaperObject.width() / 2 + i, ePaperObject.height() / 2 + i, EPD_COLOUR_YELLOW);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // Writing CP437 character set
    Serial.println("Writing CP437 character set on the screen");
    ePaperObject.clearDisplay();
    ePaperObject.setTextSize(1);                  // Normal 1:1 pixel scale
    ePaperObject.setTextColor(EPD_COLOUR_ORANGE); // Draw orange text
    ePaperObject.setCursor(0, 0);                 // Start at top-left corner
    ePaperObject.cp437(true);                     // Use full 256 char 'Code Page 437' font

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for (int16_t i = 0; i < 256; i++)
    {
        if (i == '\n')
            ePaperObject.write(' ');
        else
            ePaperObject.write(i);
    }
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // Writing basic text
    Serial.println("Writing basic text on the screen(CP437)");
    ePaperObject.clearDisplay();

    ePaperObject.setTextSize(1);                 // Normal 1:1 pixel scale
    ePaperObject.setTextColor(EPD_COLOUR_BLACK); // Draw black text
    ePaperObject.setCursor(0, 0);                // Start at top-left corner
    ePaperObject.println("Hello, world!");

    ePaperObject.setTextColor(EPD_COLOUR_GREEN);
    ePaperObject.println(3.141592);

    ePaperObject.setTextSize(2); // Draw 2X-scale text
    ePaperObject.setTextColor(EPD_COLOUR_BLUE);
    ePaperObject.print("0x");
    ePaperObject.println(0xDEADBEEF, HEX);
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // Drawing bitmap on the screen
    Serial.println("Drawing bitmap on the screen");
    ePaperObject.clearDisplay();
    ePaperObject.drawBitmap(
        (ePaperObject.width() - LOGO_WIDTH) / 2,
        (ePaperObject.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, EPD_COLOUR_RED);
    ePaperObject.display();
    ePaperObject.waitForScreenBlocking();

    // waiting for 10 seconds
    delay(10000);

    // Drawing vertical bars of all colours
    Serial.println("Drawing vertical bars of all colours on the screen");
    ePaperObject.clearDisplay();
    ePaperObject.test();
    ePaperObject.waitForScreenBlocking();

    Serial.println("Done");

    // waiting for 20 seconds
    delay(20000);
}