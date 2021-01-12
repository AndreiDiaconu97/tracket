#ifndef AXIS_RA_H
#define AXIS_RA_H

#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef enum { Start,
               Stop,
               Error,
               Delete
} tracker_cmd;

typedef struct {
    int  pinStep, pinDir, pinEnable; // driver pins
    int  pos, speed;
    bool dir;
} Axis_RA_conf;

TaskHandle_t TSK_tracker_init(Axis_RA_conf *config);

#endif