#include <Watchy.h>
#include "settings.h"

// Define DEG2RAD constant
#define DEG2RAD 0.0174532925

int fillArc2(GxEPD2_BW<WatchyDisplay, GxEPD2_154_D67::HEIGHT> &display, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour) {
  int angle = start_angle * DEG2RAD * 3;
  int x0 = x + cos(angle) * (rx - w);
  int y0 = y + sin(angle) * (ry - w);
  int x1 = x + cos(angle) * rx;
  int y1 = y + sin(angle) * ry;

  for (int i = 0; i < seg_count; i++) {
    angle += DEG2RAD * 3;
    int x2 = x + cos(angle) * (rx - w);
    int y2 = y + sin(angle) * (ry - w);
    int x3 = x + cos(angle) * rx;
    int y3 = y + sin(angle) * ry;

    display.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    display.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
  return angle;
}

class arc : public Watchy {
 public:
  arc() : Watchy(settings) {}
  void drawWatchFace();
};

void arc::drawWatchFace() {
  display.fillScreen(GxEPD_BLACK);

  // Modify these values as needed for your desired arc
  int x = 100;
  int y = 100;
  int start_angle = 0;
  int seg_count = 30; // 30 segments * 3 degrees each = 90 degrees
  int rx = 50;
  int ry = 50;
  int w = 5;
  unsigned int colour = GxEPD_WHITE;

  fillArc2(display, x, y, start_angle, seg_count, rx, ry, w, colour);

  display.refresh();
}

arc arc;
void setup() { arc.init(); }
void loop() { arc.handleButtonPress(); }