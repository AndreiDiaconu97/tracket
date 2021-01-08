#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#define CONFIG_LED_PIN 32
#define ESP_INTR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0

TaskHandle_t ISR = NULL;

void IRAM_ATTR button_isr_handler(void *arg) {
    xTaskResumeFromISR(ISR);
}

void button_task(void *arg) {
    bool led_status = false;
    while (1) {
        vTaskSuspend(NULL);
        led_status = !led_status;
        gpio_set_level(CONFIG_LED_PIN, led_status);
        printf("Button pressed!!!\n");
    }
}

void app_main(void) {
    printf("START\n");

    gpio_pad_select_gpio(CONFIG_LED_PIN);
    gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    gpio_set_direction(CONFIG_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE); // enable interrupt on falling (1->0) edge for button pin

    //Install the drivers GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);                   // install ISR service with default configuration
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL); // attach the interrupt service routine

    xTaskCreate(button_task, "button_task", 4096, NULL, 10, &ISR);
}