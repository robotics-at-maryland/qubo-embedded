/* Ross Baehr, Nathaniel Renegar
   R@M 2020
   ross.baehr@gmail.com
   naterenegar@gmail.com
*/

// QSCU
#include "include/configure.h"
#include "include/task_constants.h"
#include "tasks/include/read_uart0.h"
//#include "tasks/include/read_uart1.h"
#include "tasks/include/example_blink.h"
#include "tasks/include/example_uart.h"
#include "tasks/include/tiqu.h"
#include "tasks/include/thruster_task.h"
#include "lib/include/usb_serial.h"

// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>

// Tiva
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_nvic.h>
#include <driverlib/gpio.h>
#include <driverlib/i2c.h>
#include <driverlib/pin_map.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include <driverlib/uart.h>
#include <driverlib/fpu.h>

// If debug defined, can use this to print to UART
#ifdef DEBUG
#include <utils/uartstdio.h>
#endif

#include "lib/include/uart_queue.h"
#include "interrupts/include/uart0_interrupt.h"

#include "lib/include/query_i2c.h"

// Globals
#include "include/uart1_mutex.h"
#include "include/rgb_mutex.h"
//#include "include/read_uart1_queue.h"

/* #include "include/task_handles.h" */
/* #include "include/task_queues.h" */
/* #include "tasks/include/qubobus_test.h" */

SemaphoreHandle_t uart1_mutex;
SemaphoreHandle_t rgb_mutex;

extern volatile struct UART_Queue uart0_queue;
extern volatile struct UART_Queue uart1_queue;

QueueHandle_t thruster_message_buffer;

/* DECLARE_TASK_HANDLES; */
/* DECLARE_TASK_QUEUES; */

#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{
  for (;;) {
    blink_rgb(RED_LED, 1);
    UARTprintf("ERROR");
  }
}
#endif

void vApplicationStackOverflowHook( TaskHandle_t pxTask, signed char *pcTaskName ) {
  for (;;) {
#ifdef DEBUG
    UARTprintf("\nTick interrupt\n");
#endif
  }
}

// Called when a tick interrupt happens
// Can be used to confirm tick interrupt happening
void vApplicationTickHook(void) {
#ifdef DEBUG
  UARTprintf("\nTick interrupt\n");
#endif
}


int main() {

  // Enable floating point operations
  ROM_FPULazyStackingEnable();
  ROM_FPUEnable();

  // Set the clocking to run at 50 MHz from the PLL
  ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                     SYSCTL_OSC_MAIN);

  configureUART();
  configureGPIO(); // FIXME: Determine suitable PWM outputs to replace pins PF0-PF4
//  configureI2C();
  configurePWM();

  /* USB_serial_configure(); */


    uart1_mutex = xSemaphoreCreateMutex();
    rgb_mutex = xSemaphoreCreateMutex();

  // -----------------------------------------------------------------------
  // Allocate FreeRTOS data structures for tasks, these are automatically made in heap
  // -----------------------------------------------------------------------

  // Initialize the UART Queue for UART0.
  INIT_UART_QUEUE(uart0_queue, 256, 256, INT_UART0, UART0_BASE, pdMS_TO_TICKS(1000));
  INIT_UART_QUEUE(uart1_queue, 256, 256, INT_UART1, UART1_BASE, pdMS_TO_TICKS(1000));

  /* INIT_TASK_QUEUES(); */

  thruster_message_buffer = xQueueCreate(1, sizeof(struct Thruster_Set));

  //initI2C();

  // Master enable interrupts
  ROM_IntMasterEnable();

#ifdef DEBUG
  UARTprintf("Datastructures allocated\n");
#endif

  /* blink_rgb(BLUE_LED, 1); */
  // -----------------------------------------------------------------------
  // Start FreeRTOS tasks
  // -----------------------------------------------------------------------

  /* if ( i2c_test_init() ) { */
  /*   while(1){} */
  /* } */
  /*
    if ( example_blink_init() ) {
    while(1){}
    }
  */

  if (thruster_task_init()) {
    while(1){}
  } 

/*  if (tiqu_task_init()) {
    while(1){}
  } */


  /* if (qubobus_test_init() ){ */
  /*   while(1){} */
  /* } */
  /*
    if ( read_uart0_init() ) {
    while(1){}
    }
  */
  /*
    if( USB_serial_init() ){
    blink_rgb(RED_LED, 1);
    while(1){}
    }
  */
  /*
    if ( bme280_task_init()){
    while(1){}
    }
  */

  /*
    if ( example_uart_init() ) {
    while(1){}
    }
  */

  vTaskStartScheduler();

  while(1){
    blink_rgb(BLUE_LED, 1);
  }
}
