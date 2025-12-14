/**
 * @file fingerprint_defs.h
 * @brief GT-NUCL1633K1 Fingerprint Module Definitions
 *
 * Extracted from GT-NUCL1633K1 Programming Guide V1.3
 * ADH Technology Co. Ltd.
 */

#ifndef FINGERPRINT_DEFS_H
#define FINGERPRINT_DEFS_H

#include <stdint.h>

/* ============================================================================
 * Packet Structure Constants
 * ============================================================================ */

#define FP_PACKET_START_CODE        0xF5
#define FP_PACKET_END_CODE          0xF5
#define FP_PACKET_SIZE              8

/* Command Packet Offsets */
#define FP_CMD_OFFSET_START         0
#define FP_CMD_OFFSET_COMMAND       1
#define FP_CMD_OFFSET_P1            2
#define FP_CMD_OFFSET_P2            3
#define FP_CMD_OFFSET_P3            4
#define FP_CMD_OFFSET_P4            5
#define FP_CMD_OFFSET_CHECKSUM      6
#define FP_CMD_OFFSET_END           7

/* Response Packet Offsets */
#define FP_ACK_OFFSET_START         0
#define FP_ACK_OFFSET_COMMAND       1
#define FP_ACK_OFFSET_Q1            2
#define FP_ACK_OFFSET_Q2            3
#define FP_ACK_OFFSET_Q3            4
#define FP_ACK_OFFSET_RESERVED      5
#define FP_ACK_OFFSET_CHECKSUM      6
#define FP_ACK_OFFSET_END           7

/* ============================================================================
 * Command Codes
 * ============================================================================ */

#define FP_CMD_OPEN                 0xA0    /* Initialization */
#define FP_CMD_CLOSE                0xA1    /* Termination */
#define FP_CMD_UART_CONTROL         0xA3    /* UART baud rate setting */
#define FP_CMD_LED_CONTROL          0xB4    /* LED On/Off */
#define FP_CMD_IS_PRESS_FINGER      0xB5    /* Check if finger is placed on sensor */
#define FP_CMD_ENROLL               0x01    /* Enrollment function */
#define FP_CMD_DELETE_ID            0x04    /* Delete fingerprint with specified ID */
#define FP_CMD_DELETE_ALL           0x05    /* Delete all fingerprints from database */
#define FP_CMD_GET_USER_COUNT       0x09    /* Get enrolled fingerprint count */
#define FP_CMD_IDENTIFY             0x0C    /* 1:N Identification */
#define FP_CMD_GET_ENTRY_ID         0x0D    /* Get an unused ID */
#define FP_CMD_GET_FW_VERSION       0x26    /* Get firmware version */
#define FP_CMD_ENROLL_CANCEL        0x92    /* Break the enrollment sequences */

/* ============================================================================
 * ACK (Acknowledge) Codes
 * ============================================================================ */

#define FP_ACK_SUCCESS              0x00    /* Command execute success */
#define FP_ACK_FAIL                 0x01    /* Command execute fail */
#define FP_ACK_FULL                 0x04    /* The database is full */
#define FP_ACK_NOUSER               0x05    /* The specified ID is unregistered */
#define FP_ACK_USER_EXIST           0x07    /* The specified ID is registered */
#define FP_ACK_TIMEOUT              0x08    /* Timeout during capturing finger */
#define FP_ACK_WRONG_FORMAT         0x09    /* Template wrong format */
#define FP_ACK_BREAK                0x18    /* Abort current command */
#define FP_ACK_INVALID_PARAMETER    0xB0    /* Input invalid parameter */
#define FP_ACK_FINGER_IS_NOT_PRESSED 0xB1   /* Finger is not pressed */
#define FP_ACK_COMMAND_NO_SUPPORT   0xB4    /* Command not support */
#define FP_ACK_ENROLL_OVEREXPOSURE  0xB5    /* Finger image is overexposure */
#define FP_ACK_ENROLL_MOVE_MORE     0xB6    /* Finger moved too less */
#define FP_ACK_ENROLL_MOVE_LESS     0xB7    /* Finger moved too much */
#define FP_ACK_ENROLL_DUPLICATE     0xB8    /* Finger position is duplicated */
#define FP_ACK_FINGER_PRESS_NOT_FULL 0xB9   /* Finger press is not full */
#define FP_ACK_ENROLL_POOR_QUALITY  0xBA    /* Finger image quality is poor */

/* ============================================================================
 * UART Baud Rate Indexes
 * ============================================================================ */

#define FP_BAUDRATE_9600            1
#define FP_BAUDRATE_19200           2
#define FP_BAUDRATE_115200          3
#define FP_BAUDRATE_230400          4
#define FP_BAUDRATE_460800          5
#define FP_BAUDRATE_921600          6

/* ============================================================================
 * LED Control Values
 * ============================================================================ */

#define FP_LED_ON                   0
#define FP_LED_OFF                  1

/* ============================================================================
 * Finger Press Status
 * ============================================================================ */

#define FP_FINGER_NOT_PRESSED       0
#define FP_FINGER_PRESSED           1

/* ============================================================================
 * Enroll Result Codes
 * ============================================================================ */

