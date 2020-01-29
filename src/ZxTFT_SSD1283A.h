// created by Jean-Marc Zingg to be a standalone ZxTFT_SSD1283A library (instead of the GxCTRL_SSD1283A class for the GxTFT library)
// code extracts taken from https://github.com/lcdwiki/LCDWIKI_SPI
// code extracts taken from https://github.com/adafruit/Adafruit-GFX-Library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//

#ifndef _ZxTFT_SSD1283A_H_
#define _ZxTFT_SSD1283A_H_

#include <Adafruit_SPITFT.h>
#include "GFXcanvas16T.h"
// comment out to use only Adafruit_SPITFT
//#include "ZxTFT_GFX.h"

#ifdef _ZxTFT_GFX_H_
#define SPI_GFX_Class ZxTFT_GFX
#else
#define SPI_GFX_Class Adafruit_SPITFT
#endif

class ZxTFT_SSD1283A : public SPI_GFX_Class
{
  public:
    ZxTFT_SSD1283A(int8_t cs_pin, int8_t dc_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    ZxTFT_SSD1283A(int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin, int8_t bl_pin = -1);
    ZxTFT_SSD1283A(uint16_t width, uint16_t height, SPIClass *spi, int8_t cs_pin, int8_t dc_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    ZxTFT_SSD1283A(uint16_t width, uint16_t height, int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin = -1, int8_t bl_pin = -1);
    void begin(uint32_t freq);
    void init(uint32_t freq = 0);
    void setRotation(uint8_t r);
    void invertDisplay(boolean i);
    void invert(boolean i);
    void enableDisplay(boolean enable);
    void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  private:
    void _writeCommandData16(uint8_t cmd, uint16_t data);
    void _init_table16(const void *table, int16_t size);
  private:
    int8_t _bl_pin;
    uint16_t _inversion_bit;
};

#endif // _ZxTFT_SSD1283A_H_
