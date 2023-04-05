// includes code from: https://github.com/mistablinky/Line-for-Watchy
#include <Watchy.h>
#include "settings.h"

class orbital : public Watchy {
 public:
  orbital() : Watchy(settings) {}
  void drawWatchFace();
};

void orbital::drawWatchFace() {
  display.fillScreen(GxEPD_BLACK);

  //uint8_t hours = hour(currentTime);
  //uint8_t minutes = minute(currentTime);
  //uint8_t seconds = second(currentTime);
  uint32_t steps = sensor.getCounter();

  uint16_t pixelColor = GxEPD_WHITE;
  uint16_t bgColor = GxEPD_BLACK;
  uint8_t origin = 0;
  uint8_t w = 200;
  uint8_t h = 200;
  uint8_t myHour;
  uint8_t myMinute;
  uint8_t radius;
  float angle_hourScale;
  float angle_minuteScale;
  float angle_hourHand;
  float angle_minuteHand;
  float pi = 3.1415926535897932384626433832795;

  myHour   = currentTime.Hour > 12 ? currentTime.Hour - 12 : currentTime.Hour;
  myMinute = currentTime.Minute;
      
  angle_hourScale   = 2*pi/12;
  angle_minuteScale = 2*pi/60;
  angle_hourHand    = angle_hourScale*(myHour-3)+2*pi/720*myMinute;
  angle_minuteHand  = angle_minuteScale*(myMinute-15);
  radius = 80;

  float hx = radius*cos(angle_hourHand);
  float hy = radius*sin(angle_hourHand);
  float mx = radius*cos(angle_minuteHand);
  float my = radius*sin(angle_minuteHand);


  display. fillRect(origin+10, origin+10, w-20,h-20, pixelColor);
  display.fillCircle(w/2, h/2, radius ,GxEPD_BLACK );
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_WHITE);
  display.fillCircle(w/2+hx, h/2+hy, 10,GxEPD_BLACK);
  display.fillCircle(w/2+mx, h/2+my, 10,GxEPD_WHITE );
  display.setCursor(40, 90);
  display.println(currentTime.Hour);
  display.setCursor(40, 110);
  display.println(currentTime.Minute);
  display.setCursor(100, 100);
  display.println(String(steps) + " stps");

  display.refresh();
}

orbital orbital;
void setup() { orbital.init(); }
void loop() { orbital.handleButtonPress(); }