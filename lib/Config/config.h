// ---------------------------------------------------------------------------------------------------------------------------------
// Project configuration

#ifndef CONFIG_H
#define CONFIG_H

#include "stdbool.h"

#define OFF -1
#define ON  -2

#define DEBUG_ON // DEBUG_ON or DEBUG_OFF

// ---------------------------------------------------------------------------------------------------------------------------------
// PIN MAP

/* 
PINS NOT RECOMMENDED AS GPIO 
	BOOT SENSITIVE	:	0, 1, 3, 5, 12, 14, 15
	SPI				:	6-11
	INPUT ONLY		:	34, 35, 36, 39
	WIFI (?) 		:	26 (sould work as GPIO, but not as ADC)
*/

#define RA_PIN_DIR    27
#define RA_PIN_STEP   26
#define RA_PIN_ENABLE 25
#define RA_PIN_UART   -1

#define DEC_PIN_DIR    -1
#define DEC_PIN_STEP   -1
#define DEC_PIN_ENABLE -1
#define DEC_PIN_UART   -1

// ---------------------------------------------------------------------------------------------------------------------------------
// Stepper driver models (also see ~/OnStep/src/sd_drivers/Models.h for additional infrequently used models and more info.):
// A4988, DRV8825, LV8729, S109, SSS TMC2209*, TMC2130* **, and TMC5160* ***
// * = add _QUIET (stealthChop tracking) or _VQUIET (stealthChop tracking & slew,) for example "TMC2130_VQUIET"
// ** = SSS TMC2130 if you choose to set stepper driver current (in mA) set Vref pot. 2.5V instead of by motor current as usual.
// *** = SSS TMC5160 you must set stepper driver current (in mA) w/ #define AXISn_TMC_IRUN (IHOLD, etc.)

// AXIS1 RA/AZM
// see https://onstep.groups.io/g/main/wiki/6-Configuration#AXIS1
#define AXIS1_STEPS_PER_DEGREE 12800.0 //   Number of steps per degree:                                        				<-Req'd
//                                          n = (stepper_steps * micro_steps * overall_gear_reduction)/360.0
#define AXIS1_STEPS_PER_WORMROT 12800 //    n. Number of steps per worm rotation (PEC Eq mode only:)               		 	<-Req'd
//                                          n = (AXIS1_STEPS_PER_DEGREE*360)/reduction_final_stage

#define AXIS1_DRIVER_MODEL           OFF //    OFF, (See above.) Stepper driver model.                                      <-Often
#define AXIS1_DRIVER_MICROSTEPS      OFF //    OFF, n. Microstep mode when tracking.                                        <-Often
#define AXIS1_DRIVER_MICROSTEPS_GOTO OFF //    OFF, n. Microstep mode used during gotos.                                     Option
#define AXIS1_DRIVER_IHOLD           OFF //    OFF, n, (mA.) Current during standstill. OFF uses IRUN/2.0                    Option
#define AXIS1_DRIVER_IRUN            OFF //    OFF, n, (mA.) Current during tracking, appropriate for stepper/driver/etc.    Option
#define AXIS1_DRIVER_IGOTO           OFF //    OFF, n, (mA.) Current during slews. OFF uses same as IRUN.                    Option
#define AXIS1_DRIVER_REVERSE         OFF //    OFF, ON Reverses movement direction, or reverse wiring instead to correct.   <-Often
#define AXIS1_DRIVER_STATUS          OFF //    OFF, TMC_SPI, HIGH, or LOW.  Polling for driver status info/fault detection.  Option

#define AXIS1_LIMIT_UNDER_POLE 180 //    180, n. Where n=150..180 (degrees.) Max HA hour angle + or - for Eq modes.    Adjust
#define AXIS1_LIMIT_MAXAZM     360 //    360, n. Where n=180..360 (degrees.) Max Azimuth + or - for AltAzm mode only.  Adjust

