// created by Jean-Marc Zingg to be the ZxTFT_ILI9486 class for the ZxTFT library (instead of the GxCTRL_ILI9486 class for the GxTFT library)
// code extracts taken from https://github.com/Bodmer/TFT_HX8357
// code extracts taken from https://github.com/adafruit/Adafruit-GFX-Library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//

#include "ZxTFT_ILI9486.h"

#define SPI_SPEED 27000000
//#define SPI_SPEED 4000000

#define ILI9486_CASET 0x2A
#define ILI9486_PASET 0x2B
#define ILI9486_RAMWR 0x2C
#define ILI9486_RAMRD   0x2E
#define ILI9486_MADCTL 0x36
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

ZxTFT_ILI9486::ZxTFT_ILI9486(int8_t cs_pin, int8_t dc_pin, int8_t rst_pin) :
#if defined(ESP8266)
  Adafruit_SPITFT(320, 480, cs_pin, dc_pin, rst_pin), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
#else
  Adafruit_SPITFT(320, 480, &SPI, cs_pin, dc_pin, rst_pin), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
#endif
{
  _bgr = MADCTL_BGR;
  _cs = cs_pin;
  _dc = dc_pin;
}

ZxTFT_ILI9486::ZxTFT_ILI9486(int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin) :
  Adafruit_SPITFT(320, 480, cs_pin, dc_pin, mosi_pin, sclk_pin, rst_pin, -1), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
{
  _bgr = MADCTL_BGR;
  _cs = cs_pin;
  _dc = dc_pin;
}

ZxTFT_ILI9486::ZxTFT_ILI9486(uint16_t width, uint16_t height,
                             SPIClass *spi, int8_t cs_pin, int8_t dc_pin, int8_t rst_pin) :
#if defined(ESP8266)
  Adafruit_SPITFT(width, height, cs_pin, dc_pin, rst_pin), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
#else
  Adafruit_SPITFT(width, height, spi, cs_pin, dc_pin, rst_pin), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
#endif
{
  _bgr = MADCTL_BGR;
  _cs = cs_pin;
  _dc = dc_pin;
}

ZxTFT_ILI9486::ZxTFT_ILI9486(uint16_t width, uint16_t height,
                             int8_t cs_pin, int8_t dc_pin, int8_t mosi_pin, int8_t sclk_pin, int8_t rst_pin) :
  Adafruit_SPITFT(width, height, cs_pin, dc_pin, mosi_pin, sclk_pin, rst_pin, -1), _spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE0)
{
  _bgr = MADCTL_BGR;
  _cs = cs_pin;
  _dc = dc_pin;
}

void ZxTFT_ILI9486::begin(uint32_t freq)
{
  init(freq);
}

void ZxTFT_ILI9486::init(uint32_t freq)
{
  Serial.println("init");
  digitalWrite(_cs, HIGH);
  digitalWrite(_dc, HIGH);
  pinMode(_cs, OUTPUT);    // Enable outputs
  pinMode(_dc, OUTPUT);
  SPI.begin();
  //SPI.beginTransaction( { SPI_SPEED, MSBFIRST, SPI_MODE0 } );
  if (_rst >= 0)
  {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, LOW);
    delay(20);
    digitalWrite(_rst, HIGH);
    delay(200);
  }
  if (!freq) freq = SPI_SPEED;
  initSPI(freq);
  // this controller needs separate transactions; reason _dc before _cs
  // _dc Data/Command needs be set before activating CS
  _writeCommandTransaction(0x3A);
  _writeDataTransaction(0x55);  // use 16 bits per pixel color
  _writeCommandTransaction(0x36);
  _writeDataTransaction(0x48);  // MX, BGR == rotation 0
  // PGAMCTRL(Positive Gamma Control)
  _writeCommandTransaction(0xE0);
  _writeDataTransaction(0x0F);
  _writeDataTransaction(0x1F);
  _writeDataTransaction(0x1C);
  _writeDataTransaction(0x0C);
  _writeDataTransaction(0x0F);
  _writeDataTransaction(0x08);
  _writeDataTransaction(0x48);
  _writeDataTransaction(0x98);
  _writeDataTransaction(0x37);
  _writeDataTransaction(0x0A);
  _writeDataTransaction(0x13);
  _writeDataTransaction(0x04);
  _writeDataTransaction(0x11);
  _writeDataTransaction(0x0D);
  _writeDataTransaction(0x00);
  // NGAMCTRL(Negative Gamma Control)
  _writeCommandTransaction(0xE1);
  _writeDataTransaction(0x0F);
  _writeDataTransaction(0x32);
  _writeDataTransaction(0x2E);
  _writeDataTransaction(0x0B);
  _writeDataTransaction(0x0D);
  _writeDataTransaction(0x05);
  _writeDataTransaction(0x47);
  _writeDataTransaction(0x75);
  _writeDataTransaction(0x37);
  _writeDataTransaction(0x06);
  _writeDataTransaction(0x10);
  _writeDataTransaction(0x03);
  _writeDataTransaction(0x24);
  _writeDataTransaction(0x20);
  _writeDataTransaction(0x00);
  // Digital Gamma Control 1
  _writeCommandTransaction(0xE2);
  _writeDataTransaction(0x0F);
  _writeDataTransaction(0x32);
  _writeDataTransaction(0x2E);
  _writeDataTransaction(0x0B);
  _writeDataTransaction(0x0D);
  _writeDataTransaction(0x05);
  _writeDataTransaction(0x47);
  _writeDataTransaction(0x75);
  _writeDataTransaction(0x37);
  _writeDataTransaction(0x06);
  _writeDataTransaction(0x10);
  _writeDataTransaction(0x03);
  _writeDataTransaction(0x24);
  _writeDataTransaction(0x20);
  _writeDataTransaction(0x00);
  _writeCommandTransaction(0x11);  // Sleep OUT
  delay(150);   // wait some time
  _writeCommandTransaction(0x29);  // Display ON
}

