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
    printf("[%d] START\n", xTaskGetTickCount());

    Axis_RA_config ax_ra_conf = {
        .pinDir    = AXIS_RA_PIN_DIR,
        .pinStep   = AXIS_RA_PIN_STEP,
        .pinEnable = AXIS_RA_PIN_ENABLE,
        .speed     = 100,
        .dir       = true};
    RA_tracker = TSK_tracker_init(&ax_ra_conf);

    // TODO - find a way to pass or get values from the TASK (Queues?)

    // Axis_RA__driver_speed(&axis_RA, 1000);
    xTaskNotify(RA_tracker, Start, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(10000));
    xTaskNotify(RA_tracker, Stop, eSetValueWithOverwrite);

    printf("[%d] END\n", xTaskGetTickCount());
}