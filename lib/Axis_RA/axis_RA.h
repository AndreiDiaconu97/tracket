#ifndef AXIS_RA_H
#define AXIS_RA_H

struct Axis_RA {
    float x;
    float y;
};

void rotator__init(struct Axis_RA *self);
void rotator__setCoordinates(struct Axis_RA *self, float x, float y);
float rotator__getXCoordinate(struct Axis_RA *self);
float rotator__getYCoordinate(struct Axis_RA *self);

#endif