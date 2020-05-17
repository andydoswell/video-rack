/*

  Video Rack Controller
  (2) 2020 A.G.Doswell

  Controller software for an Audio/Video switch used to switch video sources two two independent outputs. Selection is displayed on an I2C SSD1306 OLED
  display. Hardware is capable of 8 input, 2 outputs. Not all are used here.

  The reference to 405 lines is due to that output feeding a 625 line PAL to 405 Line system A standards converter.

  Hardware details can be found on my website at www.andydoz.blogspot.com

  License: The MIT License

*/


#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);	// Fast I2C / TWI
unsigned int Aselect; // 405 line output select
unsigned int Iselect; // 625 line output select

void draw(void) { // Draws the display, and updates the address lines for the switches.
  u8g.setFont(u8g_font_gdr17);
  u8g.drawStr( 0, 22, "405");
  u8g.drawStr(0, 64, "625");
  switch (Aselect) {
    case 0:
      u8g.drawStr( 55, 22, "DVD");
      digitalWrite (14, LOW);
      digitalWrite (15, LOW);
      digitalWrite (16, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 22, "DTT1");
      digitalWrite (14, HIGH);
      digitalWrite (15, LOW);
      digitalWrite (16, LOW);
      break;
    case 2:
      u8g.drawStr( 55, 22, "DTT2");
      digitalWrite (14, LOW);
      digitalWrite (15, HIGH);
      digitalWrite (16, LOW);
      break;
    case 3:
      u8g.drawStr( 55, 22, "Media");
      digitalWrite (14, HIGH);
      digitalWrite (15, HIGH);
      digitalWrite (16, LOW);
      break;
    case 4:
      u8g.drawStr( 55, 22, "HDMI");
      digitalWrite (14, LOW);
      digitalWrite (15, LOW);
      digitalWrite (16, HIGH);
      break;
    case 5:
      u8g.drawStr( 55, 22, "Aux");
      digitalWrite (14, HIGH);
      digitalWrite (15, LOW);
      digitalWrite (16, HIGH);
      break;
  }
  switch (Iselect) {
    case 0:
      u8g.drawStr( 55, 64, "DVD");
      digitalWrite (8, LOW);
      digitalWrite (9, LOW);
      digitalWrite (10, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 64, "Media");
      digitalWrite (8, HIGH);
      digitalWrite (9, HIGH);
      digitalWrite (10, LOW);
      break;
    case 2:
      u8g.drawStr( 55, 64, "HDMI");
      digitalWrite (8, LOW);
      digitalWrite (9, LOW);
      digitalWrite (10, HIGH);
      break;
    case 3:
      u8g.drawStr( 55, 64, "Aux");
      digitalWrite (8, HIGH);
      digitalWrite (9, LOW);
      digitalWrite (10, HIGH);
      break;
  }
}

void setup(void) {
  // sets up the display
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  pinMode(3, OUTPUT); // Bring up -4V supply
  analogWrite(3, 128);
  pinMode (11, INPUT_PULLUP); // 405 select switch here
  pinMode (12, INPUT_PULLUP); // 625 select switch here
  pinMode (14, OUTPUT); // These are the address line outputs for 405.
  pinMode (15, OUTPUT);
  pinMode (16, OUTPUT);
  pinMode (8, OUTPUT); // These are the address line outputs for 625.
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  if (!digitalRead(11)) { // 405 select button increments selected channel
    Aselect++;
    delay (150); // touch of delay in lieu of debounce.
  }
  if (!digitalRead(12)) { // 625 select button increments selected channel
    Iselect++;
    delay (150);
  }

  // If anything is over-range, reset.

  if (Aselect == 6) {
    Aselect = 0;
  }
  if (Iselect == 4) {
    Iselect = 0;
  }
}
