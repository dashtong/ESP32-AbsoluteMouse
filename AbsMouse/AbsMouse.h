#include <BleMouse.h>

// The factor is not in linear scale
#define SMALL_STEP 20
#define CENTER_X 720
#define CENTER_Y 500
#define FULLSCREEN_X 1460
#define FULLSCREEN_Y 1000
#define REST_TIME 10000

class AbsMouse {
private:
  BleMouse mouse;

public:
  int now_x = 0;
  int now_y = 0;

  void begin();
  void reset();
  void move(signed char x, signed char y);
  void moveTo(int x, int y);
  void press();
  void pressAt(int x, int y);
  void release();
  void releaseAt(int x, int y);
  void click();
  void clickAt(int x, int y);
};

/*
0,0                  x,0
----------------------
|                     |
|                     |
|                     |
|                     |
|                     |
----------------------
0,y                  x,y
*/
