/** @file
 *	@brief MAVLink comm protocol generated from SoteriaRover.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#ifndef MAVLINK_STX
#define MAVLINK_STX 253
#endif

#include "../message.hpp"

namespace mavlink {
namespace SoteriaRover {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (trought @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 8> MESSAGE_ENTRIES {{ {0, 176, 4, 0, 0, 0}, {3, 119, 14, 0, 0, 0}, {11, 87, 19, 0, 0, 0}, {20, 173, 13, 0, 0, 0}, {21, 103, 1, 0, 0, 0}, {26, 97, 1, 0, 0, 0}, {27, 32, 5, 0, 0, 0}, {28, 216, 1, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 3;


// ENUM DEFINITIONS


/** @brief Commands for the locomotion module */
enum class MOTOR_COMAMND_ID
{
    COMMAND_STOP=0, /* Command the locom module to stop the rover | */
    COMMAND_STRAIGHT_FORWARD=1, /* Command the rover to drive straight forward | */
    COMMAND_STRAIGHT_BACKWARD=2, /* Command the rover to drive straight backward | */
    COMMAND_TURN_RIGHT=3, /* Command the rover to turn right | */
    COMMAND_TURN_LEFT=4, /* Command the rover to turn left | */
};

//! MOTOR_COMAMND_ID ENUM_END
constexpr auto MOTOR_COMAMND_ID_ENUM_END = 5;

/** @brief Commands for the locomotion module */
enum class MOTOR_MODE : uint8_t
{
    STOP=0, /* Command the locom module to stop the rover | */
    STRAIGHT_FORWARD=1, /* Command the rover to drive straight forward | */
    STRAIGHT_BACKWARD=2, /* Command the rover to drive straight backward | */
    TURN_RIGHT=3, /* Command the rover to turn right | */
    TURN_LEFT=4, /* Command the rover to turn left | */
};

//! MOTOR_MODE ENUM_END
constexpr auto MOTOR_MODE_ENUM_END = 5;

/** @brief Mode of each motor (i.e m1 and m2) */
enum class MOTOR_SUB_MODE : uint8_t
{
    SUBMODE_STOP=0, /* The motor is in stopped mode | */
    SUBMODE_FORWARD=1, /* The motor is in forward mode | */
    SUBMODE_BACKWARD=2, /* The motor is in backward mode | */
};

//! MOTOR_SUB_MODE ENUM_END
constexpr auto MOTOR_SUB_MODE_ENUM_END = 3;


} // namespace SoteriaRover
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.hpp"
#include "./mavlink_msg_motor_command.hpp"
#include "./mavlink_msg_motor_report.hpp"
#include "./mavlink_msg_inert_report.hpp"
#include "./mavlink_msg_inert_command.hpp"
#include "./mavlink_msg_sonar_command.hpp"
#include "./mavlink_msg_sonar_report.hpp"
#include "./mavlink_msg_camera_command.hpp"

// base include

