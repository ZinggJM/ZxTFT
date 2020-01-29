// created by Jean-Marc Zingg to be the ZxTFT_GFX class for the ZxTFT library
// code extracts taken from https://github.com/adafruit/Adafruit-GFX-Library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//

#ifndef _ZxTFT_GFX_H_
#define _ZxTFT_GFX_H_

#include <Adafruit_SPITFT.h>

class ZxTFT_GFX : public Adafruit_SPITFT
{
  public:
    ZxTFT_GFX(uint16_t w, uint16_t h, int8_t cs, int8_t dc, int8_t mosi, int8_t sck, int8_t rst = -1, int8_t miso = -1);
    ZxTFT_GFX(uint16_t w, uint16_t h, int8_t cs, int8_t dc, int8_t rst = -1);
#if !defined(ESP8266)
    ZxTFT_GFX(uint16_t w, uint16_t h, SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst = -1);
#endif // end !ESP8266
    //ZxTFT_GFX(uint16_t w, uint16_t h, tftBusWidth busWidth, int8_t d0, int8_t wr, int8_t dc, int8_t cs = -1, int8_t rst = -1, int8_t rd = -1);
    // (overridden) virtual methods
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void fillScreen(uint16_t color);
  protected:
    inline void _writeData16(uint16_t data, uint32_t n)
    {
      ZxTFT_GFX::_writeColor16(data, n);
    }
    inline void _writeData16(const uint16_t* data, uint32_t n)
    {
      ZxTFT_GFX::_writeColor16(data, n);
    }
    // note: only use for pixel data, RGB888 on ILI9488
    virtual void _writeColor16(uint16_t data, uint32_t n);
    virtual void _writeColor16(const uint16_t* data, uint32_t n);
};

#endif
