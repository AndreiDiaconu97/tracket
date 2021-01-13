#include "globals.h"

// TODO - put here global structs (Axis...etc..)

// Time keeping --------------------------------------------------------------------------------------------------------------------
// REVIEW
float sidereal_day           = 86164.1;
long  siderealTimer          = 0; // counter to issue steps during tracking
long  PecSiderealTimer       = 0; // time since worm wheel zero index for PEC
long  guideSiderealTimer     = 0; // counter to issue steps during guiding
long  siderealInterval       = 15956313;
long  masterSiderealInterval = siderealInterval; // default = 15956313 ticks per sidereal second, where a tick
                                                 // is 1/16 uS this is stored in EEPROM which is updated/adjusted
                                                 // with the ":T+#" and ":T-#" commands a higher number here means
                                                 // a longer count which slows down the sidereal clock

// Location ------------------------------------------------------------------------------------------------------------------------
// REVIEW
double latitude     = 0.0;
double latitudeSign = 1.0;
double cosLat       = 1.0;
double sinLat       = 0.0;
double longitude    = 0.0;

// Coordinates ---------------------------------------------------------------------------------------------------------------------
// TODO
// home coords...
// tracking coords for each axis...
// goto start and end coords for each axis...

// Status --------------------------------------------------------------------------------------------------------------------------
// FIXME
Axis_RA axis_RA = {
    .dir       = false,
    .isEnabled = false,
    .isRunning = false,
    .pos       = 0,
    .speed     = 10};

// Tracking: 	none, sidereal, goTo
// Park status:	not_parked, parking, parked, park_fail, park_unknown

GeneralErrors generalError = ERR_NONE;
CommandErrors commandError = CE_NONE;

// Guide command -------------------------------------------------------------------------------------------------------------------
// TODO
// guide_rates
// guide_mode	: pulse, continue

// PEC control ---------------------------------------------------------------------------------------------------------------------
// TODO