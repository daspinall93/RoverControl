#pragma once
// MESSAGE INERT_REPORT PACKING

#define MAVLINK_MSG_ID_INERT_REPORT 20

MAVPACKED(
typedef struct __mavlink_inert_report_t {
 float roll_deg; /*< */
 float pitch_deg; /*< */
 float yaw_deg; /*< */
}) mavlink_inert_report_t;

#define MAVLINK_MSG_ID_INERT_REPORT_LEN 12
#define MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN 12
#define MAVLINK_MSG_ID_20_LEN 12
#define MAVLINK_MSG_ID_20_MIN_LEN 12

#define MAVLINK_MSG_ID_INERT_REPORT_CRC 88
#define MAVLINK_MSG_ID_20_CRC 88



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_INERT_REPORT { \
    20, \
    "INERT_REPORT", \
    3, \
    {  { "roll_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_inert_report_t, roll_deg) }, \
         { "pitch_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_inert_report_t, pitch_deg) }, \
         { "yaw_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_inert_report_t, yaw_deg) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_INERT_REPORT { \
    "INERT_REPORT", \
    3, \
    {  { "roll_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_inert_report_t, roll_deg) }, \
         { "pitch_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_inert_report_t, pitch_deg) }, \
         { "yaw_deg", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_inert_report_t, yaw_deg) }, \
         } \
}
#endif

/**
 * @brief Pack a inert_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_deg 
 * @param pitch_deg 
 * @param yaw_deg 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inert_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll_deg, float pitch_deg, float yaw_deg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_float(buf, 0, roll_deg);
    _mav_put_float(buf, 4, pitch_deg);
    _mav_put_float(buf, 8, yaw_deg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#else
    mavlink_inert_report_t packet;
    packet.roll_deg = roll_deg;
    packet.pitch_deg = pitch_deg;
    packet.yaw_deg = yaw_deg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INERT_REPORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
}

/**
 * @brief Pack a inert_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll_deg 
 * @param pitch_deg 
 * @param yaw_deg 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inert_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll_deg,float pitch_deg,float yaw_deg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_float(buf, 0, roll_deg);
    _mav_put_float(buf, 4, pitch_deg);
    _mav_put_float(buf, 8, yaw_deg);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#else
    mavlink_inert_report_t packet;
    packet.roll_deg = roll_deg;
    packet.pitch_deg = pitch_deg;
    packet.yaw_deg = yaw_deg;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INERT_REPORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
}

/**
 * @brief Encode a inert_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param inert_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inert_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_inert_report_t* inert_report)
{
    return mavlink_msg_inert_report_pack(system_id, component_id, msg, inert_report->roll_deg, inert_report->pitch_deg, inert_report->yaw_deg);
}

/**
 * @brief Encode a inert_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param inert_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inert_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_inert_report_t* inert_report)
{
    return mavlink_msg_inert_report_pack_chan(system_id, component_id, chan, msg, inert_report->roll_deg, inert_report->pitch_deg, inert_report->yaw_deg);
}

/**
 * @brief Send a inert_report message
 * @param chan MAVLink channel to send the message
 *
 * @param roll_deg 
 * @param pitch_deg 
 * @param yaw_deg 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inert_report_send(mavlink_channel_t chan, float roll_deg, float pitch_deg, float yaw_deg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_float(buf, 0, roll_deg);
    _mav_put_float(buf, 4, pitch_deg);
    _mav_put_float(buf, 8, yaw_deg);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, buf, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#else
    mavlink_inert_report_t packet;
    packet.roll_deg = roll_deg;
    packet.pitch_deg = pitch_deg;
    packet.yaw_deg = yaw_deg;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, (const char *)&packet, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#endif
}

/**
 * @brief Send a inert_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_inert_report_send_struct(mavlink_channel_t chan, const mavlink_inert_report_t* inert_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_inert_report_send(chan, inert_report->roll_deg, inert_report->pitch_deg, inert_report->yaw_deg);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, (const char *)inert_report, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_INERT_REPORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_inert_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll_deg, float pitch_deg, float yaw_deg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll_deg);
    _mav_put_float(buf, 4, pitch_deg);
    _mav_put_float(buf, 8, yaw_deg);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, buf, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#else
    mavlink_inert_report_t *packet = (mavlink_inert_report_t *)msgbuf;
    packet->roll_deg = roll_deg;
    packet->pitch_deg = pitch_deg;
    packet->yaw_deg = yaw_deg;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, (const char *)packet, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE INERT_REPORT UNPACKING


/**
 * @brief Get field roll_deg from inert_report message
 *
 * @return 
 */
static inline float mavlink_msg_inert_report_get_roll_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch_deg from inert_report message
 *
 * @return 
 */
static inline float mavlink_msg_inert_report_get_pitch_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw_deg from inert_report message
 *
 * @return 
 */
static inline float mavlink_msg_inert_report_get_yaw_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a inert_report message into a struct
 *
 * @param msg The message to decode
 * @param inert_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_inert_report_decode(const mavlink_message_t* msg, mavlink_inert_report_t* inert_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    inert_report->roll_deg = mavlink_msg_inert_report_get_roll_deg(msg);
    inert_report->pitch_deg = mavlink_msg_inert_report_get_pitch_deg(msg);
    inert_report->yaw_deg = mavlink_msg_inert_report_get_yaw_deg(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_INERT_REPORT_LEN? msg->len : MAVLINK_MSG_ID_INERT_REPORT_LEN;
        memset(inert_report, 0, MAVLINK_MSG_ID_INERT_REPORT_LEN);
    memcpy(inert_report, _MAV_PAYLOAD(msg), len);
#endif
}
