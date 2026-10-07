#include "wled.h"
#include <Wire.h>
#include <U8g2lib.h>

class OledClockSpectrum : public Usermod {

private:
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled =
      U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);

  unsigned long lastUpdate = 0;

public:

  void setup() override {
    Wire.begin(21, 22);

    oled.begin();
    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB14_tr);
    oled.drawStr(10, 30, "OLED OK");

    oled.setFont(u8g2_font_6x10_tr);
    oled.drawStr(10, 50, "WLED test");

    oled.sendBuffer();
  }

  void loop() override {
    if (millis() - lastUpdate < 1000) return;
    lastUpdate = millis();

    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB14_tr);
    oled.drawStr(10, 30, "OLED OK");

    oled.setFont(u8g2_font_6x10_tr);
    oled.drawStr(10, 50, "WLED test");

    oled.sendBuffer();
  }
};

static OledClockSpectrum oledClockSpectrum;
REGISTER_USERMOD(oledClockSpectrum);

Je gebruikt het gratis abonnement
