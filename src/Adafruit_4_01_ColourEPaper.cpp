#include "Adafruit_4_01_ColourEPaper.h"

Adafruit_4_01_ColourEPaper::Adafruit_4_01_ColourEPaper(int w, int h, int rst_pin, int dc_pin, int busy_pin, bool debug_On) : Adafruit_GFX(w, h), buffer1(NULL), buffer2(NULL)
{
    dcPin = dc_pin;
    busyPin = busy_pin;
    rstPin = rst_pin;
    debugOn = debug_On;
    if (debugOn)
    {
        Serial.println("Setting Constructor pinModes");
    }
    pinMode(dcPin, OUTPUT);
    pinMode(busyPin, INPUT);
    pinMode(rstPin, OUTPUT);

    spiSettingsObject = SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0);
}

Adafruit_4_01_ColourEPaper::~Adafruit_4_01_ColourEPaper()
{
    free(buffer1);
    free(buffer2);

    delete spi;
}

bool Adafruit_4_01_ColourEPaper::begin(void)
{
    // pin and spi pointer allocation
    spi = new SPIClass(HSPI);

    if (debugOn)
    {
        Serial.println("Setting begin pinModes(csPin stuff done later)");

        Serial.print("rstPin\t");
        Serial.println(rstPin);
        Serial.print("dcPin\t");
        Serial.println(dcPin);
        Serial.print("busyPin\t");
        Serial.println(busyPin);
    }
    // pinModes
    // csPin stuff is done later since automatic SPI initialization occurs at spi->begin()

    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(busyPin, INPUT);

    // SPI init

    if (debugOn)
    {
        Serial.println("SPI init");
    }
    spi->begin();

    //CsPin init and pinMode
    csPin = spi->pinSS();
    pinMode(csPin, OUTPUT);
    if (debugOn)
    {
        Serial.print("csPin\t");
        Serial.println(csPin);
    }


    spi->beginTransaction(spiSettingsObject);

    // everything below can be it's own function
    return frameBufferAndInit();
}

bool Adafruit_4_01_ColourEPaper::begin(int sclk_pin, int copi_pin, int cs_pin)
{
    // pin and spi pointer allocation
    csPin = cs_pin;
    spi = new SPIClass(HSPI);

    // pinModes
    pinMode(csPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(busyPin, INPUT);

    // SPI init

    if (debugOn)
    {
        Serial.println("SPI init");
    }
    spi->begin(sclk_pin, -1, copi_pin, cs_pin);
    spi->beginTransaction(spiSettingsObject);

    return frameBufferAndInit();
}

bool Adafruit_4_01_ColourEPaper::frameBufferAndInit()
{
    // framebuffer allocation
    if (debugOn)
    {
        Serial.println("Let's allocate some memory");
    }

    // Apparently doesn't work when 1 large buffer is allocated
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
        Serial.println("Setting everything to 1");
    }
    memset(buffer1, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white
    memset(buffer2, 0x11, (WIDTH * HEIGHT / 2) / 2); // fill everything with white

    // send initialization commands to screen
    if (debugOn)
    {
        Serial.println("Resetting screen");
    }
    resetScreen();
    if (!(busyHigh()))
    {
        if (debugOn)
        {
            Serial.println("Busy High Failed");
        }
    }

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

    spi->endTransaction();

    if (debugOn)
    {
        Serial.println("Init complete");
    }

    return true;
}

void Adafruit_4_01_ColourEPaper::display(void)
{
    spi->beginTransaction(spiSettingsObject);
    writeSPI(0x61, true); // Set Resolution setting
    writeSPI(0x02, false);
    writeSPI(0x80, false);
    writeSPI(0x01, false);
    writeSPI(0x90, false);

    writeSPI(0x10, true);
    if (debugOn)
    {
        Serial.println("Writing to GDDR");
    }

    for (long i = 0; i < (WIDTH * HEIGHT / 2) / 2; i++)
    {
        writeSPI(buffer1[i], false);
    }

    for (long i = 0; i < (WIDTH * HEIGHT / 2) / 2; i++)
    {
        writeSPI(buffer2[i], false);
    }
    if (debugOn)
    {
        Serial.println("Wrote stuff to GDDR");
        // trigger gddr to screen
        Serial.println("Triggering send to screen.");
    }
    writeSPI(0x04, true);
    if (!(busyHigh()))
    {
        Serial.println("BusyHigh1 failed");
    }
    writeSPI(0x12, true);

    // either block until screen finishes (waitForScreenBlocking) or do something else and then send POF + endtransaction yourself once busy is high (checkBusy + sendPOFandLeaveSPI)
}
void Adafruit_4_01_ColourEPaper::clearDisplay(void)
{
    if (debugOn)
    {
        Serial.println("writing all white to memory");
    }
    memset(buffer1, 0x11, (WIDTH * HEIGHT / 2) / 2);
    memset(buffer2, 0x11, (WIDTH * HEIGHT / 2) / 2);
}

void Adafruit_4_01_ColourEPaper::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if (x > WIDTH - 1 || x < 0 || y > HEIGHT - 1 || y < 0)
    {
        return;
    }
    long pixelNum = (y * WIDTH) + x;
    bool after = pixelNum % 2; // if remainder is 0, most significant nibble, if remainder is 1, least significant nibble
    long byteNum = pixelNum / 2;
    bool secondBuffer = false;
    if (debugOn)
    {
        Serial.print("Master Pixel number:\t");
        Serial.println(pixelNum);
    }

    if (pixelNum < WIDTH * (HEIGHT / 2))
    {
        if (debugOn)
        {
            Serial.println("Buffer 1");
        }
        secondBuffer = false;
    }
    else
    {
        if (debugOn)
        {
            Serial.println("Buffer 2");
        }
        secondBuffer = true;
        pixelNum -= 128000;
    }

    after = pixelNum % 2;
    byteNum = pixelNum / 2;

    if (debugOn)
    {
        Serial.print("Pixel number:\t");
        Serial.println(pixelNum);
        Serial.print("Byte number:\t");
        Serial.println(byteNum);
        Serial.print("Position:\t");
        if (after)
        {
            Serial.println("After");
        }
        else
        {
            Serial.println("Before");
        }
    }

    // at this point, we know which buffer, which byte, and position
    // now we have to locate the byte, and edit it
    if (!secondBuffer)
    {
        // if first buffer
        if (after)
        {
            char newByte = buffer1[byteNum]; // get the byte
            newByte &= 0xF0;                 // clear the latter half for new colour
            newByte |= color;
            buffer1[byteNum] = newByte;
        }
        else
        {
            char newByte = buffer1[byteNum];
            newByte &= 0xF;
            newByte |= (color << 4);
            buffer1[byteNum] = newByte;
        }
    }
    else
    {
        // if second buffer
        if (after)
        {
            char newByte = buffer2[byteNum];
            newByte &= 0xF0;
            newByte |= color;
            buffer2[byteNum] = newByte;
        }
        else
        {
            char newByte = buffer2[byteNum];
            newByte &= 0xF;
            newByte |= (color << 4);
            buffer2[byteNum] = newByte;
        }
    }
}

