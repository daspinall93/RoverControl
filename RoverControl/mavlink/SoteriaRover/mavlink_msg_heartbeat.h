#pragma once
// MESSAGE HEARTBEAT PACKING

#define MAVLINK_MSG_ID_HEARTBEAT 0

MAVPACKED(
typedef struct __mavlink_heartbeat_t {
 float pitch_deg; /*< */
 float roll_deg; /*< */
 float yaw_deg; /*< */
 float objDist_cm; /*< */
 uint8_t motor_mode; /*< Mode of the locomotion module*/
 uint8_t modeDur_ms; /*< */
 uint8_t tiltFlag; /*< */
 uint8_t objDetFlag; /*< */
 uint8_t mavlink_version; /*< MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_heartbeat_t;

#define MAVLINK_MSG_ID_HEARTBEAT_LEN 21
#define MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN 21
#define MAVLINK_MSG_ID_0_LEN 21
#define MAVLINK_MSG_ID_0_MIN_LEN 21

#define MAVLINK_MSG_ID_HEARTBEAT_CRC 44
#define MAVLINK_MSG_ID_0_CRC 44



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    0, \
    "HEARTBEAT", \
    9, \
    {  { "motor_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_heartbeat_t, motor_mode) }, \
         { "modeDur_ms", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_heartbeat_t, modeDur_ms) }, \
         { "pitch_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_heartbeat_t, pitch_deg) }, \
         { "roll_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_heartbeat_t, roll_deg) }, \
         { "yaw_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_heartbeat_t, yaw_deg) }, \
         { "tiltFlag", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_heartbeat_t, tiltFlag) }, \
         { "objDetFlag", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_heartbeat_t, objDetFlag) }, \
         { "objDist_cm", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_heartbeat_t, objDist_cm) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_heartbeat_t, mavlink_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    "HEARTBEAT", \
    9, \
    {  { "motor_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_heartbeat_t, motor_mode) }, \
         { "modeDur_ms", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_heartbeat_t, modeDur_ms) }, \
         { "pitch_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_heartbeat_t, pitch_deg) }, \
         { "roll_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_heartbeat_t, roll_deg) }, \
         { "yaw_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_heartbeat_t, yaw_deg) }, \
         { "tiltFlag", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_heartbeat_t, tiltFlag) }, \
         { "objDetFlag", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_heartbeat_t, objDetFlag) }, \
         { "objDist_cm", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_heartbeat_t, objDist_cm) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_heartbeat_t, mavlink_version) }, \
         } \
}
#endif

/**
 * @brief Pack a heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor_mode Mode of the locomotion module
 * @param modeDur_ms 
 * @param pitch_deg 
 * @param roll_deg 
 * @param yaw_deg 
 * @param tiltFlag 
 * @param objDetFlag 
 * @param objDist_cm 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t motor_mode, uint8_t modeDur_ms, float pitch_deg, float roll_deg, float yaw_deg, uint8_t tiltFlag, uint8_t objDetFlag, float objDist_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_float(buf, 0, pitch_deg);
    _mav_put_float(buf, 4, roll_deg);
    _mav_put_float(buf, 8, yaw_deg);
    _mav_put_float(buf, 12, objDist_cm);
    _mav_put_uint8_t(buf, 16, motor_mode);
    _mav_put_uint8_t(buf, 17, modeDur_ms);
    _mav_put_uint8_t(buf, 18, tiltFlag);
    _mav_put_uint8_t(buf, 19, objDetFlag);
    _mav_put_uint8_t(buf, 20, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.pitch_deg = pitch_deg;
    packet.roll_deg = roll_deg;
    packet.yaw_deg = yaw_deg;
    packet.objDist_cm = objDist_cm;
    packet.motor_mode = motor_mode;
    packet.modeDur_ms = modeDur_ms;
    packet.tiltFlag = tiltFlag;
    packet.objDetFlag = objDetFlag;
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
 * @param motor_mode Mode of the locomotion module
 * @param modeDur_ms 
 * @param pitch_deg 
 * @param roll_deg 
 * @param yaw_deg 
 * @param tiltFlag 
 * @param objDetFlag 
 * @param objDist_cm 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t motor_mode,uint8_t modeDur_ms,float pitch_deg,float roll_deg,float yaw_deg,uint8_t tiltFlag,uint8_t objDetFlag,float objDist_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_float(buf, 0, pitch_deg);
    _mav_put_float(buf, 4, roll_deg);
    _mav_put_float(buf, 8, yaw_deg);
    _mav_put_float(buf, 12, objDist_cm);
    _mav_put_uint8_t(buf, 16, motor_mode);
    _mav_put_uint8_t(buf, 17, modeDur_ms);
    _mav_put_uint8_t(buf, 18, tiltFlag);
    _mav_put_uint8_t(buf, 19, objDetFlag);
    _mav_put_uint8_t(buf, 20, 3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.pitch_deg = pitch_deg;
    packet.roll_deg = roll_deg;
    packet.yaw_deg = yaw_deg;
    packet.objDist_cm = objDist_cm;
    packet.motor_mode = motor_mode;
    packet.modeDur_ms = modeDur_ms;
    packet.tiltFlag = tiltFlag;
    packet.objDetFlag = objDetFlag;
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
    return mavlink_msg_heartbeat_pack(system_id, component_id, msg, heartbeat->motor_mode, heartbeat->modeDur_ms, heartbeat->pitch_deg, heartbeat->roll_deg, heartbeat->yaw_deg, heartbeat->tiltFlag, heartbeat->objDetFlag, heartbeat->objDist_cm);
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
    return mavlink_msg_heartbeat_pack_chan(system_id, component_id, chan, msg, heartbeat->motor_mode, heartbeat->modeDur_ms, heartbeat->pitch_deg, heartbeat->roll_deg, heartbeat->yaw_deg, heartbeat->tiltFlag, heartbeat->objDetFlag, heartbeat->objDist_cm);
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param motor_mode Mode of the locomotion module
 * @param modeDur_ms 
 * @param pitch_deg 
 * @param roll_deg 
 * @param yaw_deg 
 * @param tiltFlag 
 * @param objDetFlag 
 * @param objDist_cm 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint8_t motor_mode, uint8_t modeDur_ms, float pitch_deg, float roll_deg, float yaw_deg, uint8_t tiltFlag, uint8_t objDetFlag, float objDist_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_float(buf, 0, pitch_deg);
    _mav_put_float(buf, 4, roll_deg);
    _mav_put_float(buf, 8, yaw_deg);
    _mav_put_float(buf, 12, objDist_cm);
    _mav_put_uint8_t(buf, 16, motor_mode);
    _mav_put_uint8_t(buf, 17, modeDur_ms);
    _mav_put_uint8_t(buf, 18, tiltFlag);
    _mav_put_uint8_t(buf, 19, objDetFlag);
    _mav_put_uint8_t(buf, 20, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t packet;
    packet.pitch_deg = pitch_deg;
    packet.roll_deg = roll_deg;
    packet.yaw_deg = yaw_deg;
    packet.objDist_cm = objDist_cm;
    packet.motor_mode = motor_mode;
    packet.modeDur_ms = modeDur_ms;
    packet.tiltFlag = tiltFlag;
    packet.objDetFlag = objDetFlag;
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
    mavlink_msg_heartbeat_send(chan, heartbeat->motor_mode, heartbeat->modeDur_ms, heartbeat->pitch_deg, heartbeat->roll_deg, heartbeat->yaw_deg, heartbeat->tiltFlag, heartbeat->objDetFlag, heartbeat->objDist_cm);
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
static inline void mavlink_msg_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t motor_mode, uint8_t modeDur_ms, float pitch_deg, float roll_deg, float yaw_deg, uint8_t tiltFlag, uint8_t objDetFlag, float objDist_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, pitch_deg);
    _mav_put_float(buf, 4, roll_deg);
    _mav_put_float(buf, 8, yaw_deg);
    _mav_put_float(buf, 12, objDist_cm);
    _mav_put_uint8_t(buf, 16, motor_mode);
    _mav_put_uint8_t(buf, 17, modeDur_ms);
    _mav_put_uint8_t(buf, 18, tiltFlag);
    _mav_put_uint8_t(buf, 19, objDetFlag);
    _mav_put_uint8_t(buf, 20, 3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t *packet = (mavlink_heartbeat_t *)msgbuf;
    packet->pitch_deg = pitch_deg;
    packet->roll_deg = roll_deg;
    packet->yaw_deg = yaw_deg;
    packet->objDist_cm = objDist_cm;
    packet->motor_mode = motor_mode;
    packet->modeDur_ms = modeDur_ms;
    packet->tiltFlag = tiltFlag;
    packet->objDetFlag = objDetFlag;
    packet->mavlink_version = 3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}
#endif

#endif

// MESSAGE HEARTBEAT UNPACKING


/**
 * @brief Get field motor_mode from heartbeat message
 *
 * @return Mode of the locomotion module
 */
static inline uint8_t mavlink_msg_heartbeat_get_motor_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field modeDur_ms from heartbeat message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_heartbeat_get_modeDur_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field pitch_deg from heartbeat message
 *
 * @return 
 */
static inline float mavlink_msg_heartbeat_get_pitch_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field roll_deg from heartbeat message
 *
 * @return 
 */
static inline float mavlink_msg_heartbeat_get_roll_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw_deg from heartbeat message
 *
 * @return 
 */
static inline float mavlink_msg_heartbeat_get_yaw_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field tiltFlag from heartbeat message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_heartbeat_get_tiltFlag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field objDetFlag from heartbeat message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_heartbeat_get_objDetFlag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  19);
}

