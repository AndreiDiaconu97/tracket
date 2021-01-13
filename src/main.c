//#include "cmd.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "globals.h"
//#include "goto.h"
//#include "guide.h"
//#include "home.h"
//#include "park.h"
#include "sdkconfig.h"
//#include "starAlign.h"
#include "track.h" // FIXME - track with GLOBAL timers
//#include "validate.h"
//#include "axis_RA.h"
//#include <stdio.h>

TaskHandle_t RA_tracker;

void app_main() {
    printf("[%s][%dms] BEGIN\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);

    // Axis_RA_conf ax_ra_conf = {
    //     .pinDir    = AXIS_RA_PIN_DIR,
    //     .pinStep   = AXIS_RA_PIN_STEP,
    //     .pinEnable = AXIS_RA_PIN_ENABLE,
    //     .speed     = 100,
    //     .dir       = true};
    // RA_tracker = TSK_tracker_init(&ax_ra_conf);

    printf("[%s][%dms] END\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
}