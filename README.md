# ZxTFT : My TFTs using Adafruit_SPITFT

This library supports some TFTs using Adafruit_SPITFT

### Version 0.0.3
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
