#include "rotator.h"

void rotator__init(struct rotator *self) {
    // TODO: load fron config file
    self->x = 0.2;
    self->y = 0.1;
}

void rotator__setCoordinates(struct rotator *self, float x, float y) {
    self->x = x;
    self->y = y;
}

float rotator__getXCoordinate(struct rotator *self) {
    return self->x;
}

float rotator__getYCoordinate(struct rotator *self) {
    return self->y;
}