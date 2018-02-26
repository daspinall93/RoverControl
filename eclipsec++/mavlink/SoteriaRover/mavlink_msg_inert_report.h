#pragma once
// MESSAGE INERT_REPORT PACKING

#define MAVLINK_MSG_ID_INERT_REPORT 20

MAVPACKED(
typedef struct __mavlink_inert_report_t {
 int32_t accX_dig; /*< */
 int32_t accY_dig; /*< */
 int32_t accZ_dig; /*< */
 int32_t gyroX_dig; /*< */
 int32_t gyroY_dig; /*< */
 int32_t gyroZ_dig; /*< */
}) mavlink_inert_report_t;

#define MAVLINK_MSG_ID_INERT_REPORT_LEN 24
#define MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN 24
#define MAVLINK_MSG_ID_20_LEN 24
#define MAVLINK_MSG_ID_20_MIN_LEN 24

#define MAVLINK_MSG_ID_INERT_REPORT_CRC 241
#define MAVLINK_MSG_ID_20_CRC 241



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_INERT_REPORT { \
    20, \
    "INERT_REPORT", \
    6, \
    {  { "accX_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_inert_report_t, accX_dig) }, \
         { "accY_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_inert_report_t, accY_dig) }, \
         { "accZ_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_inert_report_t, accZ_dig) }, \
         { "gyroX_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_inert_report_t, gyroX_dig) }, \
         { "gyroY_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_inert_report_t, gyroY_dig) }, \
         { "gyroZ_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_inert_report_t, gyroZ_dig) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_INERT_REPORT { \
    "INERT_REPORT", \
    6, \
    {  { "accX_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_inert_report_t, accX_dig) }, \
         { "accY_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_inert_report_t, accY_dig) }, \
         { "accZ_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_inert_report_t, accZ_dig) }, \
         { "gyroX_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_inert_report_t, gyroX_dig) }, \
         { "gyroY_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_inert_report_t, gyroY_dig) }, \
         { "gyroZ_dig", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_inert_report_t, gyroZ_dig) }, \
         } \
}
#endif

/**
 * @brief Pack a inert_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param accX_dig 
 * @param accY_dig 
 * @param accZ_dig 
 * @param gyroX_dig 
 * @param gyroY_dig 
 * @param gyroZ_dig 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inert_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int32_t accX_dig, int32_t accY_dig, int32_t accZ_dig, int32_t gyroX_dig, int32_t gyroY_dig, int32_t gyroZ_dig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_int32_t(buf, 0, accX_dig);
    _mav_put_int32_t(buf, 4, accY_dig);
    _mav_put_int32_t(buf, 8, accZ_dig);
    _mav_put_int32_t(buf, 12, gyroX_dig);
    _mav_put_int32_t(buf, 16, gyroY_dig);
    _mav_put_int32_t(buf, 20, gyroZ_dig);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#else
    mavlink_inert_report_t packet;
    packet.accX_dig = accX_dig;
    packet.accY_dig = accY_dig;
    packet.accZ_dig = accZ_dig;
    packet.gyroX_dig = gyroX_dig;
    packet.gyroY_dig = gyroY_dig;
    packet.gyroZ_dig = gyroZ_dig;

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
 * @param accX_dig 
 * @param accY_dig 
 * @param accZ_dig 
 * @param gyroX_dig 
 * @param gyroY_dig 
 * @param gyroZ_dig 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inert_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int32_t accX_dig,int32_t accY_dig,int32_t accZ_dig,int32_t gyroX_dig,int32_t gyroY_dig,int32_t gyroZ_dig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_int32_t(buf, 0, accX_dig);
    _mav_put_int32_t(buf, 4, accY_dig);
    _mav_put_int32_t(buf, 8, accZ_dig);
    _mav_put_int32_t(buf, 12, gyroX_dig);
    _mav_put_int32_t(buf, 16, gyroY_dig);
    _mav_put_int32_t(buf, 20, gyroZ_dig);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INERT_REPORT_LEN);
#else
    mavlink_inert_report_t packet;
    packet.accX_dig = accX_dig;
    packet.accY_dig = accY_dig;
    packet.accZ_dig = accZ_dig;
    packet.gyroX_dig = gyroX_dig;
    packet.gyroY_dig = gyroY_dig;
    packet.gyroZ_dig = gyroZ_dig;

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
    return mavlink_msg_inert_report_pack(system_id, component_id, msg, inert_report->accX_dig, inert_report->accY_dig, inert_report->accZ_dig, inert_report->gyroX_dig, inert_report->gyroY_dig, inert_report->gyroZ_dig);
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
    return mavlink_msg_inert_report_pack_chan(system_id, component_id, chan, msg, inert_report->accX_dig, inert_report->accY_dig, inert_report->accZ_dig, inert_report->gyroX_dig, inert_report->gyroY_dig, inert_report->gyroZ_dig);
}

/**
 * @brief Send a inert_report message
 * @param chan MAVLink channel to send the message
 *
 * @param accX_dig 
 * @param accY_dig 
 * @param accZ_dig 
 * @param gyroX_dig 
 * @param gyroY_dig 
 * @param gyroZ_dig 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inert_report_send(mavlink_channel_t chan, int32_t accX_dig, int32_t accY_dig, int32_t accZ_dig, int32_t gyroX_dig, int32_t gyroY_dig, int32_t gyroZ_dig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INERT_REPORT_LEN];
    _mav_put_int32_t(buf, 0, accX_dig);
    _mav_put_int32_t(buf, 4, accY_dig);
    _mav_put_int32_t(buf, 8, accZ_dig);
    _mav_put_int32_t(buf, 12, gyroX_dig);
    _mav_put_int32_t(buf, 16, gyroY_dig);
    _mav_put_int32_t(buf, 20, gyroZ_dig);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, buf, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#else
    mavlink_inert_report_t packet;
    packet.accX_dig = accX_dig;
    packet.accY_dig = accY_dig;
    packet.accZ_dig = accZ_dig;
    packet.gyroX_dig = gyroX_dig;
    packet.gyroY_dig = gyroY_dig;
    packet.gyroZ_dig = gyroZ_dig;

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
    mavlink_msg_inert_report_send(chan, inert_report->accX_dig, inert_report->accY_dig, inert_report->accZ_dig, inert_report->gyroX_dig, inert_report->gyroY_dig, inert_report->gyroZ_dig);
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
static inline void mavlink_msg_inert_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t accX_dig, int32_t accY_dig, int32_t accZ_dig, int32_t gyroX_dig, int32_t gyroY_dig, int32_t gyroZ_dig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, accX_dig);
    _mav_put_int32_t(buf, 4, accY_dig);
    _mav_put_int32_t(buf, 8, accZ_dig);
    _mav_put_int32_t(buf, 12, gyroX_dig);
    _mav_put_int32_t(buf, 16, gyroY_dig);
    _mav_put_int32_t(buf, 20, gyroZ_dig);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, buf, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#else
    mavlink_inert_report_t *packet = (mavlink_inert_report_t *)msgbuf;
    packet->accX_dig = accX_dig;
    packet->accY_dig = accY_dig;
    packet->accZ_dig = accZ_dig;
    packet->gyroX_dig = gyroX_dig;
    packet->gyroY_dig = gyroY_dig;
    packet->gyroZ_dig = gyroZ_dig;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INERT_REPORT, (const char *)packet, MAVLINK_MSG_ID_INERT_REPORT_MIN_LEN, MAVLINK_MSG_ID_INERT_REPORT_LEN, MAVLINK_MSG_ID_INERT_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE INERT_REPORT UNPACKING


/**
 * @brief Get field accX_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_accX_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field accY_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_accY_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field accZ_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_accZ_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field gyroX_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_gyroX_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field gyroY_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_gyroY_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field gyroZ_dig from inert_report message
 *
 * @return 
 */
static inline int32_t mavlink_msg_inert_report_get_gyroZ_dig(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
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
    inert_report->accX_dig = mavlink_msg_inert_report_get_accX_dig(msg);
    inert_report->accY_dig = mavlink_msg_inert_report_get_accY_dig(msg);
    inert_report->accZ_dig = mavlink_msg_inert_report_get_accZ_dig(msg);
    inert_report->gyroX_dig = mavlink_msg_inert_report_get_gyroX_dig(msg);
    inert_report->gyroY_dig = mavlink_msg_inert_report_get_gyroY_dig(msg);
    inert_report->gyroZ_dig = mavlink_msg_inert_report_get_gyroZ_dig(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_INERT_REPORT_LEN? msg->len : MAVLINK_MSG_ID_INERT_REPORT_LEN;
        memset(inert_report, 0, MAVLINK_MSG_ID_INERT_REPORT_LEN);
    memcpy(inert_report, _MAV_PAYLOAD(msg), len);
#endif
}
