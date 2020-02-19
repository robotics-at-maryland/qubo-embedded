/* Jeremy Weed
 * R@M 2017
 * jweed262@umd.edu
 */

#ifndef _THRUSTER_TEST_H_
#define _THRUSTER_TEST_H_

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>

#include "include/intertask_messages.h"

// Hardware libraries
#include "lib/include/pca9685.h"
#include "lib/include/rgb.h"

// Qubobus
#include "qubobus.h"

// TODO: Need to set thrust limiting to ensure we don't draw too much current

// which bus on the Tiva the PCA9685 is connected to
// FIXME: Find a better way to do this, it's messy and can cause headaches
#define I2C_BUS I2C0_BASE

// I2C address of the PCA9685
#define PCA_ADDR 0b1011111

// Frequency of the PWM on the PCA9685.  It's a float.
#define PWM_FREQ 244.0

// Maximum time, in microseconds, to set the PWM to
#define MAX_PULSE 1900

// Minimum time, in microseconds, to set the PWM to
#define MIN_PULSE 1100

// Pulse time, in microseconds, for zero throttle (based on BlueRobotics Basic ESC)
#define ZERO_THROTTLE 1500

// PCA has a 4096-counter where each tick is 1/4096 of the PWM_FREQ. This is used as
// reference for the phase shift of the start and stop times of your pulse.
// The frequency of the counter is thus PWM_FREQ * 4096.
#define MIN_TIME_STEP ( 1E6 / (PWM_FREQ * 4096))

// Map throttles in the range [-1 : 1] to PWM pulse lengths, then scale to PCA counter ticks
// x = 1 corresponds to 1900 us pulse length, and x = -1 corresponds to 1100 us pulse length
#define THRUSTER_SCALE(x) ((((x * (MAX_PULSE-MIN_PULSE) / 2 + ZERO_THROTTLE) * 1.01) + 1) / MIN_TIME_STEP)

// TODO: Add extra PWM parameter defines to make this work for different TM4C123G PWM Peripheral configs
#define TIVA_PWM_US_SCALE(x) ((x / 5000.0) * 31250)
#define TIVA_PWM_THROTTLE_SCALE(x) (((x * ((MAX_PULSE - MIN_PULSE) / 2) + ZERO_THROTTLE) / 5000.0) * 31250)


bool thruster_task_init();
static void thruster_task(void *params);

#endif
