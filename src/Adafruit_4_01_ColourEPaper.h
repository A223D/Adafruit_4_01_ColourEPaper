#ifndef _Adafruit_4_01_ColourEPaper
#define _Adafruit_4_01_ColourEPaper

#include <Adafruit_GFX.h>
#include <SPI.h>

#define EPD_COLOUR_BLACK 0
#define EPD_COLOUR_WHITE 1
#define EPD_COLOUR_GREEN 2
#define EPD_COLOUR_BLUE 3
#define EPD_COLOUR_RED 4
#define EPD_COLOUR_YELLOW 5
#define EPD_COLOUR_ORANGE 6
#define EPD_COLOUR_COFFEE 7
#define BUSY_THRESH 5000
#define SPI_SPEED 2000000

class Adafruit_4_01_ColourEPaper : public Adafruit_GFX
{
public:
    Adafruit_4_01_ColourEPaper(int w, int h, int rst_pin, int dc_pin, int busy_pin, bool debug_On);
    ~Adafruit_4_01_ColourEPaper();

    bool begin(void);
    bool begin(int sclk_pin, int copi_pin, int cs_pin);
    void display(void);
    void clearDisplay(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void test(void);
    void waitForScreenBlocking(void);
    void sendPOFandLeaveSPI(void);
    bool checkBusy(void);

protected:
    bool frameBufferAndInit();
    void writeSPI(uint8_t something, bool command);
    void resetScreen(void);
    bool busyHigh(void);
    bool busyLow(void);
    SPIClass *spi;
    SPISettings spiSettingsObject;
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    int csPin;
    int rstPin;
    int dcPin;
    int busyPin;
    bool debugOn = false;
    bool needToDeleteSPI;
};

#endif