void ZxTFT_ILI9486::setRotation(uint8_t r)
{
  rotation = r & 3;
  _width = (rotation & 1) ? HEIGHT : WIDTH;
  _height = (rotation & 1) ? WIDTH : HEIGHT;
  // this controller seems to need separate transactions; reason _dc before _cs
  // _dc Data/Command needs be set before activating CS
  _writeCommandTransaction(ILI9486_MADCTL);
  switch (r & 3)
  {
    case 0:
      _writeDataTransaction(MADCTL_MX | _bgr);
      break;
    case 1:
      _writeDataTransaction(MADCTL_MV | _bgr);
      break;
    case 2:
      _writeDataTransaction(MADCTL_MY | _bgr);
      break;
    case 3:
      _writeDataTransaction(MADCTL_MX | MADCTL_MY | MADCTL_MV | _bgr);
      break;
  }
}

void ZxTFT_ILI9486::invertDisplay(boolean i)
{
  _bgr = i ? MADCTL_BGR : 0x00;
  setRotation(rotation);
}


void ZxTFT_ILI9486::invert(boolean i)
{
  invertDisplay(i);
}

#if 1
void ZxTFT_ILI9486::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  uint16_t xe = x + w - 1;
  uint16_t ye = y + h - 1;
  // this controller seems to need separate transactions; reason _dc before _cs
  // _dc Data/Command needs be set before activating CS
  // parameters need separate transactions per byte
  SPI_CS_HIGH(); // undo

  SPI_DC_LOW();
  SPI_CS_LOW();
  spiWrite(ILI9486_CASET);  // Column addr set
  SPI_CS_HIGH();
  SPI_DC_HIGH();
  
  SPI_CS_LOW();
  spiWrite(x >> 8);
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(x & 0xFF); // XSTART
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(xe >> 8);
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(xe & 0xFF); // XEND
  SPI_CS_HIGH();

  SPI_DC_LOW();
  SPI_CS_LOW();
  spiWrite(ILI9486_PASET);  // Row addr set
  SPI_CS_HIGH();
  SPI_DC_HIGH();

  SPI_CS_LOW();
  spiWrite(y >> 8);
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(y);        // YSTART
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(ye >> 8);
  SPI_CS_HIGH();

  SPI_CS_LOW();
  spiWrite(ye);        // YEND
  SPI_CS_HIGH();

  SPI_DC_LOW();
  SPI_CS_LOW();
  spiWrite(ILI9486_RAMWR);  // write to RAM
  SPI_CS_HIGH();
  SPI_DC_HIGH();

  SPI_CS_LOW(); // redo
}
#else
void ZxTFT_ILI9486::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  uint16_t xe = x + w - 1;
  uint16_t ye = y + h - 1;
  // this controller seems to need separate transactions; reason _dc before _cs
  // _dc Data/Command needs be set before activating CS
  _writeCommandTransaction(ILI9486_CASET);  // Column addr set
  _writeDataTransaction(x >> 8);
  _writeDataTransaction(x & 0xFF); // XSTART
  _writeDataTransaction(xe >> 8);
  _writeDataTransaction(xe & 0xFF); // XEND
  _writeCommandTransaction(ILI9486_PASET);  // Row addr set
  _writeDataTransaction(y >> 8);
  _writeDataTransaction(y);        // YSTART
  _writeDataTransaction(ye >> 8);
  _writeDataTransaction(ye);        // YEND
  _writeCommandTransaction(ILI9486_RAMWR);  // write to RAM
  startWrite(); // undo endWrite();
}
#endif

void ZxTFT_ILI9486::enableDisplay(boolean enable)
{
  _writeCommandTransaction(enable ? 0x29 : 0x28);  // Display ON / Display OFF
}

void ZxTFT_ILI9486::_writeCommandTransaction(uint8_t cmd)
{
  if (_dc >= 0) digitalWrite(_dc, LOW); // dc before _cs
  startWrite();
  spiWrite(cmd);
  endWrite();
  if (_dc >= 0) digitalWrite(_dc, HIGH);
}

void ZxTFT_ILI9486::_writeDataTransaction(uint8_t data)
{
  startWrite();
  spiWrite(data);
  endWrite();
}
