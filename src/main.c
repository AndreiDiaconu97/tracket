//#include "cmd.h"
#include "config.h"
#include "driver/timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "goto.h"
#include "guide.h"
#include "home.h"
#include "park.h"
#include "sdkconfig.h"
#include "starAlign.h"
#include "track.h" // FIXME - track with GLOBAL timers
#include "validate.h"
//#include "axis_RA.h"
//#include <stdio.h>

void app_main() {
    printf("[%s][%dms] BEGIN\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);

    printf("[%s][%dms] END\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
}