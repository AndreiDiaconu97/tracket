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

    // Axis_RA__driver_speed(&axis_RA, 1000);
    // TODO - find a way to pass or get values from the TASK (Queues?)
    // TODO - make wrapper function for xTaskNotify()

    xTaskNotify(RA_tracker, Start, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Start, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Delete, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Delete, eSetValueWithOverwrite);

    vTaskDelay(pdMS_TO_TICKS(1000));
    ax_ra_conf.speed = 1000;
    RA_tracker       = TSK_tracker_init(&ax_ra_conf);
    xTaskNotify(RA_tracker, Start, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Stop, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Stop, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Delete, eSetValueWithOverwrite);

    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Start, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskNotify(RA_tracker, Stop, eSetValueWithOverwrite);

    printf("[%s][%dms] END\n", pcTaskGetTaskName(NULL), xTaskGetTickCount() * 10);
}