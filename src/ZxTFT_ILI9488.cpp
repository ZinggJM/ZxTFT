// created by Jean-Marc Zingg to be the ZxTFT_ILI9488 class for the ZxTFT library (instead of the GxCTRL_ILI9488 class for the GxTFT library, which doesn't work with SPI)
// code extracts taken from https://github.com/Bodmer/TFT_HX8357
// code extracts taken from https://github.com/adafruit/Adafruit-GFX-Library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//

#include "ZxTFT_ILI9488.h"

#define SPI_SPEED 40000000

#define ILI9488_CASET 0x2A
#define ILI9488_PASET 0x2B
#define ILI9488_RAMWR 0x2C
#define ILI9488_RAMRD 0x2E
#define ILI9488_MADCTL 0x36
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

ZxTFT_ILI9488::ZxTFT_ILI9488(int8_t cs_pin, int8_t dc_pin, int8_t rst_pin, int8_t bl_pin) :
#if defined(ESP8266)
  ZxTFT_GFX(320, 480, cs_pin, dc_pin, rst_pin)
#else
  ZxTFT_GFX(320, 480, &SPI, cs_pin, dc_pin, rst_pin)
#endif
{
  _bl_pin = bl_pin;
  _bgr = MADCTL_BGR;
}

ZxTFT_ILI9488::ZxTFT_ILI9488(int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin, int8_t bl_pin) :
  ZxTFT_GFX(320, 480, cs_pin, dc_pin, mosi_pin, sclk_pin, rst_pin, -1)
{
  _bl_pin = bl_pin;
  _bgr = MADCTL_BGR;
}

ZxTFT_ILI9488::ZxTFT_ILI9488(uint16_t width, uint16_t height,
                             SPIClass *spi, int8_t cs_pin, int8_t dc_pin, int8_t rst_pin, int8_t bl_pin) :
#if defined(ESP8266)
  ZxTFT_GFX(width, height, cs_pin, dc_pin, rst_pin)
#else
  ZxTFT_GFX(width, height, spi, cs_pin, dc_pin, rst_pin)
#endif
{
  (void) spi;
  _bl_pin = bl_pin;
  _bgr = MADCTL_BGR;
}

ZxTFT_ILI9488::ZxTFT_ILI9488(uint16_t width, uint16_t height,
                             int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin, int8_t bl_pin) :
  ZxTFT_GFX(width, height, cs_pin, dc_pin, mosi_pin, sclk_pin, rst_pin, -1)
{
  _bl_pin = bl_pin;
  _bgr = MADCTL_BGR;
}

void ZxTFT_ILI9488::begin(uint32_t freq)
{
  init(freq);
}

