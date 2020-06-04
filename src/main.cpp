/*
  Links de referencias
  Datasheet
  http://www.buydisplay.com/download/manual/ER-TFTM070-6_Datasheet.pdf

  Referencia en tienda
  https://www.buydisplay.com/spi-7-inch-tft-lcd-dislay-module-1024x600-ra8876-optl-touch-screen-panel

  Interface with 8051
  https://www.buydisplay.com/download/interfacing/ER-TFTM070-6_CTP_Interfacing.pdf

  Librería de Arduino
  https://github.com/xlatb/ra8876/blob/master/src/RA8876.cpp

  Pinouts ESP32 para SPI
  https://randomnerdtutorials.com/esp32-pinout-reference-gpios/


  Notas
  Vdd = 3.3V if J29 short
  Vdd = 5V   if J29 open


  Conexiones
  ESP ------------------- TFT
  VIN (5v Ext)
  23 (MOSI)               7 (SDI)
  19 (MISO)               6 (SDO)
  18 (SCLK)               8 (SCLK)
  5  (CS)                 5 (CS)
  16                      11 (RST)
                          1 (GND)
                          3 (VDD) 3.3v
                          14 (BL) 3.3v 

*/

#include <Arduino.h>
#include <RA8876.h>

#define RA8876_CS 5
#define RA8876_RESET 16
#define RA8876_BACKLIGHT 14

int r = 0;
int g = 0;
int b = 0;

RA8876 tft = RA8876(RA8876_CS, RA8876_RESET);

void initTft();
void drawText();
void testBackgrounds();

void setup()
{
  Serial.begin(9600);
  initTft();
}

void loop()
{
  testBackgrounds();
}

void initTft()
{
  pinMode(RA8876_BACKLIGHT, OUTPUT);    // Set backlight pin to OUTPUT mode
  digitalWrite(RA8876_BACKLIGHT, HIGH); // Turn on backlight

  if (!tft.init())
  {
    Serial.println("Could not initialize RA8876");
  }

  Serial.println("Startup complete...");

  tft.clearScreen(0);
  tft.colorBarTest(true);
  delay(3000);
  tft.colorBarTest(false);
}

void drawText()
{
  tft.setTextScale(4);
  tft.setCursor(tft.getWidth() / 5, tft.getHeight() / 3);
  tft.print("Que onda!?, Rodo");
}

void testBackgrounds()
{
  r = random(0, 255);
  g = random(0, 255);
  b = random(0, 255);
  
  tft.clearScreen(RGB565(r, g, b));
  drawText();
  delay(200);
}