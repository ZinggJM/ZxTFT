// created by Jean-Marc Zingg to be the ZxTFT_ILI9488 class for the ZxTFT library (instead of the GxCTRL_ILI9488 class for the GxTFT library, which doesn't work with SPI)
// code extracts taken from https://github.com/Bodmer/TFT_HX8357
// code extracts taken from https://github.com/adafruit/Adafruit-GFX-Library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//

#ifndef _ZxTFT_ILI9488_H_
#define _ZxTFT_ILI9488_H_

#include <Adafruit_SPITFT.h>
#include "GFXcanvas16T.h"
#include "ZxTFT_GFX.h"

class ZxTFT_ILI9488 : public ZxTFT_GFX
{
  public:
    ZxTFT_ILI9488(int8_t cs_pin, int8_t dc_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    ZxTFT_ILI9488(int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin, int8_t bl_pin = -1);
    ZxTFT_ILI9488(uint16_t width, uint16_t height, SPIClass *spi, int8_t cs_pin, int8_t dc_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    ZxTFT_ILI9488(uint16_t width, uint16_t height, int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    void begin(uint32_t freq);
    void init(uint32_t freq = 0);
    void setRotation(uint8_t r);
    void invertDisplay(boolean i);
    void invert(boolean i);
    void enableDisplay(boolean enable);
    void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void writePixel(int16_t x, int16_t y, uint16_t color);
    //void writePixels(uint16_t *colors, uint32_t len, bool block = true, bool bigEndian = false); // TO BE ADDED
    void writeColor(uint16_t color, uint32_t len);
    void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                       uint16_t color);
    void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  private:
    void _writeCommand16(uint16_t cmd);
    // note: only use for pixel data, RGB888 on ILI9488
    void _writeColor16(uint16_t data, uint32_t n);
    void _writeColor16(const uint16_t* data, uint32_t n);
  private:
    int8_t _bl_pin;
    int8_t _bgr;
};

#endif // _ZxTFT_ILI9488_H_
