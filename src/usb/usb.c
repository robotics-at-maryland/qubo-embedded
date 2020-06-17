
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/usb.h"
#include "inc/hw_memmap.h"
#include "usb/usb.h"

/****PRIVATE VARIABLES****/
static usb_state_t usb_state = DEFAULT;

static volatile uint32_t rx_size = 0;
static volatile uint8_t rx_buffer[256];

static const DeviceDesc_t tiva_device_desc =
{
 .bLength = 18,
 .bDescriptorType = DEVICE_DESC,
 .bcdUSB = 0x0200,
 .bDeviceClass = 0,
 .bDeviceSubClass = 0,
 .bDeviceProtocol = 0,
 .bMaxPacketSize0 = 64,
 .idVendor = 0x5555,
 .idProduct = 0x5555,
 .bcdDevice = 0x0001,
 .iManufacturer = 0,
 .iProduct = 0,
 .iSerialNumber = 0,
 .bNumConfigurations = 1
};

/****PRIVATE PROTOTYPES****/
static void usb_get_descriptor_handler(uint8_t desc_type, uint8_t desc_idx);


/****PUBLIC VARIABLES****/
uint16_t address;


void usb_state_machine_cb(void)
{
  // NOTE: For now, assuming all xfers are coming from endpoint 0
  // In the future, adjust the ISR to flag which endpoint it came from
 
  if (rx_size)
  {
    uint8_t bm_request_type = rx_buffer[0];
    uint8_t request = rx_buffer[1];

    switch(request)
    {
      case GET_STATUS:
        break;
      case CLEAR_FEATURE:
        break;
      case RESERVED_0:
        // TODO: Read spec and determine if we must throw error if we get here
        break;
      case SET_FEATURE:
        break;
      case RESERVED_1:
        // TODO: Read spec and determine if we must throw error if we get here
        break;
      case SET_ADDRESS:
        if (bm_request_type == 0x00)
        {
          address = (rx_buffer[2] << 8 ) | rx_buffer[3];
          USBDevAddrSet(USB0_BASE, address);
        }
        break;
      case GET_DESCRIPTOR:
        if (bm_request_type == 0x80)
        {
          uint8_t desc_type = rx_buffer[3];
          uint8_t desc_idx  = rx_buffer[2];
          usb_get_descriptor_handler(desc_type, desc_idx);
        }
        break;
      case SET_DESCRIPTOR:
        break;
      case GET_CONFIGURATION:
        break;
      case SET_CONFIGURATION:
        break;
      case GET_INTERFACE:
        break;
      case SET_INTERFACE:
        break;
      case SYNCH_FRAME:
        break;
      default:
        break;
    }

    rx_size = 0;
  }

  return;
}

static void usb_get_descriptor_handler(uint8_t desc_type, uint8_t desc_idx)
{
  switch(desc_type)
  {
    case DEVICE_DESC:
      if(desc_idx == 0)
      {
        USBEndpointDataPut(USB0_BASE, 0, (uint8_t *)&tiva_device_desc, tiva_device_desc.bLength);
      }
    default:
      break;
  }
}

// NOTE: This interrupt handler uses the shared resources rx_buffer and rx_size
// You must take caution when using these by disabling and reenabling irq's to
// prevent preemption during a read-write-modify
void USB0IntHandler(void) {
  // Clear USB0 related interrupt flags
  uint32_t endpoint_flags = USBIntStatusEndpoint(USB0_BASE);
  uint32_t status_flags = USBIntStatusControl(USB0_BASE);

  // Recieve packet
 
  // TODO: Have this done with DMA. Disable Endpoint interrupts and
  // enable DMA channel interrupts (i.e. DMA sends interrupt when packet is ready)
  rx_size = USBEndpointDataAvail(USB0_BASE, 0);
  if(endpoint_flags == USB_INTEP_0 && USBEndpointDataGet(USB0_BASE, 0, rx_buffer, &rx_size) == 0)
  {
    usb_state_machine_cb();
  }
  status_flags ^= endpoint_flags;
}
