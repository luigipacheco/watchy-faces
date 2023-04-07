// Includes code from : https://forum.arduino.cc/t/adafruit_gfx-fillarc/397741/6
#include <Watchy.h>
#include "settings.h"

// Define DEG2RAD constant
#define DEG2RAD 0.0174532925

void fillArc2(GxEPD2_BW<WatchyDisplay, GxEPD2_154_D67::HEIGHT> &display, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour) {
byte seg = 3; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 3; // Draw segments every 3 degrees, increase to 6 for segmented ring

    // Calculate first pair of coordinates for segment start
    float sx = cos((start_angle - 90) * DEG2RAD);
    float sy = sin((start_angle - 90) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    display.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    display.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}

class arc : public Watchy {
 public:
  arc() : Watchy(settings) {}
  void drawWatchFace();
};

void arc::drawWatchFace() {
  if (currentTime.Hour == 0 && currentTime.Minute == 0){
      sensor.resetStepCounter();
    }
    bool lowBattery = false;
    float VBAT = getBatteryVoltage();
    if(VBAT <= 3.8){
        lowBattery = true;
    }

  // Modify these values as needed for your desired arc
  int x = 100;
  int y = 100;
  int start_angle = 0;
  int hour12 = currentTime.Hour > 12 ? currentTime.Hour - 12 : currentTime.Hour; // 30 segments * 3 degrees each = 90 degrees (120)
  int hours = hour12*10;
  int minutes = currentTime.Minute * 2; // 30 segments * 3 degrees each = 90 degrees(120)
  int steps =  sensor.getCounter()*190/10000+1;
  int rx = 60;
  int ry = 60;
  int offset = 10;
  int w = 6;
  unsigned int colour = GxEPD_WHITE;
display.drawCircle(x, y,  rx,colour);
display.drawCircle(x, y,  rx + offset,colour);
fillArc2(display, x, y, start_angle, minutes, rx+w/2, ry+w/2, w, colour);
fillArc2(display, x, y, start_angle, hours, rx+offset+w/2, ry+offset+w/2, w, colour);
//display.drawRect(5, 5, 5, 190, colour);
display.drawLine(5, 190, 195, 190, colour);
display.fillRect(5, 187, steps, 6, colour);
if(lowBattery){
  display.drawCircle(x, y,  10,colour);
}
  display.refresh();
}

arc arc;
void setup() { arc.init(); }
void loop() { arc.handleButtonPress(); }