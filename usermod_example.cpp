.#include "wled.h"
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
    oled.setFont(u8g2_font_6x10_tr);

    oled.drawStr(10, 12, "Clock + Spectrum");
    oled.drawStr(10, 30, "OLED TEST");

    oled.sendBuffer();
  }

  void loop() override {

    if (millis() - lastUpdate < 100) return;
    lastUpdate = millis();

    oled.clearBuffer();

    // Klok bovenaan
    oled.setFont(u8g2_font_ncenB14_tr);

    char timeText[20];
    sprintf(timeText, "%02d:%02d:%02d",
            hour(),
            minute(),
            second());

    oled.drawStr(20, 18, timeText);

    // Spectrum onderaan
    oled.setFont(u8g2_font_6x10_tr);

    for (int i = 0; i < 16; i++) {

      int barHeight = 0;

      if (um_data) {
        barHeight = um_data->fftResult[i] / 8;
      }

      if (barHeight > 40) barHeight = 40;

      int x = i * 8;

      oled.drawBox(x, 63 - barHeight, 6, barHeight);
    }

    oled.sendBuffer();
  }
};

static OledClockSpectrum oledClockSpectrum;
REGISTER_USERMOD(oledClockSpectrum);
