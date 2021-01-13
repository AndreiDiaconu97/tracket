// ---------------------------------------------------------------------------------------------------
// GUIDE TASK for moving the mount in any direction at a series of fixed rates

#ifndef TRACK_H
#define TRACK_H

#include "config.h"
#include "globals.h"

// REVIEW Teensy3.x, ESP32, STM32 have very accurate crystal oscillators
// that usually need no frequency compensation (PPS) or tracking rate adjustment

class track {
  private:
  public:
    track();
    ~track();
    int my_c;
    int my_a;
};

#endif