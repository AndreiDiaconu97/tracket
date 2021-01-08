#ifndef ROTATOR_H
#define ROTATOR_H

struct rotator {
    float x;
    float y;
};

void rotator__init(struct rotator *self);
void rotator__setCoordinates(struct rotator *self, float x, float y);
float rotator__getXCoordinate(struct rotator *self);
float rotator__getYCoordinate(struct rotator *self);

#endif