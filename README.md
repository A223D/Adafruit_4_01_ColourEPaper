# This library helps [AdafruitGFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) work on the [4.01 inch colour e-paper display by WaveShare](https://www.waveshare.com/4.01inch-e-Paper-F.htm)
> Might work on the [5.65 inch version](https://www.waveshare.com/5.65inch-e-Paper-F.htm) as well. Haven't tested or developed with that in mind. YMMV.

**Due to the slow refresh rate of this screen, the usage of this library is slightly different compared to those which support screens with higher refresh rates**
## Theory
### Communication
Both of the screens use SPI to communicate(Controller-in-Peripheral-Out pin does not exist) and receive data to display on the screen. 

The SPI bus(HSPI) is internally initialized and used. It is possible to either use the default pin mapping for the SPI interface or user-defined pins through the GPIO mux, depending on the `begin` function used. The SPI bus operates at 2 MHz. [Check the documentation provided here to see how the SPI buses work on the ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html).

### Frame Buffer
There also exists an internal frame buffer which consumes half the number of pixels in bytes. (1 byte holds 2 pixels). For this display, the memory allocated is `640*400/2` = 1,28,000 bytes.

### Colours
The following colours are defined internally. Each pixel can only be a single colour. A pixel cannot be a mixture of 2 colours or a specific brightness of some colour.
```c++
#define  EPD_COLOUR_BLACK  0
#define  EPD_COLOUR_WHITE  1
#define  EPD_COLOUR_GREEN  2
#define  EPD_COLOUR_BLUE  3
#define  EPD_COLOUR_RED  4
#define  EPD_COLOUR_YELLOW  5
#define  EPD_COLOUR_ORANGE  6
#define  EPD_COLOUR_COFFEE  7
```

The "Coffee" colour is not officially defined, but it still works. 

> For a deeper dive into how this display works, [check this out](https://github.com/A223D/colourEpaperWaveshare). 



## Constructor
```c++
Adafruit_4_01_ColourEPaper(int w, int h, int rst_pin, int dc_pin, int busy_pin, bool debug_On);
```
This constructor is used to create the object which represents the screen. You can call functions on this object to interact with the screen. It takes the width and height (in pixels), the MCU pin to which the `reset` pin of the screen is connected to, the MCU pin to which the `DC` pin of the screen is connected to, the MCU pin to which the `Busy` pin of the screen is connected to, and a `bool` which enables or disables debugging statements during operation. 

## Functions
### Library Functions
* **Begin (two definitions, only use one)**
  **First One**
	```c++
	//first definition
	Adafruit_4_01_ColourEPaper::begin(void);
	```
	The above declaration uses the HSPI SPI bus on the ESP32 with the default pins. Everything is initialized internally, and the following pins are used by default, [according to the ESP32 SPI docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html):
	| Pin Description | Pin Number|
	| :- | :- |
	| CIPO | (not used) |
	| COPI| 13|
	|SCLK|14|
	|CS/SS|15|
	
	The frame buffer is also allocated, all white pixels are written to it, and some initialization commands are also sent to the screen. There is an example called `defaultPins` which demonstrates how to use this definition of `begin`. 
	
	**Second One**
	```c++
	//second definition
	bool Adafruit_4_01_ColourEPaper::begin(int sclk_pin, int copi_pin, int cs_pin);
	```
	The above declaration uses the HSPI SPI bus on the ESP32 with the pins that are provided as arguments. The frame buffer is also allocated, all white pixels are written to it, and some initialization commands are also sent to the screen. There is an example called `customPins`, which demonstrates how to use this definition.
	
* **Display**
	```c++
	void Adafruit_4_01_ColourEPaper::display(void);
	```
	This function transfers the internal frame buffer to the screen, and triggers a screen refresh, which takes about 30 seconds to complete. The `waitForScreenBlocking()` function must be used immediately after `display()`. Alternatively, the `checkBusy()` and `sendPOFandLeaveSPI()` functions can be called after some time to do something while the screen is refreshing. However, one the option **must** be used after `display()` to power off the display refreshing mechanism and release the SPI bus for other potential uses. If this is not done, power will be wasted keeping the refreshing mechanism turned on and colours may not be accurate, according to the developer's experience. Check their individual descriptions for more information. Examples in this library use both approaches for ending a screen writing procedure.

* **Clear Display**
	```c++
	void Adafruit_4_01_ColourEPaper::clearDisplay(void);
	```
	This function writes all-white pixels in the complete frame buffer, but does not send it to the screen. Use `display()` and one of the two mentioned methods to complete the screen write procedure.

* **Draw Pixel**
	```c++
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	```
	This function draws 1 pixel of colour `color` to the frame buffer. Use `display()` and one of the two mentioned methods to complete the screen write procedure.

* **Test Function**
	```c++
	void Adafruit_4_01_ColourEPaper::test(void);
	```
	This function is provided to test if a display works properly. It bypasses the frame buffer and directly writes vertical bars of each colour to the screen. Use one of the two mentioned methods to complete the screen write procedure.

* **Wait For Screen (Blocking)**
	```c++
	void Adafruit_4_01_ColourEPaper::waitForScreenBlocking(void);
	```
	This function blocks(stops program execution at this point) till the screen has finished updating. And then sends commands which power off the screen-refreshing mechanism inside the display and then releases the SPI bus so it can be used for other purposes. Use this function after `display()`.

* **Check Busy (Non-blocking)**
	```c++
	bool checkBusy(void);
	```
	This function checks if the screen is currently busy refreshing(takes ~30 seconds) in a non-blocking manner(program continues execution whether `true` or `false` is returned). This function is provided so that other work can be done on the ESP32 while the screen is busy updating. This function can be called periodically to check if the screen is done updating, and if so, use `sendPOFandLeaveSPI()` to power off the screen refreshing mechanism and release the SPI bus. Here is how this could be done:
	```c++
	//write to the frame buffer, then display it

	ePaperObject.display();
	//go do something
	if(!ePaperObject.checkBusy()){
		ePaperObject.sendPOFandLeaveSPI();
	}
	//if still busy, do some other work again
	if(!ePaperObject.checkBusy()){
		ePaperObject.sendPOFandLeaveSPI();
	}
	//more work can be done while screen is refreshing

	//if there is no more work to be done, 
	//just wait till screen is done working, 
	//and then power off refreshing mechanism
	//and release SPI bus
	while(ePaperObject.checkBusy());
	ePaperObject.sendPOFandLeaveSPI();

	//could have also used this here as well:
	//ePaperObject.waitForScreenBlocking()

	```
* **Power-Off Refreshing Mechanism and Release SPI Bus**
	```c++
	Adafruit_4_01_ColourEPaper::sendPOFandLeaveSPI(void);
	```
	This function sends commands to the screen which power off the refreshing mechanism, and release the SPI bus so it can work with other peripherals. Use it in conjunction with `checkBusy()` to know when the screen is ready for this. 
	
### AdafruitGFX Functions (drawing functions)

Apart from the functions in the library, all the functions in the `AdafruitGFX` library can be used on the object created by the constructor of this library. [Here is a tutorial on AdafruitGFX](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview). As a reminder, the information about colour mentioned in the `Coordinate System and Units` section is not applicable here, since each pixel can only be one of the specific colours shown above. [The graphics functions are provided here](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives).
There is an example provided which demonstrates `AdafruitGFX` functionality called `modifiedAdafruitGFXExample`, which is modified to account for the slow screen refresh. This is based on the standard `AdafruitGFX` example provided with their other display-specific libraries which use `AdafruitGFX`.
