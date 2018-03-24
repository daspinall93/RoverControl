#pragma once
// MESSAGE MOTOR_COMMAND PACKING

#define MAVLINK_MSG_ID_MOTOR_COMMAND 3

MAVPACKED(
typedef struct __mavlink_motor_command_t {
 uint64_t duration_ms; /*< duration of the locomotion command*/
 uint32_t power_per; /*< Power (0-100%) of the commanded locomotion manoeuvre*/
 uint8_t commandid; /*< The ID of the locomotion module command*/
 uint8_t newCommand; /*< new command boolean*/
}) mavlink_motor_command_t;

#define MAVLINK_MSG_ID_MOTOR_COMMAND_LEN 14
#define MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN 14
#define MAVLINK_MSG_ID_3_LEN 14
#define MAVLINK_MSG_ID_3_MIN_LEN 14

#define MAVLINK_MSG_ID_MOTOR_COMMAND_CRC 119
#define MAVLINK_MSG_ID_3_CRC 119



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_COMMAND { \
    3, \
    "MOTOR_COMMAND", \
    4, \
    {  { "commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_motor_command_t, commandid) }, \
         { "duration_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_motor_command_t, duration_ms) }, \
         { "power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_motor_command_t, power_per) }, \
         { "newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_motor_command_t, newCommand) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_COMMAND { \
    "MOTOR_COMMAND", \
    4, \
    {  { "commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_motor_command_t, commandid) }, \
         { "duration_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_motor_command_t, duration_ms) }, \
         { "power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_motor_command_t, power_per) }, \
         { "newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_motor_command_t, newCommand) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param commandid The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power_per Power (0-100%) of the commanded locomotion manoeuvre
 * @param newCommand new command boolean
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t commandid, uint64_t duration_ms, uint32_t power_per, uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint64_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 8, power_per);
    _mav_put_uint8_t(buf, 12, commandid);
    _mav_put_uint8_t(buf, 13, newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#else
    mavlink_motor_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power_per = power_per;
    packet.commandid = commandid;
    packet.newCommand = newCommand;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
}

/**
 * @brief Pack a motor_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param commandid The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power_per Power (0-100%) of the commanded locomotion manoeuvre
 * @param newCommand new command boolean
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t commandid,uint64_t duration_ms,uint32_t power_per,uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint64_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 8, power_per);
    _mav_put_uint8_t(buf, 12, commandid);
    _mav_put_uint8_t(buf, 13, newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#else
    mavlink_motor_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power_per = power_per;
    packet.commandid = commandid;
    packet.newCommand = newCommand;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
}

/**
 * @brief Encode a motor_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_command_t* motor_command)
{
    return mavlink_msg_motor_command_pack(system_id, component_id, msg, motor_command->commandid, motor_command->duration_ms, motor_command->power_per, motor_command->newCommand);
}

/**
 * @brief Encode a motor_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_command_t* motor_command)
{
    return mavlink_msg_motor_command_pack_chan(system_id, component_id, chan, msg, motor_command->commandid, motor_command->duration_ms, motor_command->power_per, motor_command->newCommand);
}

/**
 * @brief Send a motor_command message
 * @param chan MAVLink channel to send the message
 *
 * @param commandid The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power_per Power (0-100%) of the commanded locomotion manoeuvre
 * @param newCommand new command boolean
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_command_send(mavlink_channel_t chan, uint8_t commandid, uint64_t duration_ms, uint32_t power_per, uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint64_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 8, power_per);
    _mav_put_uint8_t(buf, 12, commandid);
    _mav_put_uint8_t(buf, 13, newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, buf, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#else
    mavlink_motor_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power_per = power_per;
    packet.commandid = commandid;
    packet.newCommand = newCommand;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#endif
}

/**
 * @brief Send a motor_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_command_send_struct(mavlink_channel_t chan, const mavlink_motor_command_t* motor_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_command_send(chan, motor_command->commandid, motor_command->duration_ms, motor_command->power_per, motor_command->newCommand);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, (const char *)motor_command, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t commandid, uint64_t duration_ms, uint32_t power_per, uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 8, power_per);
    _mav_put_uint8_t(buf, 12, commandid);
    _mav_put_uint8_t(buf, 13, newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, buf, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#else
    mavlink_motor_command_t *packet = (mavlink_motor_command_t *)msgbuf;
    packet->duration_ms = duration_ms;
    packet->power_per = power_per;
    packet->commandid = commandid;
    packet->newCommand = newCommand;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, (const char *)packet, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_COMMAND UNPACKING


/**
 * @brief Get field commandid from motor_command message
 *
 * @return The ID of the locomotion module command
 */
static inline uint8_t mavlink_msg_motor_command_get_commandid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field duration_ms from motor_command message
 *
 * @return duration of the locomotion command
 */
static inline uint64_t mavlink_msg_motor_command_get_duration_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field power_per from motor_command message
 *
 * @return Power (0-100%) of the commanded locomotion manoeuvre
 */
static inline uint32_t mavlink_msg_motor_command_get_power_per(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field newCommand from motor_command message
 *
 * @return new command boolean
 */
static inline uint8_t mavlink_msg_motor_command_get_newCommand(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Decode a motor_command message into a struct
 *
 * @param msg The message to decode
 * @param motor_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_command_decode(const mavlink_message_t* msg, mavlink_motor_command_t* motor_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_command->duration_ms = mavlink_msg_motor_command_get_duration_ms(msg);
    motor_command->power_per = mavlink_msg_motor_command_get_power_per(msg);
    motor_command->commandid = mavlink_msg_motor_command_get_commandid(msg);
    motor_command->newCommand = mavlink_msg_motor_command_get_newCommand(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_COMMAND_LEN;
        memset(motor_command, 0, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
    memcpy(motor_command, _MAV_PAYLOAD(msg), len);
#endif
}
