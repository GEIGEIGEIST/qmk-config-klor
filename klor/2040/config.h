// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "config_common.h"

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS



// PRO MICRO RP2040 ├───────────────────────────────────────────┐

// wiring of each half
#define MATRIX_ROW_PINS { GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP27, GP26, GP22, GP20, GP23, GP21 }
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

/*
// ADAFRUIT KB2040 ├────────────────────────────────────────────┐

// wiring of each half
#define MATRIX_ROW_PINS { GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP27, GP26, GP18, GP20, GP19, GP10 }
//#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
*/


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U


/* encoder support */
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#undef ENCODERS_PAD_A_RIGHT 
#undef ENCODERS_PAD_B_RIGHT

#define ENCODERS_PAD_A { GP28 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODERS_PAD_A_RIGHT { GP29 }
#define ENCODERS_PAD_B_RIGHT { GP28 }


/* audio support */
#undef AUDIO_PIN
//#define AUDIO_PIN GP9


/* i2c */
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define I2C_DRIVER I2CD2


/* communication between sides */
#define USE_SERIAL
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP1
#define SERIAL_PIO_USE_PIO1


/* rgb led support*/
#undef RGB_DI_PIN
#define RGB_DI_PIN GP0
