/**
 * Nathaniel Renegar
 * R@M 2020
 * naterenegar@gmail.com
 */

/** @file pni_binary.h
 *
 * @brief Defines for PNI Binary Protocol. See TRAX AHRS User Manual
 *
 */

#ifndef PNI_BINARY_H
#define PNI_BINARY_H


/** Datagram Structure
 *   __________________________________________________________
 *  |            |           |                    |            |
 *  | ByteCount  |  FrameID  |    Packet Frame    |   CRC-16   |
 *  | (uint16_t) | (uint8_t) | (1 - 4092 uint8_t) | (uint16_t) |
 *  |____________|___________|____________________|____________|
 *
 *  ByteCount: total number of bytes in the packet (including CRC-16)
 *  CRC-16: calculated from ByteCount to last byte of Packet Frame
 *  ByteCount and CRC-16 always big Endian
 */

/** FrameIDs
 *
 * @breif Allows the AHRS to determine what command is being sent
 * and the host to determine what data is being sent
 *
 */

#define K_GET_MOD_INFO               0x01
#define K_GET_MOD_INFO_RESP          0x02
#define K_SET_DATA_COMPONENTS        0x03
#define K_GET_DATA                   0x04
#define K_GET_DATA_RESP              0x05
#define K_SET_CONFIG                 0x06
#define K_GET_CONFIG                 0x07
#define K_GET_CONFIG_RESP            0x08
#define K_SAVE                       0x09
#define K_START_CAL                  0x0A
#define K_STOP_CAL                   0x0B
#define K_SET_FIR_FILTERS            0x0C
#define K_GET_FIR_FILTERS            0x0D
#define K_GET_FIR_FILTERS_RESP       0x0E
#define K_POWER_DOWN                 0x0F
#define K_SAVE_DONE                  0x10
#define K_USER_CAL_SAMPLE_COUNT      0x11
#define K_USER_CAL_SCORE             0x12
#define K_SET_CONFIG_DONE            0x13
#define K_SET_FIR_FILTERS_DONE       0x14
#define K_START_CONTINUOUS_MODE      0x15
#define K_STOP_CONTINUOUS_MODE       0x16
#define K_POWER_UP_DONE              0x17
#define K_SET_ACQ_PARAMS             0x18
#define K_GET_ACQ_PARAMS             0x19
#define K_SET_ACQ_PARAMS_DONE        0x1A
#define K_GET_ACQ_PARAMS_RESP        0x1B
#define K_POWER_DOWN_DONE            0x1C
#define K_FACTORY_MAG_COEFF          0x1D
#define K_FACTORY_MAG_COEFF_DONE     0x1E
#define K_TAKE_USER_CAL_SAMPLE       0x1F
#define K_FACTORY_ACCEL_COEFF        0x24
#define K_FACTORY_ACCEL_COEFF_DONE   0x25
#define K_SET_FUNCTIONAL_MODE        0x4F
#define K_GET_FUNCTIONAL_MODE        0x50
#define K_GET_FUNCTIONAL_MODE_RESP   0x51
#define K_SET_RESET_REF              0x6E
#define K_SET_MAG_TRUTH_METHOD       0x77
#define K_GET_MAG_THUTH_METHOD       0x78
#define K_GET_MAG_THRUTH_METHOD_RESP 0x79

#endif /* PNI_BINARY_H */
