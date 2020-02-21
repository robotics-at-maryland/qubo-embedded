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

/** UART Settings
 *
 *  When communicating over UART, use the following settings. Note
 *  the buadrate can be changed, but the power must be cycled for
 *  changes to take effect.
 *
 *  Number of Data Bits: 8
 *  Start Bits:          1
 *  Stop Bits:           1
 *  Parity:              none
 *  Default baudrate:    38400 baud
 */


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
 * @brief Allows the AHRS to determine what command is being sent
 * and the host to determine what data is being sent
 *
 */

#define K_GET_MOD_INFO_ID               0x01
#define K_GET_MOD_INFO_RESP_ID          0x02
#define K_SET_DATA_COMPONENTS_ID        0x03
#define K_GET_DATA_ID                   0x04
#define K_GET_DATA_RESP_ID              0x05
#define K_SET_CONFIG_ID                 0x06
#define K_GET_CONFIG_ID                 0x07
#define K_GET_CONFIG_RESP_ID            0x08
#define K_SAVE_ID                       0x09
#define K_START_CAL_ID                  0x0A
#define K_STOP_CAL_ID                   0x0B
#define K_SET_FIR_FILTERS_ID            0x0C
#define K_GET_FIR_FILTERS_ID            0x0D
#define K_GET_FIR_FILTERS_RESP_ID       0x0E
#define K_POWER_DOWN_ID                 0x0F
#define K_SAVE_DONE_ID                  0x10
#define K_USER_CAL_SAMPLE_COUNT_ID      0x11
#define K_USER_CAL_SCORE_ID             0x12
#define K_SET_CONFIG_DONE_ID            0x13
#define K_SET_FIR_FILTERS_DONE_ID       0x14
#define K_START_CONTINUOUS_MODE_ID      0x15
#define K_STOP_CONTINUOUS_MODE_ID       0x16
#define K_POWER_UP_DONE_ID              0x17
#define K_SET_ACQ_PARAMS_ID             0x18
#define K_GET_ACQ_PARAMS_ID             0x19
#define K_SET_ACQ_PARAMS_DONE_ID        0x1A
#define K_GET_ACQ_PARAMS_RESP_ID        0x1B
#define K_POWER_DOWN_DONE_ID            0x1C
#define K_FACTORY_MAG_COEFF_ID          0x1D
#define K_FACTORY_MAG_COEFF_DONE_ID     0x1E
#define K_TAKE_USER_CAL_SAMPLE_ID       0x1F
#define K_FACTORY_ACCEL_COEFF_ID        0x24
#define K_FACTORY_ACCEL_COEFF_DONE_ID   0x25
#define K_SET_FUNCTIONAL_MODE_ID        0x4F
#define K_GET_FUNCTIONAL_MODE_ID        0x50
#define K_GET_FUNCTIONAL_MODE_RESP_ID   0x51
#define K_SET_RESET_REF_ID              0x6E
#define K_SET_MAG_TRUTH_METHOD_ID       0x77
#define K_GET_MAG_THUTH_METHOD_ID       0x78
#define K_GET_MAG_THRUTH_METHOD_RESP_ID 0x79

/* ------------------------------------------------------------ */
/* THE REST OF THE DEFINES ARE EACH ASSOCIATED WITH COMMAND IDS */
/* ------------------------------------------------------------ */

/** Configuration IDs
 *
 * These are used in the Config ID fields of the following Command IDs:
 *
 *   kSetConfig
 *   kGetConfig
 *   kGetConfigResp
 *
 */

#define K_DECLINATION_ID            0x01
#define K_TRUE_NORTH_ID             0x02
#define K_BIG_ENDIAN_ID             0x06
#define K_MOUNTING_REF_ID           0x0A
#define K_USER_CAL_NUM_POINTS_ID    0x0C
#define K_USER_CAL_AUTO_SAMPLING_ID 0x0D
#define K_BAUD_RATE_ID              0x0E
#define K_MIL_OUT_ID                0x0F
#define K_HPR_DURING_CAL_ID         0x10
#define K_MAG_COEFF_SET_ID          0x12
#define K_ACCEL_COEFF_SET_ID        0x13

/* kSetDataComponents Data Component IDs */

#define K_HEADING_ID        0x05
#define K_PITCH_ID          0x18
#define K_ROLL_ID           0x19
#define K_HEADING_STATUS_ID 0x4F
#define K_QUATERNION_ID     0x4D
#define K_TEMPERATURE_ID    0x07
#define K_DISTORTION_ID     0x08
#define K_CAL_STATUS_ID     0x09
#define K_ACCEL_X_ID        0x15
#define K_ACCEL_Y_ID        0x16
#define K_ACCEL_Z_ID        0x17
#define K_MAG_X_ID          0x1B
#define K_MAG_Y_ID          0x1C
#define K_MAG_Z_ID          0x1D
#define K_GYRO_X_ID         0x4A
#define K_GYRO_Y_ID         0x4B
#define K_GYRO_Z_ID         0x4C

/* kSetMagTruthMethod Methods */

#define MAG_TRUTH_METHOD_STANDARD  1
#define MAG_TRUTH_METHOD_TIGHT     2
#define MAG_TRUTH_METHOD_AUTOMERGE 3

/* kSaveDone Error Codes */

#define K_SAVE_DONE_NO_ERROR 0
#define K_SAVE_DONE_ERROR    1

/* kSetAcqParams Data Acquisition Parameter defines */

#define ACQUISITION_MODE_POLL       true
#define ACQUISITION_MODE_CONTINUOUS false

#define FLUSH_FILTER_ON             true
#define FLUSH_FILTER_OFF            false

/* kStartCal Calibration Options */

#define CALIBRATION_FULL_RANGE     0x0A
#define CALIBRATION_2D             0x14
#define CALIBRATION_HARD_IRON_ONLY 0x1E
#define CALIBRATION_LIMITED_TILD   0x28
#define CALIBRATION_ACCEL_ONLY     0x64
#define CALIBRATION_MAG_ACCEL      0x6E

/* kSetFunctionalMode Parameters */

#define COMPASS_MODE 0
#define AHRS_MODE    1

#endif /* PNI_BINARY_H */
