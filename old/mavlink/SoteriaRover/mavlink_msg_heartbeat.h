#pragma once
// MESSAGE HEARTBEAT PACKING

#define MAVLINK_MSG_ID_HEARTBEAT 0

MAVPACKED(
typedef struct __mavlink_heartbeat_t {
 uint8_t locom_mode; /*< Mode of the locomotion module*/
 uint8_t motor1_mode; /*< Mode of motor 1*/
 uint8_t motor2_mode; /*< Mode of motor 2*/
 uint8_t mavlink_version; /*< MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_heartbeat_t;

#define MAVLINK_MSG_ID_HEARTBEAT_LEN 4
#define MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN 4
#define MAVLINK_MSG_ID_0_LEN 4
#define MAVLINK_MSG_ID_0_MIN_LEN 4

#define MAVLINK_MSG_ID_HEARTBEAT_CRC 176
#define MAVLINK_MSG_ID_0_CRC 176



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    0, \
    "HEARTBEAT", \
    4, \
    {  { "locom_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_heartbeat_t, locom_mode) }, \
         { "motor1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_heartbeat_t, motor1_mode) }, \
         { "motor2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_heartbeat_t, motor2_mode) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_heartbeat_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    "HEARTBEAT", \
    4, \
    {  { "locom_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_heartbeat_t, locom_mode) }, \
         { "motor1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_heartbeat_t, motor1_mode) }, \
         { "motor2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_heartbeat_t, motor2_mode) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_heartbeat_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);
    _mav_put_uint8_t(buf, 3, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEARTBEAT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
}

/**
 * @brief Pack a heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t locom_mode,uint8_t motor1_mode,uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);
    _mav_put_uint8_t(buf, 3, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;
    packet.mavlink_version = 3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEARTBEAT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
}

/**
 * @brief Encode a heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack(system_id, component_id, msg, heartbeat->locom_mode, heartbeat->motor1_mode, heartbeat->motor2_mode);
}

/**
 * @brief Encode a heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack_chan(system_id, component_id, chan, msg, heartbeat->locom_mode, heartbeat->motor1_mode, heartbeat->motor2_mode);
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param locom_mode Mode of the locomotion module
 * @param motor1_mode Mode of motor 1
 * @param motor2_mode Mode of motor 2
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);
    _mav_put_uint8_t(buf, 3, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t packet;
    packet.locom_mode = locom_mode;
    packet.motor1_mode = motor1_mode;
    packet.motor2_mode = motor2_mode;
    packet.mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)&packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_heartbeat_send(chan, heartbeat->locom_mode, heartbeat->motor1_mode, heartbeat->motor2_mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)heartbeat, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}

#if MAVLINK_MSG_ID_HEARTBEAT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t locom_mode, uint8_t motor1_mode, uint8_t motor2_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, locom_mode);
    _mav_put_uint8_t(buf, 1, motor1_mode);
    _mav_put_uint8_t(buf, 2, motor2_mode);
    _mav_put_uint8_t(buf, 3, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t *packet = (mavlink_heartbeat_t *)msgbuf;
    packet->locom_mode = locom_mode;
    packet->motor1_mode = motor1_mode;
    packet->motor2_mode = motor2_mode;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}
#endif

#endif

// MESSAGE HEARTBEAT UNPACKING


/**
 * @brief Get field locom_mode from heartbeat message
 *
 * @return Mode of the locomotion module
 */
static inline uint8_t mavlink_msg_heartbeat_get_locom_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field motor1_mode from heartbeat message
 *
 * @return Mode of motor 1
 */
static inline uint8_t mavlink_msg_heartbeat_get_motor1_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field motor2_mode from heartbeat message
 *
 * @return Mode of motor 2
 */
static inline uint8_t mavlink_msg_heartbeat_get_motor2_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field mavlink_version from heartbeat message
 *
 * @return MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_heartbeat_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Decode a heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_heartbeat_decode(const mavlink_message_t* msg, mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    heartbeat->locom_mode = mavlink_msg_heartbeat_get_locom_mode(msg);
    heartbeat->motor1_mode = mavlink_msg_heartbeat_get_motor1_mode(msg);
    heartbeat->motor2_mode = mavlink_msg_heartbeat_get_motor2_mode(msg);
    heartbeat->mavlink_version = mavlink_msg_heartbeat_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HEARTBEAT_LEN? msg->len : MAVLINK_MSG_ID_HEARTBEAT_LEN;
        memset(heartbeat, 0, MAVLINK_MSG_ID_HEARTBEAT_LEN);
    memcpy(heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
