#include "tasks/include/thruster_task.h"

#include <driverlib/pwm.h>

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
  return (uint16_t) (((((throttle * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 2) +
                     ZERO_THROTTLE_WIDTH) * 1.01) + 1) / MIN_TIME_STEP);
}

static inline uint16_t pca_9685_pwm_scale(uint16_t pulse_width)
{
  return (uint16_t) (((pulse_width * 1.01) + 1) / MIN_TIME_STEP);
}


static inline uint32_t tiva_throttle_scale(float throttle)
{
  return (uint32_t) ((((throttle * ((MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 2.0))
                      + ZERO_THROTTLE_WIDTH) / TIVA_PWM_PERIOD) * TIVA_PWM_TICKS);
}


static inline uint32_t tiva_pwm_scale(uint32_t pulse_width)
{
  return (uint32_t) ((pulse_width / TIVA_PWM_PERIOD) * TIVA_PWM_TICKS);
}

static void thruster_task(void *params) {
  struct Thruster_Set thruster_set;
  bool init = false;
  int i = 0;
  int j = 0;
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

  // PWM is configured to have period of 5000 us (freq 200 Hz) divided into 31250 ticks
  // (1500 / 5000) * 31250 = 9375
  
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, tiva_throttle_scale(0.5));


  // With PWM period, ticks, and pulse width set, we're ready to enable the generators
  ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
  ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1);
  ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_2);
  ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3);

  // Now enable the outputs
  ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT
                     | PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);
  ROM_PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT | PWM_OUT_5_BIT
                     | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);

  vTaskDelay(xDelay);

  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, tiva_throttle_scale(0));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, tiva_throttle_scale(0));

  vTaskDelay(xDelay);

  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, tiva_throttle_scale(0.5));
  ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, tiva_throttle_scale(0.5));

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

  for (;;) {
    // wait indefinitely for something to come over the buffer
    /* xMessageBufferReceive(thruster_message_buffer, (void*)&thruster_set, */
    /*                       sizeof(thruster_set), portMAX_DELAY); */
    /* xQueueReceive(thruster_message_buffer, (void*)&thruster_set,
                  portMAX_DELAY); */
  }
}
