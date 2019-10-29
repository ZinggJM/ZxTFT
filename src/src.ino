// original code taken from https://github.com/lcdwiki/LCDWIKI_SPI/tree/master/Example/Example_03_display_string/display_string

// select the display controller class
//#include "ZxTFT_SSD1283A.h"
#include "ZxTFT_ILI9486.h"

#if defined(_ZxTFT_SSD1283A_H_)

#if (defined(TEENSYDUINO) && (TEENSYDUINO == 147))
// for Mike's Artificial Horizon
ZxTFT_SSD1283A tft(/*CS=*/ 10, /*DC=*/ 15, /*RST=*/ 14, /*LED=*/ -1); //hardware spi,cs,cd,reset,led

// for my wirings used for e-paper displays:
#elif defined (ESP8266)
ZxTFT_SSD1283A tft(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*LED=D2*/ 4); //hardware spi,cs,cd,reset,led
#elif defined(ESP32)
ZxTFT_SSD1283A tft(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*LED=*/ 4); //hardware spi,cs,cd,reset,led
#elif defined(_BOARD_GENERIC_STM32F103C_H_)
ZxTFT_SSD1283A tft(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*LED=*/ 1); //hardware spi,cs,cd,reset,led
#elif defined(__AVR)
ZxTFT_SSD1283A tft(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*LED=*/ 7); //hardware spi,cs,cd,reset,led
#else
// catch all other default
ZxTFT_SSD1283A tft(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*LED=*/ 7); //hardware spi,cs,cd,reset,led
#endif

#endif

#if defined(_ZxTFT_ILI9486_H_)
#if defined (ESP8266)
ZxTFT_ILI9486 tft(/*CS=D8*/ SS, /*DC=D4*/ 2, /*RST=D3*/ 0); //hardware spi,cs,cd,reset
//ZxTFT_ILI9486 tft(/*CS=D8*/ SS, /*DC=D4*/ 2, MOSI, SCK, /*RST=D3*/ 0); // my proto board
#elif defined(ARDUINO_ARCH_SAM)
ZxTFT_ILI9486 tft(/*CS=10*/ SS, /*DC=*/ 6, /*RST=*/ 5); // my proto board
#endif
#endif

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
#if defined(_ZxTFT_ILI9486_H_)
  // uncomment for normal SPI mode, used for "special" SPI circuit found e.g. on 3.5" RPI HVGA display
  //setSpiKludge(false); // rpi_spi16_mode
#endif
  tft.init();
#if defined(_ZxTFT_ILI9486_H_)
  // my TFT uses BGR, uncomment for RGB panel
  //tft.invertDisplay(false); // set to false for RGB
#endif
  Serial.println("init() done");
  tft.fillScreen(BLACK);
  Serial.println("setup done");
}

void loop()
{
  for (uint8_t r = 0; r < 4; r++)
  {
    //Serial.print("rotation "); Serial.println(r);
    tft.setRotation(r);
    tft.fillScreen(0x0000);
    tft.setCursor(0, 0);
    tft.setTextColor(RED, BLACK);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.println(01234.56789, 2);
    tft.println(0xDEADBEF, HEX);

    tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.println("Hello");
    tft.println(01234.56789, 2);
    tft.println(0xDEADBEF, HEX);

    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.println("Hello");
    tft.println(01234.56789, 2);
    tft.println(0xDEADBEF, HEX);
    //Serial.print("rotation "); Serial.print(r); Serial.println(" done");

    delay(5000);
  }
  testTextOnCanvas();
}

//GFXcanvas16 canvas(130, 130); // uses heap space

// let the linker complain if not enough ram
GFXcanvas16T<130, 130> canvas; // uses dynamic memory space

void show_canvas_on_screen_timed()
{
  uint32_t start = micros();
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());
  uint32_t elapsed = micros() - start;
  Serial.print(F("show_canvas_on_screen    ")); Serial.println(elapsed);
}

void testTextOnCanvas()
{
  canvas.fillScreen(BLACK);
  canvas.setCursor(0, 0);
  canvas.setTextColor(WHITE);  canvas.setTextSize(1);
  canvas.println("Hello World!");
  canvas.setTextColor(YELLOW); canvas.setTextSize(2);
  canvas.println(1234.56);
  canvas.setTextColor(RED);    canvas.setTextSize(3);
  canvas.println(0xDEADBEF, HEX);
  //canvas.println();
  canvas.setTextColor(GREEN);
  canvas.setTextSize(4);
  canvas.println("Groop");
  canvas.setTextSize(2);
  canvas.println("I implore thee,");
  canvas.setTextSize(1);
  canvas.setTextColor(GREEN);
  canvas.println("my foonting turlingdromes.");
  canvas.println("And hooptiously drangle me");
  canvas.println("with crinkly bindlewurdles,");
  canvas.println("Or I will rend thee");
  canvas.println("in the gobberwarts");
  canvas.println("with my blurglecruncheon,");
  canvas.println("see if I don't!");
  if ((canvas.width() < tft.width()) || canvas.height() < tft.height())
  {
    tft.fillScreen(BLACK);
  }
  for (uint8_t r = 0; r < 4; r++)
  {
    tft.setRotation(r);
    show_canvas_on_screen_timed();
    delay(5000);
  }
}
