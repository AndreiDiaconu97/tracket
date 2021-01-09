#ifndef AXIS_RA_H
#define AXIS_RA_H

struct Axis_RA {
    float x;
    float y;
};

void Axis_RA__init(struct Axis_RA *self);
void Axis_RA__setCoordinates(struct Axis_RA *self, float x, float y);
float Axis_RA__getXCoordinate(struct Axis_RA *self);
float Axis_RA__getYCoordinate(struct Axis_RA *self);

#endif