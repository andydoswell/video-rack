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

void draw(void) { // Draws the display, and updates the arress lines for the switches.
  u8g.setFont(u8g_font_gdr17);
  u8g.drawStr( 0, 22, "405");
  u8g.drawStr(0, 64, "625");
  switch (Aselect) {
    case 0:
      u8g.drawStr( 55, 22, "DVD");
      digitalWrite (PC0, LOW);
      digitalWrite (PC1, LOW);
      digitalWrite (PC2, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 22, "DTT1");
      digitalWrite (PC0, HIGH);
      digitalWrite (PC1, LOW);
      digitalWrite (PC2, LOW);
      break;
    case 2:
      u8g.drawStr( 55, 22, "DDT2");
      digitalWrite (PC0, LOW);
      digitalWrite (PC1, HIGH);
      digitalWrite (PC2, LOW);
      break;
    case 3:
      u8g.drawStr( 55, 22, "Media");
      digitalWrite (PC0, HIGH);
      digitalWrite (PC1, HIGH);
      digitalWrite (PC2, LOW);
      break;
    case 4:
      u8g.drawStr( 55, 22, "HDMI");
      digitalWrite (PC0, LOW);
      digitalWrite (PC1, LOW);
      digitalWrite (PC2, HIGH);
      break;
    case 5:
      u8g.drawStr( 55, 22, "Aux");
      digitalWrite (PC0, HIGH);
      digitalWrite (PC1, LOW);
      digitalWrite (PC2, HIGH);
      break;
  }
  switch (Iselect) {
    case 0:
      u8g.drawStr( 55, 64, "DVD");
      digitalWrite (PB0, LOW);
      digitalWrite (PB1, LOW);
      digitalWrite (PB2, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 64, "Media");
      digitalWrite (PB0, HIGH);
      digitalWrite (PB1, HIGH);
      digitalWrite (PB2, LOW);
      break;
    case 2:
      u8g.drawStr( 55, 64, "HDMI");
      digitalWrite (PB0, LOW);
      digitalWrite (PB1, LOW);
      digitalWrite (PB2, HIGH);
      break;
    case 3:
      u8g.drawStr( 55, 64, "Aux");
      digitalWrite (PB0, HIGH);
      digitalWrite (PB1, LOW);
      digitalWrite (PB2, HIGH);
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
  pinMode (PC0, OUTPUT); // These are the address line outputs for 405.
  pinMode (PC1, OUTPUT);
  pinMode (PC2, OUTPUT);
  pinMode (PB0, OUTPUT); // These are the address line outputs for 625.
  pinMode (PB1, OUTPUT);
  pinMode (PB2, OUTPUT);
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  if (!digitalRead(11)) { // 405 select button increments selected channel
    Aselect++;
    delay (100);
  }
  if (!digitalRead(12)) { // 625 select button increments selected channel
    Iselect++;
    delay (100);
  }

  // If anything is over-range, reset.

  if (Aselect == 6) {
    Aselect = 0;
  }
  if (Iselect == 4) {
    Iselect = 0;
  }
}
