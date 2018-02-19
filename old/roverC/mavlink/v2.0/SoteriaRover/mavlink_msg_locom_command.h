#pragma once
// MESSAGE LOCOM_COMMAND PACKING

#define MAVLINK_MSG_ID_LOCOM_COMMAND 1

MAVPACKED(
typedef struct __mavlink_locom_command_t {
 uint32_t duration_ms; /*< duration of the locomotion command*/
 uint32_t power; /*< Power (0-100%) of the commanded locomotion manoeuvre*/
 uint8_t command_id; /*< The ID of the locomotion module command*/
}) mavlink_locom_command_t;

#define MAVLINK_MSG_ID_LOCOM_COMMAND_LEN 9
#define MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN 9
#define MAVLINK_MSG_ID_1_LEN 9
#define MAVLINK_MSG_ID_1_MIN_LEN 9

#define MAVLINK_MSG_ID_LOCOM_COMMAND_CRC 133
#define MAVLINK_MSG_ID_1_CRC 133



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOCOM_COMMAND { \
    1, \
    "LOCOM_COMMAND", \
    3, \
    {  { "command_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_locom_command_t, command_id) }, \
         { "duration_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_locom_command_t, duration_ms) }, \
         { "power", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_locom_command_t, power) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOCOM_COMMAND { \
    "LOCOM_COMMAND", \
    3, \
    {  { "command_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_locom_command_t, command_id) }, \
         { "duration_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_locom_command_t, duration_ms) }, \
         { "power", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_locom_command_t, power) }, \
         } \
}
#endif

/**
 * @brief Pack a locom_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param command_id The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power Power (0-100%) of the commanded locomotion manoeuvre
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t command_id, uint32_t duration_ms, uint32_t power)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 4, power);
    _mav_put_uint8_t(buf, 8, command_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN);
#else
    mavlink_locom_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power = power;
    packet.command_id = command_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
}

/**
 * @brief Pack a locom_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command_id The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power Power (0-100%) of the commanded locomotion manoeuvre
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t command_id,uint32_t duration_ms,uint32_t power)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 4, power);
    _mav_put_uint8_t(buf, 8, command_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN);
#else
    mavlink_locom_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power = power;
    packet.command_id = command_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
}

/**
 * @brief Encode a locom_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param locom_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_locom_command_t* locom_command)
{
    return mavlink_msg_locom_command_pack(system_id, component_id, msg, locom_command->command_id, locom_command->duration_ms, locom_command->power);
}

/**
 * @brief Encode a locom_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param locom_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_locom_command_t* locom_command)
{
    return mavlink_msg_locom_command_pack_chan(system_id, component_id, chan, msg, locom_command->command_id, locom_command->duration_ms, locom_command->power);
}

/**
 * @brief Send a locom_command message
 * @param chan MAVLink channel to send the message
 *
 * @param command_id The ID of the locomotion module command
 * @param duration_ms duration of the locomotion command
 * @param power Power (0-100%) of the commanded locomotion manoeuvre
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_locom_command_send(mavlink_channel_t chan, uint8_t command_id, uint32_t duration_ms, uint32_t power)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 4, power);
    _mav_put_uint8_t(buf, 8, command_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_COMMAND, buf, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
#else
    mavlink_locom_command_t packet;
    packet.duration_ms = duration_ms;
    packet.power = power;
    packet.command_id = command_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
#endif
}

/**
 * @brief Send a locom_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_locom_command_send_struct(mavlink_channel_t chan, const mavlink_locom_command_t* locom_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_locom_command_send(chan, locom_command->command_id, locom_command->duration_ms, locom_command->power);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_COMMAND, (const char *)locom_command, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOCOM_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_locom_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t command_id, uint32_t duration_ms, uint32_t power)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, duration_ms);
    _mav_put_uint32_t(buf, 4, power);
    _mav_put_uint8_t(buf, 8, command_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_COMMAND, buf, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
#else
    mavlink_locom_command_t *packet = (mavlink_locom_command_t *)msgbuf;
    packet->duration_ms = duration_ms;
    packet->power = power;
    packet->command_id = command_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_COMMAND, (const char *)packet, MAVLINK_MSG_ID_LOCOM_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN, MAVLINK_MSG_ID_LOCOM_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE LOCOM_COMMAND UNPACKING


/**
 * @brief Get field command_id from locom_command message
 *
 * @return The ID of the locomotion module command
 */
static inline uint8_t mavlink_msg_locom_command_get_command_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field duration_ms from locom_command message
 *
 * @return duration of the locomotion command
 */
static inline uint32_t mavlink_msg_locom_command_get_duration_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field power from locom_command message
 *
 * @return Power (0-100%) of the commanded locomotion manoeuvre
 */
static inline uint32_t mavlink_msg_locom_command_get_power(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Decode a locom_command message into a struct
 *
 * @param msg The message to decode
 * @param locom_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_locom_command_decode(const mavlink_message_t* msg, mavlink_locom_command_t* locom_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    locom_command->duration_ms = mavlink_msg_locom_command_get_duration_ms(msg);
    locom_command->power = mavlink_msg_locom_command_get_power(msg);
    locom_command->command_id = mavlink_msg_locom_command_get_command_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LOCOM_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_LOCOM_COMMAND_LEN;
        memset(locom_command, 0, MAVLINK_MSG_ID_LOCOM_COMMAND_LEN);
    memcpy(locom_command, _MAV_PAYLOAD(msg), len);
#endif
}