void ZxTFT_ILI9488::init(uint32_t freq)
{
  Serial.println("init");
  if (!freq) freq = SPI_SPEED;
  initSPI(freq);
  startWrite();
#if 1
  writeCommand(0xE0); // Positive Gamma Control
  spiWrite(0x00);
  spiWrite(0x03);
  spiWrite(0x09);
  spiWrite(0x08);
  spiWrite(0x16);
  spiWrite(0x0A);
  spiWrite(0x3F);
  spiWrite(0x78);
  spiWrite(0x4C);
  spiWrite(0x09);
  spiWrite(0x0A);
  spiWrite(0x08);
  spiWrite(0x16);
  spiWrite(0x1A);
  spiWrite(0x0F);

  writeCommand(0XE1); // Negative Gamma Control
  spiWrite(0x00);
  spiWrite(0x16);
  spiWrite(0x19);
  spiWrite(0x03);
  spiWrite(0x0F);
  spiWrite(0x05);
  spiWrite(0x32);
  spiWrite(0x45);
  spiWrite(0x46);
  spiWrite(0x04);
  spiWrite(0x0E);
  spiWrite(0x0D);
  spiWrite(0x35);
  spiWrite(0x37);
  spiWrite(0x0F);

  writeCommand(0XC0); // Power Control 1
  spiWrite(0x17);
  spiWrite(0x15);

  writeCommand(0xC1); // Power Control 2
  spiWrite(0x41);

  writeCommand(0xC5); // VCOM Control
  spiWrite(0x00);
  spiWrite(0x12);
  spiWrite(0x80);

  writeCommand(ILI9488_MADCTL); // Memory Access Control
  spiWrite(0x48);          // MX, BGR

  writeCommand(0x3A); // Pixel Interface Format
  spiWrite(0x66);  // 18 bit colour for SPI

  writeCommand(0xB0); // Interface Mode Control
  spiWrite(0x00);

  writeCommand(0xB1); // Frame Rate Control
  spiWrite(0xA0);

  writeCommand(0xB4); // Display Inversion Control
  spiWrite(0x02);

  writeCommand(0xB6); // Display Function Control
  spiWrite(0x02);
  spiWrite(0x02);
  spiWrite(0x3B);

  writeCommand(0xB7); // Entry Mode Set
  spiWrite(0xC6);

  writeCommand(0xF7); // Adjust Control 3
  spiWrite(0xA9);
  spiWrite(0x51);
  spiWrite(0x2C);
  spiWrite(0x82);

  writeCommand(0x11);  //Exit Sleep
  delay(120);

  writeCommand(0x29);  //Display on
  delay(25);
#else
  writeCommand(0x3A);
  spiWrite(0x55);  // use 16 bits per pixel color
  writeCommand(0x36);
  spiWrite(0x48);  // MX, BGR == rotation 0
  // PGAMCTRL(Positive Gamma Control)
  writeCommand(0xE0);
  spiWrite(0x0F);
  spiWrite(0x1F);
  spiWrite(0x1C);
  spiWrite(0x0C);
  spiWrite(0x0F);
  spiWrite(0x08);
  spiWrite(0x48);
  spiWrite(0x98);
  spiWrite(0x37);
  spiWrite(0x0A);
  spiWrite(0x13);
  spiWrite(0x04);
  spiWrite(0x11);
  spiWrite(0x0D);
  spiWrite(0x00);
  // NGAMCTRL(Negative Gamma Control)
  writeCommand(0xE1);
  spiWrite(0x0F);
  spiWrite(0x32);
  spiWrite(0x2E);
  spiWrite(0x0B);
  spiWrite(0x0D);
  spiWrite(0x05);
  spiWrite(0x47);
  spiWrite(0x75);
  spiWrite(0x37);
  spiWrite(0x06);
  spiWrite(0x10);
  spiWrite(0x03);
  spiWrite(0x24);
  spiWrite(0x20);
  spiWrite(0x00);
  // Digital Gamma Control 1
  writeCommand(0xE2);
  spiWrite(0x0F);
  spiWrite(0x32);
  spiWrite(0x2E);
  spiWrite(0x0B);
  spiWrite(0x0D);
  spiWrite(0x05);
  spiWrite(0x47);
  spiWrite(0x75);
  spiWrite(0x37);
  spiWrite(0x06);
  spiWrite(0x10);
  spiWrite(0x03);
  spiWrite(0x24);
  spiWrite(0x20);
  spiWrite(0x00);
  writeCommand(0x11);  // Sleep OUT
  delay(150);   // wait some time
  writeCommand(0x29);  // Display ON
#endif
  if (_bl_pin >= 0)
  {
    pinMode(_bl_pin, OUTPUT);
    digitalWrite(_bl_pin, HIGH);
  }
  endWrite();
}

void ZxTFT_ILI9488::setRotation(uint8_t r)
{
  Adafruit_GFX::setRotation(r);
  startWrite();
  writeCommand(ILI9488_MADCTL);
  switch (r & 3)
  {
    case 0:
      spiWrite(MADCTL_MX | _bgr);
      break;
    case 1:
      spiWrite(MADCTL_MV | _bgr);
      break;
    case 2:
      spiWrite(MADCTL_MY | _bgr);
      break;
    case 3:
      spiWrite(MADCTL_MX | MADCTL_MY | MADCTL_MV | _bgr);
      break;
  }
  endWrite();
}

void ZxTFT_ILI9488::invertDisplay(boolean i)
{
  _bgr = i ? MADCTL_BGR : 0x00;
  setRotation(rotation);
}


void ZxTFT_ILI9488::invert(boolean i)
{
  invertDisplay(i);
}

void ZxTFT_ILI9488::enableDisplay(boolean enable)
{
  startWrite();
  writeCommand(enable ? 0x29 : 0x28);  // Display ON / Display OFF
  if (_bl_pin >= 0) digitalWrite(_bl_pin, enable ? HIGH : LOW);
  endWrite();
}

void ZxTFT_ILI9488::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  uint16_t xe = x + w - 1;
  uint16_t ye = y + h - 1;
  writeCommand(ILI9488_CASET);
  SPI_WRITE16(x);
  SPI_WRITE16(xe);
  writeCommand(ILI9488_PASET);
  SPI_WRITE16(y);
  SPI_WRITE16(ye);
  writeCommand(ILI9488_RAMWR);
}

void ZxTFT_ILI9488::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  // Clip first...
  if ((x >= 0) && (x < _width) && (y >= 0) && (y < _height))
  {
    // THEN set up transaction (if needed) and draw...
    startWrite();
    setAddrWindow(x, y, 1, 1);
    _writeColor16(color, 1);
    endWrite();
  }
  //Serial.print(".");
}