#define FP_ENROLL_CONTINUE          0x01    /* Continue enrollment */
#define FP_ENROLL_FINAL             0x03    /* Final enroll (complete) */

/* ============================================================================
 * Open Command Flags
 * ============================================================================ */

#define FP_OPEN_FLAG_NO_DATA        0       /* No data packet returned */
#define FP_OPEN_FLAG_READ_FW_INFO   1       /* Read FW date and module */

/* ============================================================================
 * Open Command Data Structure Offsets (11 bytes)
 * ============================================================================ */

#define FP_OPEN_DATA_DEVICE_ID      0       /* Device ID: 0x01 */
#define FP_OPEN_DATA_RESERVED1      1       /* Reserved: default 0x00 */
#define FP_OPEN_DATA_FW_DAY         2       /* FW release date: Day */
#define FP_OPEN_DATA_FW_MONTH       3       /* FW release date: Month */
#define FP_OPEN_DATA_FW_YEAR_LOW    4       /* FW release date: Year (Low byte) */
#define FP_OPEN_DATA_FW_YEAR_HIGH   5       /* FW release date: Year (High byte) */
#define FP_OPEN_DATA_RESERVED2      6       /* Reserved: default 0x00 */
#define FP_OPEN_DATA_SENSOR_TYPE    10      /* Sensor type */
#define FP_OPEN_DATA_SIZE           11

/* ============================================================================
 * Firmware Version Data Structure Offsets (40 bytes)
 * ============================================================================ */

#define FP_FW_DATA_SENSOR_TYPE      0       /* Sensor type */
#define FP_FW_DATA_YEAR             12      /* Year */
#define FP_FW_DATA_MONTH            13      /* Month */
#define FP_FW_DATA_DAY              14      /* Day */
#define FP_FW_DATA_VERSION          15      /* Version */
#define FP_FW_DATA_SIZE             40

/* ============================================================================
 * Device Constants
 * ============================================================================ */

#define FP_DEVICE_ID                0x01
#define FP_ENROLL_SAMPLE_COUNT      8       /* Number of samples needed for enrollment */
#define FP_ENROLL_TIMEOUT_SECONDS   8       /* Timeout for each sampling */

/* ============================================================================
 * User ID Range
 * ============================================================================ */

#define FP_USER_ID_MIN              1       /* Minimum user ID value */

/* ============================================================================
 * Lookup Functions
 * ============================================================================ */

/**
 * @brief Convert command code to string name
 * @param cmd Command code
 * @return Command name string
 */
static inline const char* fp_cmd_to_string(uint8_t cmd) {
    switch (cmd) {
        case FP_CMD_OPEN:           return "Open";
        case FP_CMD_CLOSE:          return "Close";
        case FP_CMD_UART_CONTROL:   return "UART Control";
        case FP_CMD_LED_CONTROL:    return "LED Control";
        case FP_CMD_IS_PRESS_FINGER: return "IsPressFinger";
        case FP_CMD_ENROLL:         return "Enroll";
        case FP_CMD_DELETE_ID:      return "DeleteID";
        case FP_CMD_DELETE_ALL:     return "DeleteAll";
        case FP_CMD_GET_USER_COUNT: return "GetUserCount";
        case FP_CMD_IDENTIFY:       return "Identify";
        case FP_CMD_GET_ENTRY_ID:   return "GetEntryID";
        case FP_CMD_GET_FW_VERSION: return "GetFWVersion";
        case FP_CMD_ENROLL_CANCEL:  return "EnrollCancel";
        default:                    return "Unknown";
    }
}

/**
 * @brief Convert ACK code to string name
 * @param ack ACK code
 * @return ACK name string
 */
static inline const char* fp_ack_to_string(uint8_t ack) {
    switch (ack) {
        case FP_ACK_SUCCESS:              return "Success";
        case FP_ACK_FAIL:                 return "Fail";
        case FP_ACK_FULL:                 return "Full";
        case FP_ACK_NOUSER:               return "NoUser";
        case FP_ACK_USER_EXIST:           return "UserExist";
        case FP_ACK_TIMEOUT:              return "Timeout";
        case FP_ACK_WRONG_FORMAT:         return "WrongFormat";
        case FP_ACK_BREAK:                return "Break";
        case FP_ACK_INVALID_PARAMETER:    return "InvalidParameter";
        case FP_ACK_FINGER_IS_NOT_PRESSED: return "FingerNotPressed";
        case FP_ACK_COMMAND_NO_SUPPORT:   return "CommandNoSupport";
        case FP_ACK_ENROLL_OVEREXPOSURE:  return "EnrollOverexposure";
        case FP_ACK_ENROLL_MOVE_MORE:     return "EnrollMoveMore";
        case FP_ACK_ENROLL_MOVE_LESS:     return "EnrollMoveLess";
        case FP_ACK_ENROLL_DUPLICATE:     return "EnrollDuplicate";
        case FP_ACK_FINGER_PRESS_NOT_FULL: return "FingerPressNotFull";
        case FP_ACK_ENROLL_POOR_QUALITY:  return "EnrollPoorQuality";
        default:                          return "Unknown";
    }
}

#endif /* FINGERPRINT_DEFS_H */
