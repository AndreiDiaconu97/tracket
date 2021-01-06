#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#define CONFIG_LED_PIN 32
#define ESP_INTR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0

TaskHandle_t blink_task_handle = NULL;
TaskHandle_t heap_task_handle = NULL;

void blink_task(void *args) {
    printf("START TASK: %s\n", pcTaskGetTaskName(blink_task_handle));
    int c = 0;
    while (1) {
        vTaskSuspend(heap_task_handle);
        printf("[%d] Led OFF - %d\n", c, eTaskGetState(heap_task_handle));
        vTaskDelay(pdMS_TO_TICKS(1000));
        c = xTaskGetTickCount();

        vTaskResume(heap_task_handle);
        printf("[%d] Led ON - %d\n", c, eTaskGetState(heap_task_handle));
        vTaskDelay(pdMS_TO_TICKS(1000));
        c = xTaskGetTickCount();

        if (c == 401) {
            vTaskDelete(NULL);
            printf("[%d] DELETE hello_task - %d\n", c, eTaskGetState(heap_task_handle));
        }
    }
}

void heap_task(void *args) {
    int c = 0;
    while (1) {
        c = xTaskGetTickCount();
        printf("[%d] FREE HEAP: %d\n", c, esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void) {
    printf("START\n");

}