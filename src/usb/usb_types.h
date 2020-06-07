/* Nathaniel Renegar
   R@M 2020
   naterenegar@gmail.com
*/

/*
  USB 2.0 Type Definitions. See Chapters 4, 5, and 9 of the USB 2.0 spec for details.
  We plan to use tiva as a USB Device. System sensor data will be transported over the
  USB interface to the Jetson for logging and processing.
 */

#ifndef __USB_TYPES_H_
#define __USB_TYPES_H_

#include <stdint.h>


// TODO: Standard Request Definitions
// TODO: Descriptor field value definitions
// TODO: USB Device States

/*========== TYPE DEFINITIONS AND ENUMS ==========*/



enum DescriptorTypes {
  DEVICE                    = 1,
  CONFIGURATION             = 2,
  STRING                    = 3,
  INTERFACE                 = 4,
  ENDPOINT                  = 5,
  DEVICE_QUALIFIER          = 6,
  OTHER_SPEED_CONFIGURATION = 7,
  INTERFACE_POWER           = 8
};

enum StandardFeatureSelectors {
  ENDPOINT_HALT = 0,
  DEVICE_REMOTE_WAKEUP = 1,
  TEST_MODE = 2
};

/*========== VISIBLE STATE DEFINITIONS ==========*/

/*
  Device states from page 240 of USB 2.0 Specification
 */
enum VisibleStates {
  ATTACHED   = 0,
  POWERED    = 1,
  SUSPENDED  = 2,
  DEFAULT    = 3,
  ADDRESS    = 4,
  CONFIGURED = 5
};


/*========== REQUEST DEFINITIONS ==========*/

typedef struct __attribute__((packed)) DeviceRequest {
  uint8_t  bmRequestType;
  uint8_t  bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} DeviceRequest_t;

/* bmRequestType: Data Transfer Direction */
#define REQUEST_TYPE_DIR_HOST_DEV 0x00
#define REQUEST_TYPE_DIR_DEV_HOST 0x80

/* bmRequestType: Type */
#define REQUEST_TYPE_STANDARD 0x00
#define REQUEST_TYPE_CLASS    0x20
#define REQUEST_TYPE_VENDOR   0x40

/* bmRequestType: Recipient */
#define REQUEST_TYPE_RECP_DEVICE    0x00
#define REQUEST_TYPE_RECP_INTERFACE 0x01
#define REQUEST_TYPE_RECP_ENDPOINT  0x02
#define REQUEST_TYPE_RECP_OTHER     0x03

/* bRequest: Standard Request Codes (Table 9-4) */
enum RequestTypes {
  GET_STATUS        = 0,
  CLEAR_FEATURE     = 1,
  RESERVED_0        = 2,
  SET_FEATURE       = 3,
  RESERVED_1        = 4,
  SET_ADDRESS       = 5,
  GET_DESCRIPTOR    = 6,
  SET_DESCRIPTOR    = 7,
  GET_CONFIGURATION = 8,
  SET_CONFIGURATION = 9,
  GET_INTERFACE     = 10,
  SET_INTERFACE     = 11,
  SYNCH_FRAME       = 12
};


/*========== DESCRIPTOR DEFINITIONS ==========*/

typedef struct __attribute__((packed)) DeviceDesc {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t  iManufacturer;
  uint8_t  iProduct;
  uint8_t  iSerialNumber;
  uint8_t  bNumConfigurations;
} DeviceDesc_t;

typedef struct __attribute__((packed)) DeviceQualifierDesc {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint8_t  bNumConfigurations;
  uint8_t  bReserved;
} DeviceQualifierDesc_t;

typedef struct __attribute__((packed)) ConfigurationDesc {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} ConfigurationDesc_t;

typedef struct __attribute__((packed)) OtherSpeedConfigurationDesc {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} OtherSpeedConfigurationDesc_t;

typedef struct __attribute__((packed)) InterfaceDesc {
   uint8_t  bLength;
   uint8_t  bDescriptorType;
   uint8_t  bInterfaceNumber;
   uint8_t  bAlternateSetting;
   uint8_t  bNumEndpoints;
   uint8_t  bInterfaceClass;
   uint8_t  bInterfaceSubClass;
   uint8_t  bInterfaceProtocol;
   uint8_t  iInterface;
} InterfaceDesc_t;

typedef struct __attribute__((packed)) EndpointDesc {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;
} EndpointDesc_t;

#endif // __USB_TYPES_H_