void Adafruit_4_01_ColourEPaper::test(void)
{
    // used for testing begin function
    // This function writes bars of each colour to the screen. Use blocking wait function or do it manually with check busy and POF+SPIShutdown
    spi->beginTransaction(spiSettingsObject);
    writeSPI(0x61, true); // Set Resolution setting
    writeSPI(0x02, false);
    writeSPI(0x80, false);
    writeSPI(0x01, false);
    writeSPI(0x90, false);
    writeSPI(0x10, true);

    for (int j = 0; j < 400; j++)
    {

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x0, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x11, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x22, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x33, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x44, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x55, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x66, false);
        }

        for (int i = 0; i < 40; i++)
        {
            writeSPI(0x77, false);
        }
    }
    if (debugOn)
    {
        Serial.println("Sent all clear commands. Refreshing screen");
    }
    writeSPI(0x04, true);
    if (!(busyHigh()))
    {
        if (debugOn)
        {
            Serial.println("BusyHigh1 failed");
        }
    }
    writeSPI(0x12, true);

    // either block until screen finishes (waitForScreenBlocking) or do something else and then send POF + endtransaction yourself once busy is high (checkBusy + sendPOFandLeaveSPI)
}

void Adafruit_4_01_ColourEPaper::writeSPI(uint8_t something, bool command)
{
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

void Adafruit_4_01_ColourEPaper::resetScreen(void)
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

void Adafruit_4_01_ColourEPaper::waitForScreenBlocking(void)
{
    if (debugOn)
    {
        Serial.println("Blocking wait for screen to finish updating");
    }
    while (!digitalRead(busyPin))
        ;
    sendPOFandLeaveSPI();
}

void Adafruit_4_01_ColourEPaper::sendPOFandLeaveSPI(void)
{
    if (debugOn)
    {
        Serial.println("Shutting off and leaving SPI");
    }
    writeSPI(0x02, true);
    if (!(busyLow()))
    {
        if (debugOn)
        {
            Serial.println("BusyLow1 failed");
        }
    }
    spi->endTransaction();
}

bool Adafruit_4_01_ColourEPaper::checkBusy(void)
{
    if (debugOn)
    {
        Serial.println("Blocking wait for busy to be high");
    }
    return !(digitalRead(busyPin));
}