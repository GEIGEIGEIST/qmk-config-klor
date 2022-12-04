// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "config_common.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* i2c */
#define I2C_DRIVER I2CD2

/* communication between sides */
#define SERIAL_PIO_USE_PIO1

/* audio support */
//#undef AUDIO_PIN
//#define AUDIO_PIN GP9
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4