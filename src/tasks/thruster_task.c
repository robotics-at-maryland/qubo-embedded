#include "tasks/include/thruster_task.h"
#include <stdio.h>

bool thruster_task_init() {
  if ( xTaskCreate(thruster_task, (const portCHAR *)"Thruster", 256, NULL,
                   tskIDLE_PRIORITY + 3, NULL) != pdTRUE) {
    return true;
  }
  return false;
}

static void thruster_task(void *params) {
  struct Thruster_Set thruster_set;
  bool init = false;
  volatile int i = 0;
  volatile int j = 0;
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;


  pca9685_begin(I2C0_BASE, PCA_ADDR);
  pca9685_setPWMFreq(I2C0_BASE, PWM_FREQ);

  vTaskDelay(xDelay * 10);

  blink_rgb(BLUE_LED | GREEN_LED, 1);

  // THRUSTER TEST
  // We run this once, then task does nothing



  // First, go through each thruster and throttle up to highest safe throttle
  // TODO: Take note of current draw vs. thrust
  // TODO: Figure out mapping of thrusters to pins
  for(i = 0; i < 8; i++) { // thruster select loop
    for(j = 1; j < 8; j++) {// thrust set loop
      vTaskDelay(xDelay * 5);
      blink_rgb(BLUE_LED | GREEN_LED, 1);
      pca9685_setPWM(I2C0_BASE, i, 0, THRUSTER_SCALE(0.1*j));
      vTaskDelay(xDelay * 10);
      pca9685_setPWM(I2C0_BASE, i, 0, THRUSTER_SCALE(0));
    }
  }


  for (;;) {
    // wait indefinitely for something to come over the buffer
    /* xMessageBufferReceive(thruster_message_buffer, (void*)&thruster_set, */
    /*                       sizeof(thruster_set), portMAX_DELAY); */
    /* xQueueReceive(thruster_message_buffer, (void*)&thruster_set,
                  portMAX_DELAY); */

  }
}
