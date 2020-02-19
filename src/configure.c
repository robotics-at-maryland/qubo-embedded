/* Ross Baehr, Nathaniel Renegar
   R@M 2020
   ross.baehr@gmail.com
   naterenegar@gmail.com
*/

#include "include/configure.h"
#include <inc/tm4c123gh6pm.h>
#include <driverlib/pwm.h>

// Need to configure pins PD0, PD1, PE4, PE5, PF0, PF1, PF2, and PF3 for PWM operation
// NOTE: This goes through the steps on page 1239 of the TM4C123G Datasheet
void configurePWM(void) {

  // Enable GPIO blocks D, E, and F
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
  {
  }
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
  {
  }

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }

  // Enable PWM Module 1
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
  {
  }

  ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_8);


  // Write to GPIOLOCK register to unlock GPIOCR for port F (see page 684 of TM4C123G datasheet)
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R |= 0x00000001;

  // Set the alternate function of each pin to be PWM
  ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);
  ROM_GPIOPinConfigure(GPIO_PD1_M1PWM1);
  ROM_GPIOPinConfigure(GPIO_PE4_M1PWM2);
  ROM_GPIOPinConfigure(GPIO_PE5_M1PWM3);
  ROM_GPIOPinConfigure(GPIO_PF0_M1PWM4);
  ROM_GPIOPinConfigure(GPIO_PF1_M1PWM5);
  ROM_GPIOPinConfigure(GPIO_PF2_M1PWM6);
  ROM_GPIOPinConfigure(GPIO_PF3_M1PWM7);

  // Configure pins to be used by PWM peripheral
  ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  ROM_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
  ROM_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 |
                     GPIO_PIN_2 | GPIO_PIN_3);


  // Configure PWM Generators 0-3 for countdown mode with immediate updates

  ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
  ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
  ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
  ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

  // Want PWM freq of 200 Hz, period of 5000 us
  // 5000 us / 0.16 us = 31250 ticks

  ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 31250 - 1);
  ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 31250 - 1);
  ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 31250 - 1);
  ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 31250 - 1);

}

void configureUART(void)
{
  // UART0:
  //
  // Enable the GPIO Peripheral used by the UART.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  //
  // Enable UART0
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  //
  // Configure GPIO Pins for UART mode.
  //
  ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
  ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  //
  // Use the internal 16MHz oscillator as the UART clock source.
  //
  ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

  // Configure the UART to communicate with the computer
  ROM_UARTConfigSetExpClk(UART0_BASE, 16000000, 115200,
      UART_CONFIG_PAR_NONE |UART_CONFIG_STOP_ONE | UART_CONFIG_WLEN_8);

  //enable the FIFO, and configure it
  ROM_UARTFIFOEnable(UART0_BASE);
  ROM_UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

  // Disable the sending interrupt
  ROM_UARTIntDisable(UART0_BASE, 0xFFFFFFFF);
  // Enable UART0 receive and receive timeout
  ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

  ROM_IntEnable(INT_UART0);

  ROM_UARTEnable(UART0_BASE);


  #ifdef DEBUG
  //
  // Initialize the UART for console I/O.
  //
  UARTStdioConfig(0, 115200, 16000000);

  UARTprintf("\nUART0 configured\n");
  #endif



  // -----------------------------------------------------------
  // UART1:

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

  //
  // Enable port PC4 for UART1 U1RX
  //
  ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4);
  ROM_GPIOPinConfigure(GPIO_PC4_U1RX);

  // Enable port PC5 for UART1 U1TX
  ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5);
  ROM_GPIOPinConfigure(GPIO_PC5_U1TX);

  //
  // Use the internal 16MHz oscillator as the UART clock source.
  //
  ROM_UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

  ROM_UARTConfigSetExpClk(UART1_BASE, 16000000, 38400,
      UART_CONFIG_PAR_NONE |UART_CONFIG_STOP_ONE | UART_CONFIG_WLEN_8);

  ROM_UARTFIFOEnable(UART1_BASE);
  ROM_UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

  ROM_UARTIntDisable(UART1_BASE, 0xFFFFFFFF);
  // Enable UART1 receive and receive timeout
  ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

  ROM_IntEnable(INT_UART1);

  ROM_UARTEnable(UART1_BASE);

  #ifdef DEBUG
  UARTprintf("UART1 configured\n");
  #endif

}

// FIXME: Pin conflict between LED driver pins and PWM driver pins
void configureGPIO(void) {
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }
  //
  // Configure the GPIO port for the LED operation.
  //
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void configureI2C(void) {
  //
  // Enable the peripherals used by this example.
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  //
  // Configure the pin muxing for I2C0 functions on port B2 and B3.
  // This step is not necessary if your part does not support pin muxing.
  // TODO: change this to select the port/pin you are using.
  //
  ROM_GPIOPinConfigure(GPIO_PB2_I2C0SCL);
  ROM_GPIOPinConfigure(GPIO_PB3_I2C0SDA);

  // Select the I2C function for these pins.
  ROM_GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
  ROM_GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);


  //
  // Initialize the I2C master.
  //
  ROM_I2CMasterInitExpClk(I2C0_BASE, ROM_SysCtlClockGet(), false);

  //
  // Enable interrupts for Arbitration Lost, Stop, NAK, CLock lLow Timeout and Data
  ROM_I2CMasterIntEnableEx(I2C0_BASE, (I2C_MASTER_INT_ARB_LOST |
                                   I2C_MASTER_INT_STOP | I2C_MASTER_INT_NACK |
                                   I2C_MASTER_INT_TIMEOUT | I2C_MASTER_INT_DATA));

  //
  // Enable the I2C interrupt.
  //
  ROM_IntEnable(INT_I2C0);
  ROM_IntEnable(INT_I2C3);

  #ifdef DEBUG
  UARTprintf("I2C configured\n");
  #endif
}
