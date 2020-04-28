/*

  Video Rack Controller
  (2) 2020 A.G.Doswell


*/


#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);	// Fast I2C / TWI
unsigned int Aselect;
unsigned int Iselect;

void draw(void) {

  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_gdr17);
  u8g.drawStr( 0, 22, "405");
  u8g.drawStr(0, 64, "625");
  switch (Aselect) {
    case 0:
      u8g.drawStr( 55, 22, "DVD");
      digitalWrite (A0, LOW);
      digitalWrite (A1, LOW);
      digitalWrite (A3, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 22, "DTT1");
      digitalWrite (A0, HIGH);
      digitalWrite (A1, LOW);
      digitalWrite (A3, LOW);
      break;
    case 2:
      u8g.drawStr( 55, 22, "DDT2");
      digitalWrite (A0, LOW);
      digitalWrite (A1, HIGH);
      digitalWrite (A3, LOW);
      break;
    case 3:
      u8g.drawStr( 55, 22, "Media");
      digitalWrite (A0, HIGH);
      digitalWrite (A1, HIGH);
      digitalWrite (A3, LOW);
      break;
    case 4:
      u8g.drawStr( 55, 22, "HDMI");
      digitalWrite (A0, LOW);
      digitalWrite (A1, LOW);
      digitalWrite (A3, HIGH);
      break;
    case 5:
      u8g.drawStr( 55, 22, "Aux");
      digitalWrite (A0, HIGH);
      digitalWrite (A1, LOW);
      digitalWrite (A3, HIGH);
      break;
  }
  switch (Iselect) {
    case 0:
      u8g.drawStr( 55, 64, "DVD");
      digitalWrite (A0, LOW);
      digitalWrite (A1, LOW);
      digitalWrite (A3, LOW);
      break;
    case 1:
      u8g.drawStr( 55, 64, "Media");
      digitalWrite (A0, HIGH);
      digitalWrite (A1, HIGH);
      digitalWrite (A3, LOW);
      break;
    case 2:
      digitalWrite (A0, LOW);
      digitalWrite (A1, LOW);
      digitalWrite (A3, HIGH);
      u8g.drawStr( 55, 64, "HDMI");
      break;
    case 3:
      u8g.drawStr( 55, 64, "Aux");
      digitalWrite (A0, HIGH);
      digitalWrite (A1, LOW);
      digitalWrite (A3, HIGH);
      break;
  }

}

void setup(void) {
  // assign default color value
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
  pinMode (11, INPUT_PULLUP);
  pinMode (12, INPUT_PULLUP);
  pinMode (A0, OUTPUT);
  pinMode (A1, OUTPUT);
  pinMode (A2, OUTPUT);
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  if (!digitalRead(11)) {
    Aselect++;
    delay (100);
  }
  if (!digitalRead(12)) {
    Iselect++;
    delay (100);
  }
  if (Aselect == 6) {
    Aselect = 0;
  }
  if (Iselect == 4) {
    Iselect = 0;
  }


}
