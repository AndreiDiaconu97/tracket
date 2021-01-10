// ---------------------------------------------------------------------------------------------------------------------------------
// Project configuration

#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG_ON // DEBUG_ON or DEBUG_OFF

/* 
PINS NOT RECOMMENDED AS GPIO 
	BOOT SENSITIVE	:	0, 1, 3, 5, 12, 14, 15
	SPI				:	6-11
	INPUT ONLY		:	34, 35, 36, 39
	WIFI (?) 		:	26 (sould work as GPIO, but not as ADC)
*/

// Stepper Drivers Pins
#define AXIS_RA_PIN_DIR    27
#define AXIS_RA_PIN_STEP   26
#define AXIS_RA_PIN_ENABLE 25
#define AXIS_RA_PIN_UART   -1

#define AXIS_DEC_PIN_DIR    -1
#define AXIS_DEC_PIN_STEP   -1
#define AXIS_DEC_PIN_ENABLE -1
#define AXIS_DEC_PIN_UART   -1

#endif
