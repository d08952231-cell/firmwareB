#include <Arduino.h>
#include <LovyanGFX.hpp>
#include <ELECHOUSE_CC1101.h>

class LGFX : public lgfx::LGFX_Default {
public:
  LGFX(void) {
    { 
      auto cfg = bus_spi();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      cfg.spi_3wire  = true;
      cfg.use_lock   = true;
      cfg.dma_channel = 1;
      cfg.pin_sclk = 18;
      cfg.pin_mosi = 23;
      cfg.pin_miso = -1;
      cfg.pin_dc   = 15;
      bus_spi(cfg);
    }
    { 
      auto cfg = panel();
      cfg.pin_cs           = 5;
      cfg.pin_rst          = 13;
      cfg.pin_busy         = -1;
      cfg.panel_width      = 240;
      cfg.panel_height     = 135;
      cfg.offset_x         = 40;
      cfg.offset_y         = 52;
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = false;
      cfg.invert           = true;
      cfg.rgb_order        = false;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       = false;
      panel(cfg);
    }
  }
};

LGFX lcd;

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLACK);
  
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  lcd.setTextSize(3);
  lcd.setCursor(10, 20);
  lcd.print("ГЛАВНОЕ МЕНЮ");

  lcd.setTextSize(4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.setCursor(30, 60);
  lcd.print("Привет!"); // Ваше слово

  lcd.setTextSize(2);
  lcd.setTextColor(TFT_CYAN, TFT_BLACK);
  lcd.setCursor(10, 110);
  lcd.print("CC1101 Ready...");

  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setMHZ(433.92);
}

void loop() {
  delay(1000);
}
