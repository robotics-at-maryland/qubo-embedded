
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/usb.h"
#include "inc/hw_memmap.h"
#include "usb/usb.h"


static usb_state_t usb_state = DEFAULT;

static volatile uint32_t rx_size = 0;
static volatile uint8_t rx_buffer[256];

uint8_t address;

void usb_state_machine_cb(void)
{

  // TODO: State machine for endpoint 0 control transfers
  // Three stages of a ctrl xfer:
  //   Setup
  //   Data
  //   Status

  // NOTE: As of now, assuming all xfers are coming from endpoint 0
  // In the future, adjust the ISR to flag which endpoint it came from
 
  if (rx_size)
  {
    uint8_t bm_request_type = rx_buffer[0];
    uint8_t request = rx_buffer[1];

    switch(request)
    {
      case SET_ADDRESS:
        address = rx_buffer[2];
        // TODO: write to USB Address reg after sending status packet
        break;
      default:
        break;
    }
  }
  switch(usb_state)
  {
    case DEFAULT:
      // TODO: USB Atomic (or disable irq)
     
      break;
    case ADDRESS:
      break;
    case CONFIGURED:
      break;
    case SUSPENDED:
      break;
    case POWERED:
      break;
    case ATTACHED:
      break;
    default:
      break;
  }

  return;
 
}


// NOTE: This interrupt handler uses the shared resources rx_buffer and rx_size
// You must take caution when using these by disabling and reenabling irq's to
// prevent preemption during a read-write-modify
void USB0IntHandler(void) {
  // Clear USB0 related interrupt flags
  USBIntStatusEndpoint(USB0_BASE);
  USBIntStatusControl(USB0_BASE);

  // Recieve packet
 
  // TODO: Have this done with DMA. Disable Endpoint interrupts and
  // enable DMA channel interrupts (i.e. DMA sends interrupt when packet is ready)
  rx_size = USBEndpointDataAvail(USB0_BASE, 0);
  USBEndpointDataGet(USB0_BASE, 0, rx_buffer, &rx_size);
  usb_state_machine_cb();
}
