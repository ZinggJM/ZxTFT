# ZxTFT : My TFTs using Adafruit_SPITFT

This library supports some TFTs using Adafruit_SPITFT

### Version 1.0.1
- added suport for ILI9488 SPI TFT, e.g. https://www.aliexpress.com/item/32908809356.html
- caution: this board is for 3.3V supply AND data lines
- tested with ESP32, ESP8266, STM32F103 BluePill, Arduino Due, Arduino Pro Mini 3.3V
#### Version 1.0.0
- added base class ZxTFT_GFX, enhances Adafruit_SPITFT for ESP8266, ESP32
- replaced RPi SPI kludge handling for ILI9486, better performance
- added method setSpiKludge() for ILI9486
- rpi_spi16_mode is on for ILI9486 per default, switch off by setSpiKludge(false)
#### Version 0.0.3
- added support for ILI9486 SPI TFT
- works with my "3.5" TFT LCD Touch Screen Module 320 x 480 SPI RGB Display For Raspberry Pi B B+"
- https://www.aliexpress.com/item/32661117216.html
- only tested on ESP8266 Wemos D1 R2 and Arduino Due
- if your TFT shows wrong colors, use invertDisplay(false), my TFT uses BGR
#### Version 0.0.2
- fixed rotation for SSD1283A (rendering canvas ok for all 4 rotations)
- added template class GFXcanvas16T, uses dynamic memory space instead of heap space
#### Version 0.0.1
- preliminary version
- supports SSD1283A
- works with my "Transflective Display Module LCD Display DIY SPI Serial Port 130*130 Communicate for Arduino"
- https://www.aliexpress.com/item/4000116854157.html
- only tested with HW SPI.
