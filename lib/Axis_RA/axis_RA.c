#include "axis_RA.h"

typedef struct {
    int  pinStep, pinDir, pinEnable; // driver pins
    bool dir, step;
    bool isEnabled;
    int  pos;   // steps (should convert to some astronomical unit)
    int  speed; // step/s (should convert to some astronomical unit)
    int  stepTime;
} Axis_RA;

// Private functions
void IRAM_ATTR tracker_isr(Axis_RA *self);

void Axis_RA_init(Axis_RA *self, Axis_RA_config *config);
void Axis_RA__driver_enable(Axis_RA *self, bool toEnable);
void Axis_RA__driver_direction(Axis_RA *self, bool dir);
void Axis_RA__driver_speed(Axis_RA *self, int speed);

void TSK_tracker(Axis_RA_config *config);
void TSK_tracker_command(Axis_RA *axis_RA, esp_timer_handle_t tracker_timer, tracker_cmd cmd);

void Axis_RA_init(Axis_RA *self, Axis_RA_config *config) {
    self->pinStep   = config->pinStep;
    self->pinDir    = config->pinDir;
    self->pinEnable = config->pinEnable;
    self->pos       = config->pos;
    self->step      = false;

    gpio_pad_select_gpio(self->pinDir);
    gpio_pad_select_gpio(self->pinStep);
    gpio_pad_select_gpio(self->pinEnable);
    gpio_set_direction(self->pinDir, GPIO_MODE_OUTPUT);
    gpio_set_direction(self->pinStep, GPIO_MODE_OUTPUT);
    gpio_set_direction(self->pinEnable, GPIO_MODE_OUTPUT);

    gpio_set_level(self->pinStep, self->step);
    Axis_RA__driver_speed(self, config->speed);
    Axis_RA__driver_enable(self, false);
    Axis_RA__driver_direction(self, config->dir);
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

TaskHandle_t TSK_tracker_init(Axis_RA_config *config) {
    TaskHandle_t axis_RA_tracker_handle;
    xTaskCreate((void *)TSK_tracker, "TSK_tracker", 2048, config, 5, &axis_RA_tracker_handle);
    return axis_RA_tracker_handle;
}

void TSK_tracker(Axis_RA_config *config) {
    printf("[%d] INIT TRACKER\n", xTaskGetTickCount());

    Axis_RA axis_RA;
    Axis_RA_init(&axis_RA, config);

    // set timer
    esp_timer_handle_t            tracker_timer;
    const esp_timer_create_args_t track_timer_args = {
        .callback = (void *)&tracker_isr,
        .name     = "tracker_timer", // name is optional, but may help identify the timer when debugging
        .arg      = &axis_RA};
    ESP_ERROR_CHECK(esp_timer_create(&track_timer_args, &tracker_timer));
    Axis_RA__driver_enable(&axis_RA, true);

    // wait for command
    uint32_t command;
    while (xTaskNotifyWait(0, ULONG_MAX, &command, portMAX_DELAY)) {
        TSK_tracker_command(&axis_RA, tracker_timer, command);
    }

    TSK_tracker_command(&axis_RA, tracker_timer, Error); // Should never get here
}

// Constant steps at specified speed
void IRAM_ATTR tracker_isr(Axis_RA *axis_RA) {
    axis_RA->step = !axis_RA->step;
    gpio_set_level(axis_RA->pinStep, axis_RA->step);

    if (!axis_RA->step) {
        axis_RA->dir ? (axis_RA->pos++) : (axis_RA->pos--);
    }
}

void TSK_tracker_command(Axis_RA *axis_RA, esp_timer_handle_t tracker_timer, tracker_cmd cmd) {
    printf("[%s] received command %d\n", pcTaskGetTaskName(NULL), cmd);
    printf("[%s] pos: %d\n", pcTaskGetTaskName(NULL), axis_RA->pos);

    switch (cmd) {
    case Start:
        printf("[%d] START TRACKER\n", xTaskGetTickCount());
        Axis_RA__driver_enable(axis_RA, true);
        ESP_ERROR_CHECK(esp_timer_start_periodic(tracker_timer, axis_RA->stepTime));
        break;
    case Stop:
        printf("[%d] STOP TRACKER\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(tracker_timer));
        Axis_RA__driver_enable(axis_RA, false);
        break;
    case Error:
        printf("[%d] ERROR TRACKER\n", xTaskGetTickCount());
        ESP_ERROR_CHECK(esp_timer_stop(tracker_timer));
        Axis_RA__driver_enable(axis_RA, false);
        break;
    default:
        ESP_LOGE("TSK_tracker", "Command not supported");
        break;
    }
}