/**
 * @brief Get field objDist_cm from heartbeat message
 *
 * @return 
 */
static inline float mavlink_msg_heartbeat_get_objDist_cm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field mavlink_version from heartbeat message
 *
 * @return MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version
 */
static inline uint8_t mavlink_msg_heartbeat_get_mavlink_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
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
    heartbeat->pitch_deg = mavlink_msg_heartbeat_get_pitch_deg(msg);
    heartbeat->roll_deg = mavlink_msg_heartbeat_get_roll_deg(msg);
    heartbeat->yaw_deg = mavlink_msg_heartbeat_get_yaw_deg(msg);
    heartbeat->objDist_cm = mavlink_msg_heartbeat_get_objDist_cm(msg);
    heartbeat->motor_mode = mavlink_msg_heartbeat_get_motor_mode(msg);
    heartbeat->modeDur_ms = mavlink_msg_heartbeat_get_modeDur_ms(msg);
    heartbeat->tiltFlag = mavlink_msg_heartbeat_get_tiltFlag(msg);
    heartbeat->objDetFlag = mavlink_msg_heartbeat_get_objDetFlag(msg);
    heartbeat->mavlink_version = mavlink_msg_heartbeat_get_mavlink_version(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HEARTBEAT_LEN? msg->len : MAVLINK_MSG_ID_HEARTBEAT_LEN;
        memset(heartbeat, 0, MAVLINK_MSG_ID_HEARTBEAT_LEN);
    memcpy(heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
