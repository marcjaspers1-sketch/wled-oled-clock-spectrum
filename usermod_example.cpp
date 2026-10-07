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
    oled.sendBuffer();
  }

  void loop() override {

    if (millis() - lastUpdate < 100) return;
    lastUpdate = millis();

    oled.clearBuffer();

    // =========================
    // KLOK
    // =========================

    updateLocalTime();

    char timeText[12];

    sprintf(timeText, "%02d:%02d:%02d",
            hour(localTime),
            minute(localTime),
            second(localTime));

    oled.setFont(u8g2_font_6x13_tr);
    oled.drawStr(25, 13, timeText);


    // =========================
    // SPECTRUM
    // =========================

    if (um_data && um_data->u_data && um_data->u_data[2]) {

      uint8_t *fft = (uint8_t *)um_data->u_data[2];

      for (int i = 0; i < 16; i++) {

        int barHeight = fft[i] / 5;

        if (barHeight > 47)
          barHeight = 47;

        int x = i * 8;

        if (barHeight > 0) {
          oled.drawBox(x, 63 - barHeight, 6, barHeight);
        }
      }
    }

    oled.sendBuffer();
  }
};

static OledClockSpectrum oledClockSpectrum;

REGISTER_USERMOD(oledClockSpectrum);
