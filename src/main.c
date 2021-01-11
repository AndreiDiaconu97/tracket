#include "axis_RA.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "sdkconfig.h"
#include "validate.h"
//#include <stdio.h>

Axis_RA axis_RA;

void app_main() {
    printf("[%d] START\n", xTaskGetTickCount());
    Axis_RA__init(&axis_RA, AXIS_RA_PIN_DIR, AXIS_RA_PIN_STEP, AXIS_RA_PIN_ENABLE);
    xTaskCreate((void *)Axis_RA__task_track, "task_track_RA", 2048, &axis_RA, 5, &axis_RA_track_handle);

    Axis_RA__driver_speed(&axis_RA, 500);

    //Axis_RA__task_track_handle(&axis_RA, axis_RA_track_handle, Start);
    vTaskDelay(pdMS_TO_TICKS(1000));
    Axis_RA__task_track_handle(&axis_RA, axis_RA_track_handle, Delete);
}