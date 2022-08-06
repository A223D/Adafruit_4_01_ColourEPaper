#ifndef _Adafruit_4_01_ColourEPaper
#define _Adafruit_4_01_ColourEPaper

#include "Adafruit_GFX.h"
#include <SPI.h>

#define EPD_COLOUR_BLACK 0
#define EPD_COLOUR_WHITE 1
#define EPD_COLOUR_GREEN 2
#define EPD_COLOUR_BLUE  3
#define EPD_COLOUR_RED   4
#define EPD_COLOUR_YELLOW 5
#define EPD_COLOUR_ORANGE 6
#define EPD_COLOUR_COFFEE 7


class Adafruit_4_01_ColourEPaper : public Adafruit_GFX{
    public:
    Adafruit_4_01_ColourEPaper(uint8_t w, uint8_t h, int mosi_pin, int sclk_pin, int rst_pin, int cs_pin, int dc_pin, int busyPin);
    ~Adafruit_4_01_ColourEPaper(void);


    void display(void);
    void init(void);
    void clearDisplay(void);
    void drawPixel(int x, int y, int colour);


    protected:
    SPIClass *spi;
    uint8_t *buffer;
    int mosiPin;
    int clkPin;
    int csPin;
    int rstPin;
    int dcPin;
    int busyPin;

};



#endif _Adafruit_4_01_ColourEPaper