void ZxTFT_ILI9488::writePixel(int16_t x, int16_t y, uint16_t color)
{
  // Clip first...
  if ((x >= 0) && (x < _width) && (y >= 0) && (y < _height))
  {
    // THEN set up transaction (if needed) and draw...
    setAddrWindow(x, y, 1, 1);
    _writeColor16(color, 1);
  }
  //Serial.print(".");
}

void ZxTFT_ILI9488::writeColor(uint16_t color, uint32_t len)
{
  _writeColor16(color, len);
}

void ZxTFT_ILI9488::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  //  if ((x < 0) || (y < 0) || (w < 1) || (h < 1) || (x + w > _width) || (y + h > _height))
  //  {
  //    Serial.print("writeFillRect("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.print(", "); Serial.print(w); Serial.print(", "); Serial.print(h); Serial.println(") oops? "); delay(1);
  //  }
  // a correct clipping is the goal. try to achieve this
  if (x < 0) w += x, x = 0;
  if (y < 0) h += y, y = 0;
  if (x + w > _width) w = _width - x;
  if (y + h > _height) h = _height - y;
  if ((w < 1) || (h < 1)) return;
  setAddrWindow(x, y, w, h);
  _writeColor16(color, uint32_t(w) * uint32_t(h));
}

void ZxTFT_ILI9488::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  writeFillRect(x, y, w, 1, color);
}

void ZxTFT_ILI9488::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  writeFillRect(x, y, 1, h, color);
}

void ZxTFT_ILI9488::_writeColor16(uint16_t data, uint32_t n)
{
  if (0 == connection) // TFT_HARD_SPI
  {
#if (defined (ESP8266) || defined(ESP32))
    uint8_t rgb888[] = {uint8_t((data & 0xF800) >> 8), uint8_t((data & 0x07E0) >> 3), uint8_t((data & 0x001F) << 3)};
    SPI.writePattern(rgb888, 3, n);
#else // wdt on ESP8266
    while (n-- > 0)
    {
      spiWrite(uint8_t((data & 0xF800) >> 8));
      spiWrite(uint8_t((data & 0x07E0) >> 3));
      spiWrite(uint8_t((data & 0x001F) << 3));
    }
#endif
  }
  else
  {
    while (n-- > 0)
    {
      spiWrite(uint8_t((data & 0xF800) >> 8));
      spiWrite(uint8_t((data & 0x07E0) >> 3));
      spiWrite(uint8_t((data & 0x001F) << 3));
    }
  }
}

#if (defined (ESP8266) || defined(ESP32))
#define SPI_WRITE_BYTES(data, n) SPI.transferBytes(data, 0, n)
#elif defined(ARDUINO_ARCH_SAM)
#define SPI_WRITE_BYTES(data, n) SPI.transfer(SS, data, n)
#elif (TEENSYDUINO == 147)
#define SPI_WRITE_BYTES(data, n) SPI.transfer(data, 0, n)
#elif defined(ARDUINO_ARCH_STM32F1) || defined(ARDUINO_ARCH_STM32F4)
#define SPI_WRITE_BYTES(data, n) SPI.write(data, n)
#else
// valid for all other platforms? else comment out next line
#define SPI_WRITE_BYTES(data, n) SPI.transfer(data, n)
#endif


void ZxTFT_ILI9488::_writeColor16(const uint16_t* data, uint32_t n)
{
  if (0 == connection) // TFT_HARD_SPI
  {
#if defined(SPI_WRITE_BYTES)
    static const uint16_t rgb888_buffer_size = 60; // 64 optimal for ESP8266 SPI
    static const uint32_t max_chunk = rgb888_buffer_size / 3; // rgb888
    uint8_t rgb888_buffer[rgb888_buffer_size];
    while (n > 0)
    {
      uint32_t chunk = min(max_chunk, n);
      n -= chunk;
      uint8_t* p = rgb888_buffer;
      uint16_t ncopy = chunk;
      while (ncopy-- > 0)
      {
        *p++ = uint8_t((*data & 0xF800) >> 8);
        *p++ = uint8_t((*data & 0x07E0) >> 3);
        *p++ = uint8_t((*data & 0x001F) << 3);
        data++;
      }
      SPI_WRITE_BYTES(rgb888_buffer, 3 * chunk);
    }
#else
    while (n-- > 0)
    {
      spiWrite(uint8_t((*data & 0xF800) >> 8));
      spiWrite(uint8_t((*data & 0x07E0) >> 3));
      spiWrite(uint8_t((*data & 0x001F) << 3));
    }
#endif
  }
  else
  {
    while (n-- > 0)
    {
      spiWrite(uint8_t((*data & 0xF800) >> 8));
      spiWrite(uint8_t((*data & 0x07E0) >> 3));
      spiWrite(uint8_t((*data & 0x001F) << 3));
    }
  }
}
