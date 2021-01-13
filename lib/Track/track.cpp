#include "track.h"

// TODO - fully implement as timer
// TODO - implement workload monitoring (e.g.: long last_loop_micros = 0; )

track::track() {
    my_c = sidereal_day;
    my_a = RA_PIN_DIR;
}

track::~track() {
}