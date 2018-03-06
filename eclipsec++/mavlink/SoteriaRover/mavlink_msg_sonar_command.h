#pragma once
// MESSAGE SONAR_COMMAND PACKING

#define MAVLINK_MSG_ID_SONAR_COMMAND 26

MAVPACKED(
typedef struct __mavlink_sonar_command_t {
 uint8_t newCommand; /*< */
}) mavlink_sonar_command_t;

#define MAVLINK_MSG_ID_SONAR_COMMAND_LEN 1
#define MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN 1
#define MAVLINK_MSG_ID_26_LEN 1
#define MAVLINK_MSG_ID_26_MIN_LEN 1

#define MAVLINK_MSG_ID_SONAR_COMMAND_CRC 97
#define MAVLINK_MSG_ID_26_CRC 97



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SONAR_COMMAND { \
    26, \
    "SONAR_COMMAND", \
    1, \
    {  { "newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_sonar_command_t, newCommand) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SONAR_COMMAND { \
    "SONAR_COMMAND", \
    1, \
    {  { "newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_sonar_command_t, newCommand) }, \
         } \
}
#endif

/**
 * @brief Pack a sonar_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param newCommand 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sonar_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SONAR_COMMAND_LEN);
#else
    mavlink_sonar_command_t packet;
    packet.newCommand = newCommand;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SONAR_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SONAR_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
}

/**
 * @brief Pack a sonar_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param newCommand 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sonar_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SONAR_COMMAND_LEN);
#else
    mavlink_sonar_command_t packet;
    packet.newCommand = newCommand;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SONAR_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SONAR_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
}

/**
 * @brief Encode a sonar_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sonar_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sonar_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sonar_command_t* sonar_command)
{
    return mavlink_msg_sonar_command_pack(system_id, component_id, msg, sonar_command->newCommand);
}

/**
 * @brief Encode a sonar_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sonar_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sonar_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sonar_command_t* sonar_command)
{
    return mavlink_msg_sonar_command_pack_chan(system_id, component_id, chan, msg, sonar_command->newCommand);
}

/**
 * @brief Send a sonar_command message
 * @param chan MAVLink channel to send the message
 *
 * @param newCommand 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sonar_command_send(mavlink_channel_t chan, uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_COMMAND, buf, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
#else
    mavlink_sonar_command_t packet;
    packet.newCommand = newCommand;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
#endif
}

/**
 * @brief Send a sonar_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sonar_command_send_struct(mavlink_channel_t chan, const mavlink_sonar_command_t* sonar_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sonar_command_send(chan, sonar_command->newCommand);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_COMMAND, (const char *)sonar_command, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_SONAR_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sonar_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t newCommand)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_COMMAND, buf, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
#else
    mavlink_sonar_command_t *packet = (mavlink_sonar_command_t *)msgbuf;
    packet->newCommand = newCommand;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_COMMAND, (const char *)packet, MAVLINK_MSG_ID_SONAR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_LEN, MAVLINK_MSG_ID_SONAR_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE SONAR_COMMAND UNPACKING


/**
 * @brief Get field newCommand from sonar_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_sonar_command_get_newCommand(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a sonar_command message into a struct
 *
 * @param msg The message to decode
 * @param sonar_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_sonar_command_decode(const mavlink_message_t* msg, mavlink_sonar_command_t* sonar_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sonar_command->newCommand = mavlink_msg_sonar_command_get_newCommand(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SONAR_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_SONAR_COMMAND_LEN;
        memset(sonar_command, 0, MAVLINK_MSG_ID_SONAR_COMMAND_LEN);
    memcpy(sonar_command, _MAV_PAYLOAD(msg), len);
#endif
}
