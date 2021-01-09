#include "axis_RA.h"

void Axis_RA__init(struct Axis_RA *self) {
    // TODO: load fron config file
    self->x = 0.2;
    self->y = 0.1;
}

void Axis_RA__setCoordinates(struct Axis_RA *self, float x, float y) {
    self->x = x;
    self->y = y;
}

float Axis_RA__getXCoordinate(struct Axis_RA *self) {
    return self->x;
}

float Axis_RA__getYCoordinate(struct Axis_RA *self) {
    return self->y;
}