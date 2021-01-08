#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rotator.h"
#include "sdkconfig.h"

struct rotator rotator_RA;
struct rotator rotator_DEC;

void task_1(void *args) {
    printf("[%d] %s\n", xTaskGetTickCount(), pcTaskGetTaskName(NULL));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void task_2(void *args) {
    TaskHandle_t task_1_handle = NULL;
    while (1) {
        printf("[%d] %s\n", xTaskGetTickCount(), pcTaskGetTaskName(NULL));

        printf("[%d] create %s\n", xTaskGetTickCount(), pcTaskGetTaskName(task_1_handle));
        xTaskCreate(task_1, "task_1", 2048, NULL, 5, &task_1_handle);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    rotator__init(&rotator_RA);
    printf("START %f\n", rotator_RA.x);
    printf("START %f\n", rotator_DEC.x);
    xTaskCreate(task_2, "task_2", 2048, NULL, 5, NULL);
}