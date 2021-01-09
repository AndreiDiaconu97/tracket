#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#define ESP_INTR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
SemaphoreHandle_t xSemaphore = NULL;
TaskHandle_t ISR = NULL;

void IRAM_ATTR button_isr_handler(void *arg) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}

void task1(void *arg) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("hello from task 1 [%d]\n", xTaskGetTickCount());
        xSemaphoreGive(xSemaphore);
    }
}

void task2(void *arg) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100));
        printf("waiting the button!\n");
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
            printf("got message! [%d] \n", xTaskGetTickCount());
        }
    }
}

void app_main() {
    printf("START\n");

    gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE); // enable interrupt on falling (1->0) edge for button pin

    //Install the drivers GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);                   // install ISR service with default configuration
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL); // attach the interrupt service routine

    xSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTask2Handle, 1);
}