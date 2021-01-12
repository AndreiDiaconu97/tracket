#include "axis_RA.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "sdkconfig.h"
#include "validate.h"
//#include <stdio.h>

TaskHandle_t RA_tracker;

void app_main() {
    printf("[%s][%dms] BEGIN\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);

    Axis_RA_conf ax_ra_conf = {
        .pinDir    = AXIS_RA_PIN_DIR,
        .pinStep   = AXIS_RA_PIN_STEP,
        .pinEnable = AXIS_RA_PIN_ENABLE,
        .speed     = 100,
        .dir       = true};
    RA_tracker = TSK_tracker_init(&ax_ra_conf);



    printf("[%s][%dms] END\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
}