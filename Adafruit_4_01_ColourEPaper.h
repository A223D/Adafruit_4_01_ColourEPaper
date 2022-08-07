#ifndef _Adafruit_4_01_ColourEPaper
#define _Adafruit_4_01_ColourEPaper

#include "Adafruit_GFX.h"
#include <SPI.h>

#define EPD_COLOUR_BLACK 0
#define EPD_COLOUR_WHITE 1
#define EPD_COLOUR_GREEN 2
#define EPD_COLOUR_BLUE 3
#define EPD_COLOUR_RED 4
#define EPD_COLOUR_YELLOW 5
#define EPD_COLOUR_ORANGE 6
#define EPD_COLOUR_COFFEE 7

class Adafruit_4_01_ColourEPaper : public Adafruit_GFX
{
public:
    Adafruit_4_01_ColourEPaper(int w, int h, SPIClass *spi_ptr, int rst_pin, int cs_pin, int dc_pin, int busy_pin);
    Adafruit_4_01_ColourEPaper(int w, int h, SPIClass *spi_ptr, int rst_pin, int cs_pin, int dc_pin, int busy_pin, bool debug_On);
    ~Adafruit_4_01_ColourEPaper(void);

    bool begin(void);
    void display(void);
    void init(void);
    void clearDisplay(void);
    void drawPixel(int x, int y, int colour);

protected:
    void writeSPI(uint8_t something);
    void test(void);
    SPIClass *spi;
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    int csPin;
    int rstPin;
    int dcPin;
    int busyPin;
    bool debugOn = false;
};

#endif _Adafruit_4_01_ColourEPaper