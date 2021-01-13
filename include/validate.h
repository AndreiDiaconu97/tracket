// -----------------------------------------------------------------------------------
// Check current configuration

#ifndef VALIDATE_H
#define VALIDATE_H

#include "config.h"

// Check pin settings
#if !defined(RA_PIN_DIR) || !defined(RA_PIN_STEP) || !defined(RA_PIN_ENABLE) || !defined(RA_PIN_UART)
    #error "Config.h: RA axis have missing settings!"
#endif
#if RA_PIN_DIR < 0 || RA_PIN_STEP < 0 || RA_PIN_ENABLE < 0
    #warning "Config.h: RA axis have invalid settings!"
#endif

#if !defined(DEC_PIN_DIR) || !defined(DEC_PIN_STEP) || !defined(DEC_PIN_ENABLE) || !defined(DEC_PIN_UART)
    #error "Config.h: DEC axis have missing settings!"
#endif
#if DEC_PIN_DIR < 0 || DEC_PIN_STEP < 0 || DEC_PIN_ENABLE < 0
    #warning "Config.h: DEC axis have invalid settings!"
#endif

// Check that no pin is used more than once

#endif
