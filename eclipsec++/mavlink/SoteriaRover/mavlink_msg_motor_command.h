#pragma once
// MESSAGE MOTOR_COMMAND PACKING

#define MAVLINK_MSG_ID_MOTOR_COMMAND 10

MAVPACKED(
typedef struct __mavlink_motor_command_t {
 uint32_t m1_power_per; /*< */
 uint32_t m2_power_per; /*< */
 uint8_t m1_commandid; /*< */
 uint8_t m1_newCommand; /*< */
 uint8_t m2_commandid; /*< */
 uint8_t m2_newCommand; /*< */
}) mavlink_motor_command_t;

#define MAVLINK_MSG_ID_MOTOR_COMMAND_LEN 12
#define MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN 12
#define MAVLINK_MSG_ID_10_LEN 12
#define MAVLINK_MSG_ID_10_MIN_LEN 12

#define MAVLINK_MSG_ID_MOTOR_COMMAND_CRC 47
#define MAVLINK_MSG_ID_10_CRC 47



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_COMMAND { \
    10, \
    "MOTOR_COMMAND", \
    6, \
    {  { "m1_commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_motor_command_t, m1_commandid) }, \
         { "m1_newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_motor_command_t, m1_newCommand) }, \
         { "m1_power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_command_t, m1_power_per) }, \
         { "m2_commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_motor_command_t, m2_commandid) }, \
         { "m2_newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_motor_command_t, m2_newCommand) }, \
         { "m2_power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motor_command_t, m2_power_per) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_COMMAND { \
    "MOTOR_COMMAND", \
    6, \
    {  { "m1_commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_motor_command_t, m1_commandid) }, \
         { "m1_newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_motor_command_t, m1_newCommand) }, \
         { "m1_power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_command_t, m1_power_per) }, \
         { "m2_commandid", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_motor_command_t, m2_commandid) }, \
         { "m2_newCommand", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_motor_command_t, m2_newCommand) }, \
         { "m2_power_per", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motor_command_t, m2_power_per) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param m1_commandid 
 * @param m1_newCommand 
 * @param m1_power_per 
 * @param m2_commandid 
 * @param m2_newCommand 
 * @param m2_power_per 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t m1_commandid, uint8_t m1_newCommand, uint32_t m1_power_per, uint8_t m2_commandid, uint8_t m2_newCommand, uint32_t m2_power_per)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, m1_power_per);
    _mav_put_uint32_t(buf, 4, m2_power_per);
    _mav_put_uint8_t(buf, 8, m1_commandid);
    _mav_put_uint8_t(buf, 9, m1_newCommand);
    _mav_put_uint8_t(buf, 10, m2_commandid);
    _mav_put_uint8_t(buf, 11, m2_newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#else
    mavlink_motor_command_t packet;
    packet.m1_power_per = m1_power_per;
    packet.m2_power_per = m2_power_per;
    packet.m1_commandid = m1_commandid;
    packet.m1_newCommand = m1_newCommand;
    packet.m2_commandid = m2_commandid;
    packet.m2_newCommand = m2_newCommand;

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
 * @param m1_commandid 
 * @param m1_newCommand 
 * @param m1_power_per 
 * @param m2_commandid 
 * @param m2_newCommand 
 * @param m2_power_per 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t m1_commandid,uint8_t m1_newCommand,uint32_t m1_power_per,uint8_t m2_commandid,uint8_t m2_newCommand,uint32_t m2_power_per)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, m1_power_per);
    _mav_put_uint32_t(buf, 4, m2_power_per);
    _mav_put_uint8_t(buf, 8, m1_commandid);
    _mav_put_uint8_t(buf, 9, m1_newCommand);
    _mav_put_uint8_t(buf, 10, m2_commandid);
    _mav_put_uint8_t(buf, 11, m2_newCommand);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
#else
    mavlink_motor_command_t packet;
    packet.m1_power_per = m1_power_per;
    packet.m2_power_per = m2_power_per;
    packet.m1_commandid = m1_commandid;
    packet.m1_newCommand = m1_newCommand;
    packet.m2_commandid = m2_commandid;
    packet.m2_newCommand = m2_newCommand;

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
    return mavlink_msg_motor_command_pack(system_id, component_id, msg, motor_command->m1_commandid, motor_command->m1_newCommand, motor_command->m1_power_per, motor_command->m2_commandid, motor_command->m2_newCommand, motor_command->m2_power_per);
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
    return mavlink_msg_motor_command_pack_chan(system_id, component_id, chan, msg, motor_command->m1_commandid, motor_command->m1_newCommand, motor_command->m1_power_per, motor_command->m2_commandid, motor_command->m2_newCommand, motor_command->m2_power_per);
}