// AXIS2 DEC/ALT
// see https://onstep.groups.io/g/main/wiki/6-Configuration#AXIS2
#define AXIS2_STEPS_PER_DEGREE 12800.0 //   12800, n. Number of steps per degree:                                          <-Req'd
//                                          n = (stepper_steps * micro_steps * overall_gear_reduction)/360.0

#define AXIS2_DRIVER_MODEL           OFF //    OFF, (See above.) Stepper driver model.                                      <-Often
#define AXIS2_DRIVER_MICROSTEPS      OFF //    OFF, n. Microstep mode when tracking.                                        <-Often
#define AXIS2_DRIVER_MICROSTEPS_GOTO OFF //    OFF, n. Microstep mode used during gotos.                                     Option
#define AXIS2_DRIVER_IHOLD           OFF //    OFF, n, (mA.) Current during standstill. OFF uses IRUN/2.0                    Option
#define AXIS2_DRIVER_IRUN            OFF //    OFF, n, (mA.) Current during tracking, appropriate for stepper/driver/etc.    Option
#define AXIS2_DRIVER_IGOTO           OFF //    OFF, n, (mA.) Current during slews. OFF uses same as IRUN.                    Option
#define AXIS2_DRIVER_POWER_DOWN      OFF //    OFF, ON Powers off 10sec after movement stops or 10min after last<=1x guide.  Option
#define AXIS2_DRIVER_REVERSE         OFF //    OFF, ON Reverses movement direction, or reverse wiring instead to correct.   <-Often
#define AXIS2_DRIVER_STATUS          OFF //    OFF, TMC_SPI, HIGH, or LOW.  Polling for driver status info/fault detection.  Option
#define AXIS2_TANGENT_ARM            OFF //    OFF, ON +limit range below. Set cntr w/[Reset Home] Return cntr w/[Find Home] Infreq

#define AXIS2_LIMIT_MIN -91 //    -91, n. Where n=-91..0 (degrees.) Minimum allowed declination.                Infreq
#define AXIS2_LIMIT_MAX 91  //     91, n. Where n=0..91 (degrees.) Maximum allowed declination.                 Infreq

// TRACKING BEHAVIOUR -------------------------------------------- see https://onstep.groups.io/g/main/wiki/6-Configuration#TRACKING
#define TRACK_AUTOSTART     OFF //    OFF, ON Start with tracking enabled.                                          Option
#define TRACK_BACKLASH_RATE 25  //    25, n. Where n=2..50 (x sidereal rate) during backlash takeup.               Option
//                                    Too fast motors stall/gears slam or too slow and sluggish in backlash.

// SLEWING BEHAVIOUR ---------------------------------------------- see https://onstep.groups.io/g/main/wiki/6-Configuration#SLEWING
#define SLEW_RATE_BASE_DESIRED 1.0 //    1.0, n. Desired slew rate in deg/sec. Adjustable at run-time from            <-Req'd
//                                       1/2 to 2x this rate, and as MCU performace considerations require.
#define SLEW_RATE_MEMORY       OFF //    OFF, ON Remembers rates set across power cycles.                              Option
#define SLEW_ACCELERATION_DIST 5.0 //    5.0, n, (degrees.) Approx. distance for acceleration (and deceleration.)      Adjust
#define SLEW_RAPID_STOP_DIST   2.5 //    2.0, n, (degrees.) Approx. distance required to stop when a slew              Adjust
//                                       is aborted or a limit is exceeded.

#define MFLIP_SKIP_HOME         OFF //    OFF, ON Goto directly to the destination without visiting home position.      Option
#define MFLIP_PAUSE_HOME_MEMORY OFF //    OFF, ON Remember meridian flip pause at home setting across power cycles.     Option
#define MFLIP_AUTOMATIC_MEMORY  OFF //    OFF, ON Remember automatic meridian flip setting across power cycles.         Option

// ---------------------------------------------------------------------------------------------------------------------------------
// LIMITS - default allowed degrees past the meridian on the East and West sides of the pier
#define AXIS1_LIMIT_MERIDIAN_E 7.5
#define AXIS1_LIMIT_MERIDIAN_W 7.5

#endif
