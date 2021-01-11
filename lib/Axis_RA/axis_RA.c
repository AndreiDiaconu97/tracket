#include "axis_RA.h"

void Axis_RA__init(Axis_RA *self, int pinDir, int pinStep, int pinEnable) {
    self->pinStep   = pinStep;
    self->pinDir    = pinDir;
    self->pinEnable = pinEnable;

    self->pos = 0;
    Axis_RA__driver_speed(self, 10);

    gpio_pad_select_gpio(self->pinDir);
    gpio_pad_select_gpio(self->pinStep);
    gpio_pad_select_gpio(self->pinEnable);
    gpio_set_direction(self->pinDir, GPIO_MODE_OUTPUT);
    gpio_set_direction(self->pinStep, GPIO_MODE_OUTPUT);
    gpio_set_direction(self->pinEnable, GPIO_MODE_OUTPUT);

    self->step = false;
    gpio_set_level(self->pinStep, self->step);

    Axis_RA__driver_enable(self, false);
    Axis_RA__driver_direction(self, true);
}

void Axis_RA__driver_enable(Axis_RA *self, bool toEnable) {
    self->isEnabled = toEnable;
    gpio_set_level(self->pinEnable, !self->isEnabled);
}

void Axis_RA__driver_direction(Axis_RA *self, bool dir) {
    self->dir = dir;
    gpio_set_level(self->pinDir, self->dir);
}

void Axis_RA__driver_speed(Axis_RA *self, int speed) {
    self->speed    = speed;
    self->stepTime = 1000000 / 2 / self->speed;
}

void IRAM_ATTR task_track_isr_handler(void *arg) {
    xTaskNotifyFromISR(axis_RA_track_handle, 1, eSetValueWithOverwrite, NULL);
}

void Axis_RA__task_track_handle(Axis_RA *self, TaskHandle_t task_track_handle, track_op operation) {
    if (task_track_handle == NULL) {
        ESP_LOGE("task_track_RA", "Handler not found");
    }

    printf("[%d] Pos: %d\n", xTaskGetTickCount(), self->pos);

    switch (operation) {
    case Start:

        break;
    case Resume:
        printf("[%d] RESUME TRACKING\n", xTaskGetTickCount());
        Axis_RA__driver_enable(self, true);
        ESP_ERROR_CHECK(esp_timer_start_periodic(task_track_timer, self->stepTime));
        vTaskResume(task_track_handle);
        break;
    case Stop:
        printf("[%d] STOP TRACKING\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(task_track_timer));
        Axis_RA__driver_enable(self, false);
        vTaskSuspend(task_track_handle);
        break;
    case Delete:
        printf("[%d] REMOVE TRACKING\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(task_track_timer));
        ESP_ERROR_CHECK(esp_timer_delete(task_track_timer));
        Axis_RA__driver_enable(self, false);
        vTaskDelete(task_track_handle);
        break;
    default:
        ESP_LOGE("task_track_RA", "Operation not supported");
        break;
    }
}

// FIXME - number of steps is not precise
// TODO - change from semaphore to signal notification (40% faster)
// TODO - being a task makes no more sense, leave it to timer interrupts
void Axis_RA__task_track(Axis_RA *self) {
    printf("[%d] START TRACKING\n", xTaskGetTickCount());

    // set timer
    const esp_timer_create_args_t task_track_timer_args = {
        .callback = &task_track_isr_handler,
        .name     = "task_track_timer" // name is optional, but may help identify the timer when debugging
    };
    ESP_ERROR_CHECK(esp_timer_create(&task_track_timer_args, &task_track_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(task_track_timer, self->stepTime));
    Axis_RA__driver_enable(self, true);

    while (xTaskNotifyWait(0, ULONG_MAX, NULL, portMAX_DELAY)) {
        self->step = !self->step;
        gpio_set_level(self->pinStep, self->step);

        if (!self->step) {
            self->dir ? (self->pos++) : (self->pos--);
        }
    }
}