/**
 * @brief Send a motor_command message
 * @param chan MAVLink channel to send the message
 *
 * @param m1_commandid 
 * @param m1_newCommand 
 * @param m1_power_per 
 * @param m2_commandid 
 * @param m2_newCommand 
 * @param m2_power_per 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_command_send(mavlink_channel_t chan, uint8_t m1_commandid, uint8_t m1_newCommand, uint32_t m1_power_per, uint8_t m2_commandid, uint8_t m2_newCommand, uint32_t m2_power_per)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, m1_power_per);
    _mav_put_uint32_t(buf, 4, m2_power_per);
    _mav_put_uint8_t(buf, 8, m1_commandid);
    _mav_put_uint8_t(buf, 9, m1_newCommand);
    _mav_put_uint8_t(buf, 10, m2_commandid);
    _mav_put_uint8_t(buf, 11, m2_newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, buf, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#else
    mavlink_motor_command_t packet;
    packet.m1_power_per = m1_power_per;
    packet.m2_power_per = m2_power_per;
    packet.m1_commandid = m1_commandid;
    packet.m1_newCommand = m1_newCommand;
    packet.m2_commandid = m2_commandid;
    packet.m2_newCommand = m2_newCommand;

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
    mavlink_msg_motor_command_send(chan, motor_command->m1_commandid, motor_command->m1_newCommand, motor_command->m1_power_per, motor_command->m2_commandid, motor_command->m2_newCommand, motor_command->m2_power_per);
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
static inline void mavlink_msg_motor_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t m1_commandid, uint8_t m1_newCommand, uint32_t m1_power_per, uint8_t m2_commandid, uint8_t m2_newCommand, uint32_t m2_power_per)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, m1_power_per);
    _mav_put_uint32_t(buf, 4, m2_power_per);
    _mav_put_uint8_t(buf, 8, m1_commandid);
    _mav_put_uint8_t(buf, 9, m1_newCommand);
    _mav_put_uint8_t(buf, 10, m2_commandid);
    _mav_put_uint8_t(buf, 11, m2_newCommand);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, buf, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#else
    mavlink_motor_command_t *packet = (mavlink_motor_command_t *)msgbuf;
    packet->m1_power_per = m1_power_per;
    packet->m2_power_per = m2_power_per;
    packet->m1_commandid = m1_commandid;
    packet->m1_newCommand = m1_newCommand;
    packet->m2_commandid = m2_commandid;
    packet->m2_newCommand = m2_newCommand;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_COMMAND, (const char *)packet, MAVLINK_MSG_ID_MOTOR_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN, MAVLINK_MSG_ID_MOTOR_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_COMMAND UNPACKING


/**
 * @brief Get field m1_commandid from motor_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_command_get_m1_commandid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field m1_newCommand from motor_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_command_get_m1_newCommand(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field m1_power_per from motor_command message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_motor_command_get_m1_power_per(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field m2_commandid from motor_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_command_get_m2_commandid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field m2_newCommand from motor_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_command_get_m2_newCommand(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field m2_power_per from motor_command message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_motor_command_get_m2_power_per(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
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
    motor_command->m1_power_per = mavlink_msg_motor_command_get_m1_power_per(msg);
    motor_command->m2_power_per = mavlink_msg_motor_command_get_m2_power_per(msg);
    motor_command->m1_commandid = mavlink_msg_motor_command_get_m1_commandid(msg);
    motor_command->m1_newCommand = mavlink_msg_motor_command_get_m1_newCommand(msg);
    motor_command->m2_commandid = mavlink_msg_motor_command_get_m2_commandid(msg);
    motor_command->m2_newCommand = mavlink_msg_motor_command_get_m2_newCommand(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_COMMAND_LEN;
        memset(motor_command, 0, MAVLINK_MSG_ID_MOTOR_COMMAND_LEN);
    memcpy(motor_command, _MAV_PAYLOAD(msg), len);
#endif
}
