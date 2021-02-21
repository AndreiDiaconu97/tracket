// -----------------------------------------------------------------------------------
// Global variables

#ifndef GLOBALS_H
#define GLOBALS_H

// TODO - put here global structs (Axis...etc..)

// Time keeping --------------------------------------------------------------------------------------------------------------------
// REVIEW
extern float sidereal_day;
extern long  siderealTimer;      // counter to issue steps during tracking
extern long  PecSiderealTimer;   // time since worm wheel zero index for PEC
extern long  guideSiderealTimer; // counter to issue steps during guiding
extern long  siderealInterval;
extern long  masterSiderealInterval; // default = 15956313 ticks per sidereal second, where a tick
                                     // is 1/16 uS this is stored in EEPROM which is updated/adjusted
                                     // with the ":T+#" and ":T-#" commands a higher number here means
                                     // a longer count which slows down the sidereal clock

// Location ------------------------------------------------------------------------------------------------------------------------
// REVIEW
extern double latitude;
extern double latitudeSign;
extern double cosLat;
extern double sinLat;
extern double longitude;

// Coordinates ---------------------------------------------------------------------------------------------------------------------
// TODO
// home coords...
// tracking coords for each axis...
// goto start and end coords for each axis...

// Status --------------------------------------------------------------------------------------------------------------------------
// FIXME
typedef struct {
    bool dir;
    bool isEnabled;
    bool isRunning;
    int  pos;   // steps (should convert to some astronomical unit)
    int  speed; // step/s (should convert to some astronomical unit)
} Axis_RA;
extern Axis_RA axis_RA;

// Tracking: 	none, sidereal, goTo
// Park status:	not_parked, parking, parked, park_fail, park_unknown

typedef enum {
    ERR_NONE,
    ERR_MOTOR_FAULT,
    ERR_ALT_MIN,
    ERR_LIMIT_SENSE,
    ERR_DEC,
    ERR_AZM,
    ERR_UNDER_POLE,
    ERR_MERIDIAN,
    ERR_SYNC,
    ERR_PARK,
    ERR_GOTO_SYNC,
    ERR_UNSPECIFIED,
    ERR_ALT_MAX,
    ERR_WEATHER_INIT,
    ERR_SITE_INIT
} GeneralErrors;
extern GeneralErrors generalError;

typedef enum {
    CE_NONE,
    CE_0,
    CE_CMD_UNKNOWN,
    CE_REPLY_UNKNOWN,
    CE_PARAM_RANGE,
    CE_PARAM_FORM,
    CE_ALIGN_FAIL,
    CE_ALIGN_NOT_ACTIVE,
    CE_NOT_PARKED_OR_AT_HOME,
    CE_PARKED,
    CE_PARK_FAILED,
    CE_NOT_PARKED,
    CE_NO_PARK_POSITION_SET,
    CE_GOTO_FAIL,
    CE_LIBRARY_FULL,
    CE_GOTO_ERR_BELOW_HORIZON,
    CE_GOTO_ERR_ABOVE_OVERHEAD,
    CE_SLEW_ERR_IN_STANDBY,
    CE_SLEW_ERR_IN_PARK,
    CE_GOTO_ERR_GOTO,
    CE_SLEW_ERR_OUTSIDE_LIMITS,
    CE_SLEW_ERR_HARDWARE_FAULT,
    CE_MOUNT_IN_MOTION,
    CE_GOTO_ERR_UNSPECIFIED,
    CE_NULL
} CommandErrors;
extern CommandErrors commandError;

// Guide command -------------------------------------------------------------------------------------------------------------------
// TODO
// guide_rates
// guide_mode	: pulse, continue

// PEC control ---------------------------------------------------------------------------------------------------------------------
// TODO

#endif