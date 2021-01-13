// -----------------------------------------------------------------------------------
// Check current configuration

#ifndef VALIDATE_H
#define VALIDATE_H

#include "config.h"

// Check pin settings
#if !defined(AXIS_RA_PIN_DIR) || !defined(AXIS_RA_PIN_STEP) || !defined(AXIS_RA_PIN_ENABLE) || !defined(AXIS_RA_PIN_UART)
    #error "Config.h: AXIS_RA have missing settings!"
#endif
#if AXIS_RA_PIN_DIR < 0 || AXIS_RA_PIN_STEP < 0 || AXIS_RA_PIN_ENABLE < 0
    #warning "Config.h: AXIS_RA have invalid settings!"
#endif

#if !defined(AXIS_DEC_PIN_DIR) || !defined(AXIS_DEC_PIN_STEP) || !defined(AXIS_DEC_PIN_ENABLE) || !defined(AXIS_DEC_PIN_UART)
    #error "Config.h: AXIS_DEC have missing settings!"
#endif
#if AXIS_DEC_PIN_DIR < 0 || AXIS_DEC_PIN_STEP < 0 || AXIS_DEC_PIN_ENABLE < 0
    #warning "Config.h: AXIS_DEC have invalid settings!"
#endif

// Check that no pin is used more than once

#endif
