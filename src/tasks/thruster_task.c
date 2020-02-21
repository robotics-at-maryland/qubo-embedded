#include "tasks/include/thruster_task.h"
#include <stdio.h>

bool thruster_task_init() {
  if ( xTaskCreate(thruster_task, (const portCHAR *)"Thruster", 256, NULL,
                   tskIDLE_PRIORITY + 3, NULL) != pdTRUE) {
    return true;
  }
  return false;
}

/* NOTE: The factor of 1.01 is a calibration offest determined emperically */

static inline uint16_t pca_9685_throttle_scale(float throttle)
{
  if (throttle > 1.0)
  {
    throttle = 1.0;
  }
  else if (throttle < -1.0)
  {
    throttle = -1.0;
  }


  return (uint16_t) (((((throttle * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 2) +
                     ZERO_THROTTLE_WIDTH) * 1.01) + 1) / MIN_TIME_STEP);
}

static inline uint16_t pca_9685_pwm_scale(uint16_t pulse_width)
{
  if (pulse_width > MAX_PULSE_WIDTH)
  {
    pulse_width = MAX_PULSE_WIDTH;
  }
  else if (pulse_width < MIN_PULSE_WIDTH)
  {
    pulse_width = MIN_PULSE_WIDTH;
  }

  return (uint16_t) (((pulse_width * 1.01) + 1) / MIN_TIME_STEP);
}


static void thruster_task(void *params) {
  struct Thruster_Set thruster_set;
  bool init = false;
  volatile int i = 0;
  volatile int j = 0;
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;


  pca9685_begin(I2C0_BASE, PCA_ADDR);
  pca9685_setPWMFreq(I2C0_BASE, PWM_FREQ);

  // With current PCA9685, here are the offsets:
  // 1900 - 1880 = 20 us
  // 1500 - 1484 = 16 us
  // 1100 - 1088 = 12 us
  // Calculation for us offset:
  // (1900 - 1100) / (20 - 12) = 100 = m
  // y - 1100 = 100(x - 12)
  // y = 100x - 100
  // y = 100(x - 1)
  // (desired / 100) + 1 = us offset

 for(uint8_t i = 0; i < 10; i++)
  {
    pca9685_setPWM(I2C0_BASE, i, 0, (1500 + (1500 / 100) + 1) / (1E6/(PWM_FREQ*4096)));
  }

 vTaskDelay(xDelay * 2);

  for(uint8_t i = 0; i < 10; i++)
  {
    pca9685_setPWM(I2C0_BASE, i, 0, (1400 + (1400 / 100) + 1) / (1E6/(PWM_FREQ*4096)));
  }

  for (;;) {
    // wait indefinitely for something to come over the buffer
    /* xMessageBufferReceive(thruster_message_buffer, (void*)&thruster_set, */
    /*                       sizeof(thruster_set), portMAX_DELAY); */
    /* xQueueReceive(thruster_message_buffer, (void*)&thruster_set,
                  portMAX_DELAY); */

  }
}
