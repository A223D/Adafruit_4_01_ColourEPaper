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
        Serial.println("Setting everything to 0 and pinmodes");
    }
    memset(buffer1, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white
    memset(buffer2, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white

    pinMode(csPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(busyPin, OUTPUT);
    if (debugOn)
    {
        Serial.println("SPI init");
    }
    spi->begin();
    spi->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    // send initialization commands to screen
    if (debugOn)
    {
        Serial.println("Resetting screen");
    }
    resetSceen();
    busyHigh();

    if (debugOn)
    {
        Serial.println("Reset complete");
    }

    writeSPI(0x00, true);
    writeSPI(0x2F, false);
    writeSPI(0x00, false);

    writeSPI(0x01, true);
    writeSPI(0x37, false); // trying default of 00001000 orig 0x37
    writeSPI(0x01, false); // trying default of 0x01, orig 0x00
    writeSPI(0x05, false);
    writeSPI(0x05, false);

    writeSPI(0x03, true);
    writeSPI(0x00, false);

    writeSPI(0x06, true);
    writeSPI(0xC7, false);
    writeSPI(0xC7, false);
    writeSPI(0x1D, false);

    writeSPI(0x41, true);
    writeSPI(0x00, false);

    writeSPI(0x50, true);
    writeSPI(0x37, false);

    writeSPI(0x60, true);
    writeSPI(0x22, false);

    writeSPI(0x61, true);
    writeSPI(0x02, false);
    writeSPI(0x80, false);
    writeSPI(0x01, false);
    writeSPI(0x90, false);

    writeSPI(0xE3, true);
    writeSPI(0xAA, false);

    if (debugOn)
    {
        Serial.println("Init complete");
    }

    return true;
}

void Adafruit_4_01_ColourEPaper::display(void)
{
    // Serial.println("Not implemented yet");
    writeSPI(0x61, true); // Set Resolution setting
    writeSPI(0x02, false);
    writeSPI(0x80, false);
    writeSPI(0x01, false);
    writeSPI(0x90, false);

    writeSPI(0x10, true);
    // write to gddr

    for (long i = 0; i < (WIDTH * HEIGHT / 2) / 2; i++)
    {
        writeSPI(buffer1[i], false);
    }

    for (long i = 0; i < (WIDTH * HEIGHT / 2) / 2; i++)
    {
        writeSPI(buffer2[i], false);
    }

    //trigger gddr to screen
    writeSPI(0x04, true);
    busyHigh();
    writeSPI(0x12, true);
    busyHigh();
    writeSPI(0x02, true);
    busyHigh();
}
void Adafruit_4_01_ColourEPaper::clearDisplay(void)
{
    if (debugOn)
    {
        Serial.println("writing ");
    }
    memset(buffer1, 0, (WIDTH * HEIGHT / 2) / 2);
    memset(buffer2, 0, (WIDTH * HEIGHT / 2) / 2);
    // Serial.println("Not implemented yet");
}
void Adafruit_4_01_ColourEPaper::drawPixel(int x, int y, int colour)
{
    Serial.println("Not implemented yet");
}

void Adafruit_4_01_ColourEPaper::test(void)
{
    // used for testing begin function
    // just write rainbow code to the screen after begin command is complete
    writeSPI(0x61, true); // Set Resolution setting
    writeSPI(0x02, false);
    writeSPI(0x80, false);
    writeSPI(0x01, false);
    writeSPI(0x90, false);
    writeSPI(0x10, true);

    for (int i = 0; i < WIDTH / 2; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            writeSPI(0x11, false);
        }
    }
    Serial.println("Sent all clear commands. Refreshing screen");

    writeSPI(0x04, true);
    busyHigh();
    writeSPI(0x12, true);
    busyHigh();
    writeSPI(0x02, true);
    busyLow();
    delay(500);
}

void Adafruit_4_01_ColourEPaper::writeSPI(uint8_t something, bool command)
{
    // Serial.println("Not yet implemented");
    if (command)
    {
        digitalWrite(dcPin, LOW);
    }
    else
    {
        digitalWrite(dcPin, HIGH);
    }

    digitalWrite(csPin, LOW);

    spi->transfer(something);

    digitalWrite(csPin, HIGH);
}

void Adafruit_4_01_ColourEPaper::resetSceen(void)
{
    digitalWrite(rstPin, HIGH);
    delay(200);
    digitalWrite(rstPin, LOW);
    delay(1);
    digitalWrite(rstPin, HIGH);
    delay(200);
}

bool Adafruit_4_01_ColourEPaper::busyHigh()
{
    unsigned long endTime = millis() + BUSY_THRESH;
    while (!digitalRead(busyPin) && (millis() < endTime))
        ;

    if (digitalRead(busyPin) == 0)
    {
        return false;
    }

    return true;
}

bool Adafruit_4_01_ColourEPaper::busyLow()
{
    unsigned long endTime = millis() + BUSY_THRESH;
    while (digitalRead(busyPin) && (millis() < endTime))
        ;

    if (digitalRead(busyPin) == 1)
    {
        return false;
    }

    return true;
}