#include "Adafruit_4_01_ColourEPaper.h"

Adafruit_4_01_ColourEPaper::Adafruit_4_01_ColourEPaper(int w, int h, SPIClass *spi_ptr, int rst_pin, int cs_pin, int dc_pin, int busy_pin) : Adafruit_GFX(w, h), spi(spi_ptr ? spi_ptr : &SPI), buffer1(NULL), buffer2(NULL)
{
    dcPin = dc_pin;
    csPin = cs_pin;
    busyPin = busy_pin;
}
Adafruit_4_01_ColourEPaper::Adafruit_4_01_ColourEPaper(int w, int h, SPIClass *spi_ptr, int rst_pin, int cs_pin, int dc_pin, int busy_pin, bool debug_On) : Adafruit_GFX(w, h), spi(spi_ptr ? spi_ptr : &SPI), buffer1(NULL), buffer2(NULL)
{
    dcPin = dc_pin;
    csPin = cs_pin;
    busyPin = busy_pin;
    debugOn = debug_On;
}

bool Adafruit_4_01_ColourEPaper::begin(void)
{
    if (debugOn)
    {
        Serial.println("Let's allocate some memory");
    }
    buffer1 = (char *)malloc((WIDTH * HEIGHT / 2) / 2);
    buffer2 = (char *)malloc((WIDTH * HEIGHT / 2) / 2);

    if (buffer1 == NULL || buffer2 == NULL)
    {
        if (debugOn)
        {
            Serial.println("Memory not allocated");
        }
        return false;
    }
    if (debugOn)
    {
        Serial.println("Setting everything to 0");
    }
    memset(buffer1, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white
    memset(buffer2, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white

    pinMode(csPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(busyPin, OUTPUT);

    // send initialization commands to screen

    return true;
}

void Adafruit_4_01_ColourEPaper::display(void)
{
    Serial.println("Not implemented yet");
}
void Adafruit_4_01_ColourEPaper::clearDisplay(void)
{
    if (debugOn)
    {
        Serial.println("writing ");
    }
    memset(buffer1, 0, (WIDTH * HEIGHT / 2) / 2);
    memset(buffer2, 0, (WIDTH * HEIGHT / 2) / 2);
    Serial.println("Not implemented yet");
}
void Adafruit_4_01_ColourEPaper::drawPixel(int x, int y, int colour)
{
    Serial.println("Not implemented yet");
}

void Adafruit_4_01_ColourEPaper::test(void)
{
    // used for testing begin function
    // just write rainbow code to the screen
}

void Adafruit_4_01_ColourEPaper::writeSPI(uint8_t something)
{
    Serial.println("Not yet implemented");
}