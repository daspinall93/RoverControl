/** @file
 *  @brief MAVLink comm protocol generated from SoteriaRover.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_SOTERIAROVER_H
#define MAVLINK_SOTERIAROVER_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_SOTERIAROVER.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 76, 24, 0, 0, 0}, {3, 119, 14, 0, 0, 0}, {11, 87, 19, 0, 0, 0}, {20, 173, 13, 0, 0, 0}, {21, 103, 1, 0, 0, 0}, {26, 97, 1, 0, 0, 0}, {27, 32, 5, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SOTERIAROVER

// ENUM DEFINITIONS


/** @brief Commands for the locomotion module */
#ifndef HAVE_ENUM_MOTOR_COMAMND_ID
#define HAVE_ENUM_MOTOR_COMAMND_ID
typedef enum MOTOR_COMAMND_ID
{
   MOTOR_COMMAND_STOP=0, /* Command the locom module to stop the rover | */
   MOTOR_COMMAND_STRAIGHT_FORWARD=1, /* Command the rover to drive straight forward | */
   MOTOR_COMMAND_STRAIGHT_BACKWARD=2, /* Command the rover to drive straight backward | */
   MOTOR_COMMAND_TURN_RIGHT=3, /* Command the rover to turn right | */
   MOTOR_COMMAND_TURN_LEFT=4, /* Command the rover to turn left | */
   MOTOR_COMAMND_ID_ENUM_END=5, /*  | */
} MOTOR_COMAMND_ID;
#endif

/** @brief Commands for the locomotion module */
#ifndef HAVE_ENUM_MOTOR_MODE
#define HAVE_ENUM_MOTOR_MODE
typedef enum MOTOR_MODE
{
   MOTOR_MODE_STOP=0, /* Command the locom module to stop the rover | */
   MOTOR_MODE_STRAIGHT_FORWARD=1, /* Command the rover to drive straight forward | */
   MOTOR_MODE_STRAIGHT_BACKWARD=2, /* Command the rover to drive straight backward | */
   MOTOR_MODE_TURN_RIGHT=3, /* Command the rover to turn right | */
   MOTOR_MODE_TURN_LEFT=4, /* Command the rover to turn left | */
   MOTOR_MODE_ENUM_END=5, /*  | */
} MOTOR_MODE;
#endif

/** @brief Mode of each motor (i.e m1 and m2) */
#ifndef HAVE_ENUM_MOTOR_SUB_MODE
#define HAVE_ENUM_MOTOR_SUB_MODE
typedef enum MOTOR_SUB_MODE
{
   MOTOR_SUBMODE_STOP=0, /* The motor is in stopped mode | */
   MOTOR_SUBMODE_FORWARD=1, /* The motor is in forward mode | */
   MOTOR_SUBMODE_BACKWARD=2, /* The motor is in backward mode | */
   MOTOR_SUB_MODE_ENUM_END=3, /*  | */
} MOTOR_SUB_MODE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.h"
#include "./mavlink_msg_motor_command.h"
#include "./mavlink_msg_motor_report.h"
#include "./mavlink_msg_inert_report.h"
#include "./mavlink_msg_inert_command.h"
#include "./mavlink_msg_sonar_command.h"
#include "./mavlink_msg_sonar_report.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_MOTOR_COMMAND, MAVLINK_MESSAGE_INFO_MOTOR_REPORT, MAVLINK_MESSAGE_INFO_INERT_REPORT, MAVLINK_MESSAGE_INFO_INERT_COMMAND, MAVLINK_MESSAGE_INFO_SONAR_COMMAND, MAVLINK_MESSAGE_INFO_SONAR_REPORT}
# define MAVLINK_MESSAGE_NAMES {{ "HEARTBEAT", 0 }, { "INERT_COMMAND", 21 }, { "INERT_REPORT", 20 }, { "MOTOR_COMMAND", 3 }, { "MOTOR_REPORT", 11 }, { "SONAR_COMMAND", 26 }, { "SONAR_REPORT", 27 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_SOTERIAROVER_H
