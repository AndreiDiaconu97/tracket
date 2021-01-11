#ifndef AXIS_RA_H
#define AXIS_RA_H

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

esp_timer_handle_t track_timer;

typedef enum { Start,
               Resume,
               Stop,
               Delete
} track_op;

typedef struct {
    int  pinStep, pinDir, pinEnable; // driver pins
    bool dir, step;
    bool isEnabled;
    int  pos;   // steps (should convert to some astronomical unit)
    int  speed; // step/s (should convert to some astronomical unit)
    int  stepTime;
} Axis_RA;

void Axis_RA__init(Axis_RA *self, int pinDir, int pinStep, int pinEnable);
void Axis_RA__task_track(Axis_RA *self);
void Axis_RA__task_track_handle(Axis_RA *self, TaskHandle_t handle, track_op operation);

void IRAM_ATTR track_isr(Axis_RA *self);

void Axis_RA__driver_enable(Axis_RA *self, bool toEnable);
void Axis_RA__driver_direction(Axis_RA *self, bool dir);
void Axis_RA__driver_speed(Axis_RA *self, int speed);

#endif