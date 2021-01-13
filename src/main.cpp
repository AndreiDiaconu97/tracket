
#include "config.h"
#include "driver/timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "track.h" // FIXME - track with HARDWARE timers
#include "validate.h"
#include <sdkconfig.h>
//#include "cmd.h"
//#include "goto.h"
//#include "guide.h"
//#include "home.h"
//#include "park.h"
//#include "starAlign.h"
//#include "axis_RA.h"
//#include <stdio.h>

track my_track;

extern "C" void app_main() {
    printf("[%s][%dms] BEGIN\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
    vTaskDelay(100);
    my_track.my_c = sidereal_day;
    printf("[%s][%dms] END\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
}