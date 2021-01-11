#include "axis_RA.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "globals.h"
#include "sdkconfig.h"
#include "validate.h"
//#include <stdio.h>

TaskHandle_t axis_RA_track_handle;
Axis_RA      axis_RA;

void app_main() {
    printf("[%d] START\n", xTaskGetTickCount());
    Axis_RA__init(&axis_RA, AXIS_RA_PIN_DIR, AXIS_RA_PIN_STEP, AXIS_RA_PIN_ENABLE);
    // xTaskCreate((void *)Axis_RA__task_track, "task_track_RA", 2048, &axis_RA, 5, &axis_RA_track_handle);

    // Axis_RA__driver_speed(&axis_RA, 1000);

    // //Axis_RA__task_track_handle(&axis_RA, axis_RA_track_handle, Start);
    // vTaskDelay(pdMS_TO_TICKS(10000));
    // Axis_RA__task_track_handle(&axis_RA, axis_RA_track_handle, Delete);

    // set timer
    const esp_timer_create_args_t track_timer_args = {
        .callback = &track_isr,
        .name     = "task_track_timer", // name is optional, but may help identify the timer when debugging
        .arg      = &axis_RA};
    ESP_ERROR_CHECK(esp_timer_create(&track_timer_args, &track_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(track_timer, axis_RA.stepTime));
    Axis_RA__driver_enable(&axis_RA, true);

    printf("[%d] END\n", xTaskGetTickCount());
}