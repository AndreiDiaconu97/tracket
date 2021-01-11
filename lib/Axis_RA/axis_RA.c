#include "axis_RA.h"

void Axis_RA__init(Axis_RA *self, int pinDir, int pinStep, int pinEnable) {
    self->pinStep   = pinStep;
    self->pinDir    = pinDir;
    self->pinEnable = pinEnable;

    self->pos = 0;
    Axis_RA__driver_speed(self, 1000);

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

void Axis_RA__task_track_handle(Axis_RA *self, TaskHandle_t task_track_handle, track_op operation) {
    if (task_track_handle == NULL) {
        ESP_LOGE("task_track_RA", "Handler not found");
    }

    printf("[%d] Pos: %d\n", xTaskGetTickCount() * 10, self->pos);

    switch (operation) {
    case Start:

        break;
    case Resume:
        printf("[%d] RESUME TRACKING\n", xTaskGetTickCount());
        Axis_RA__driver_enable(self, true);
        ESP_ERROR_CHECK(esp_timer_start_periodic(track_timer, self->stepTime));
        vTaskResume(task_track_handle);
        break;
    case Stop:
        printf("[%d] STOP TRACKING\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(track_timer));
        Axis_RA__driver_enable(self, false);
        vTaskSuspend(task_track_handle);
        break;
    case Delete:
        printf("[%d] REMOVE TRACKING\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(track_timer));
        ESP_ERROR_CHECK(esp_timer_delete(track_timer));
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

    // while (xTaskNotifyWait(0, ULONG_MAX, NULL, portMAX_DELAY)) {
    // }
}

// Constant steps at specified speed
void IRAM_ATTR track_isr(Axis_RA *self) {
    self->step = !self->step;
    gpio_set_level(self->pinStep, self->step);

    if (!self->step) {
        self->dir ? (self->pos++) : (self->pos--);
    }
}