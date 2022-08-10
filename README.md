# This library helps [AdafruitGFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) work on the [4.01 inch colour e-paper display by WaveShare](https://www.waveshare.com/4.01inch-e-Paper-F.htm)
> Might work on the [5.65 inch version](https://www.waveshare.com/5.65inch-e-Paper-F.htm) as well. Haven't tested or developed with that in mind. YMMV.

**Due to the slow refresh rate of this screen, the usage of this library is slightly different compared to those which support screens with higher refresh rates**
## Theory
Both of the screens use SPI to communicate(Controller-in-Peripheral-Out pin does not exist) and receive data to display on the screen. 

SPI can either be explicitly initialized(HSPI is used) or can be left up to the library to do, depending on the `begin()` function used. If left up to the library, default pins for HSPI are used for clock, controller-out-peripheral-in. Check 

For a deeper dive into how this display works, [check this out](https://github.com/A223D/colourEpaperWaveshare). 

## Constructor
```c++
Adafruit_4_01_ColourEPaper(int w, int h, int rst_pin, int dc_pin, int busy_pin, bool debug_On);
```
This constructor is used to create the object which represents the screen. You can call functions on this object to interact with the screen. It takes the width and height (in pixels), the MCU pin to which the `reset` pin of the screen is connected to, the MCU pin to which the `DC` pin of the screen is connected to, the MCU pin to which the `Busy` pin of the screen is connected to, and a `bool` which enables or disables debugging statements during operation. 

## Functions
* **Begin (two definitions)**
	```c++
	bool begin(SPIClass *spi_ptr, int cs_pin);
	```
	The above declaration expects an SPI bus on the ESP32 to be initialized and then it's object to be passed to it, along with MCU pin which is connected to the in `CS` pin on the screen. 

