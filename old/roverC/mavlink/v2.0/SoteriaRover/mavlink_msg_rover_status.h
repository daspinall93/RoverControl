#pragma once
// MESSAGE ROVER_STATUS PACKING

#define MAVLINK_MSG_ID_ROVER_STATUS 2

MAVPACKED(
typedef struct __mavlink_rover_status_t {
 uint8_t locom_mode; /*< Mode of the locomotion module*/
 uint8_t motor1_mode; /*< Mode of motor 1*/
 uint8_t motor2_mode; /*< Mode of motor 2*/
}) mavlink_rover_status_t;

#define MAVLINK_MSG_ID_ROVER_STATUS_LEN 3
#define MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN 3
#define MAVLINK_MSG_ID_2_LEN 3
#define MAVLINK_MSG_ID_2_MIN_LEN 3

#define MAVLINK_MSG_ID_ROVER_STATUS_CRC 162
#define MAVLINK_MSG_ID_2_CRC 162



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ROVER_STATUS { \
    2, \
    "ROVER_STATUS", \
    3, \
    {  { "locom_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_rover_status_t, locom_mode) }, \
         { "motor1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_rover_status_t, motor1_mode) }, \
         { "motor2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_rover_status_t, motor2_mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ROVER_STATUS { \
    "ROVER_STATUS", \
    3, \
    {  { "locom_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_rover_status_t, locom_mode) }, \
         { "motor1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_rover_status_t, motor1_mode) }, \
         { "motor2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_rover_status_t, motor2_mode) }, \
         } \
}
#endif

/**
 * @brief Pack a rover_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rover_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ROVER_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ROVER_STATUS_LEN);
#else
    mavlink_rover_status_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ROVER_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ROVER_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
}

/**
 * @brief Pack a rover_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rover_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t locom_mode,uint8_t motor1_mode,uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ROVER_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ROVER_STATUS_LEN);
#else
    mavlink_rover_status_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ROVER_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ROVER_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
}

/**
 * @brief Encode a rover_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rover_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rover_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rover_status_t* rover_status)
{
    return mavlink_msg_rover_status_pack(system_id, component_id, msg, rover_status->locom_mode, rover_status->motor1_mode, rover_status->motor2_mode);
}

/**
 * @brief Encode a rover_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rover_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rover_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rover_status_t* rover_status)
{
    return mavlink_msg_rover_status_pack_chan(system_id, component_id, chan, msg, rover_status->locom_mode, rover_status->motor1_mode, rover_status->motor2_mode);
}

/**
 * @brief Send a rover_status message
 * @param chan MAVLink channel to send the message
 *
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rover_status_send(mavlink_channel_t chan, uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ROVER_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROVER_STATUS, buf, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
#else
    mavlink_rover_status_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROVER_STATUS, (const char *)&packet, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
#endif
}

/**
 * @brief Send a rover_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rover_status_send_struct(mavlink_channel_t chan, const mavlink_rover_status_t* rover_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rover_status_send(chan, rover_status->locom_mode, rover_status->motor1_mode, rover_status->motor2_mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROVER_STATUS, (const char *)rover_status, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_ROVER_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rover_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROVER_STATUS, buf, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
#else
    mavlink_rover_status_t *packet = (mavlink_rover_status_t *)msgbuf;
    packet->locom_mode = locom_mode;
    packet->motor1_mode = motor1_mode;
    packet->motor2_mode = motor2_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ROVER_STATUS, (const char *)packet, MAVLINK_MSG_ID_ROVER_STATUS_MIN_LEN, MAVLINK_MSG_ID_ROVER_STATUS_LEN, MAVLINK_MSG_ID_ROVER_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE ROVER_STATUS UNPACKING


/**
 * @brief Get field locom_mode from rover_status message
 *
 * @return Mode of the locomotion module
 */
static inline uint8_t mavlink_msg_rover_status_get_locom_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field motor1_mode from rover_status message
 *
 * @return Mode of motor 1
 */
static inline uint8_t mavlink_msg_rover_status_get_motor1_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field motor2_mode from rover_status message
 *
 * @return Mode of motor 2
 */
static inline uint8_t mavlink_msg_rover_status_get_motor2_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a rover_status message into a struct
 *
 * @param msg The message to decode
 * @param rover_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_rover_status_decode(const mavlink_message_t* msg, mavlink_rover_status_t* rover_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rover_status->locom_mode = mavlink_msg_rover_status_get_locom_mode(msg);
    rover_status->motor1_mode = mavlink_msg_rover_status_get_motor1_mode(msg);
    rover_status->motor2_mode = mavlink_msg_rover_status_get_motor2_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ROVER_STATUS_LEN? msg->len : MAVLINK_MSG_ID_ROVER_STATUS_LEN;
        memset(rover_status, 0, MAVLINK_MSG_ID_ROVER_STATUS_LEN);
    memcpy(rover_status, _MAV_PAYLOAD(msg), len);
#endif
}
