#pragma once
// MESSAGE SONAR_REPORT PACKING

#define MAVLINK_MSG_ID_SONAR_REPORT 27

MAVPACKED(
typedef struct __mavlink_sonar_report_t {
 float objectDistance_cm; /*< */
 uint8_t objectDetected_flag; /*< */
}) mavlink_sonar_report_t;

#define MAVLINK_MSG_ID_SONAR_REPORT_LEN 5
#define MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN 5
#define MAVLINK_MSG_ID_27_LEN 5
#define MAVLINK_MSG_ID_27_MIN_LEN 5

#define MAVLINK_MSG_ID_SONAR_REPORT_CRC 32
#define MAVLINK_MSG_ID_27_CRC 32



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SONAR_REPORT { \
    27, \
    "SONAR_REPORT", \
    2, \
    {  { "objectDetected_flag", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_sonar_report_t, objectDetected_flag) }, \
         { "objectDistance_cm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_sonar_report_t, objectDistance_cm) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SONAR_REPORT { \
    "SONAR_REPORT", \
    2, \
    {  { "objectDetected_flag", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_sonar_report_t, objectDetected_flag) }, \
         { "objectDistance_cm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_sonar_report_t, objectDistance_cm) }, \
         } \
}
#endif

/**
 * @brief Pack a sonar_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param objectDetected_flag 
 * @param objectDistance_cm 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sonar_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t objectDetected_flag, float objectDistance_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_REPORT_LEN];
    _mav_put_float(buf, 0, objectDistance_cm);
    _mav_put_uint8_t(buf, 4, objectDetected_flag);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SONAR_REPORT_LEN);
#else
    mavlink_sonar_report_t packet;
    packet.objectDistance_cm = objectDistance_cm;
    packet.objectDetected_flag = objectDetected_flag;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SONAR_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SONAR_REPORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
}

/**
 * @brief Pack a sonar_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param objectDetected_flag 
 * @param objectDistance_cm 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sonar_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t objectDetected_flag,float objectDistance_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_REPORT_LEN];
    _mav_put_float(buf, 0, objectDistance_cm);
    _mav_put_uint8_t(buf, 4, objectDetected_flag);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SONAR_REPORT_LEN);
#else
    mavlink_sonar_report_t packet;
    packet.objectDistance_cm = objectDistance_cm;
    packet.objectDetected_flag = objectDetected_flag;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SONAR_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SONAR_REPORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
}

/**
 * @brief Encode a sonar_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sonar_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sonar_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sonar_report_t* sonar_report)
{
    return mavlink_msg_sonar_report_pack(system_id, component_id, msg, sonar_report->objectDetected_flag, sonar_report->objectDistance_cm);
}

/**
 * @brief Encode a sonar_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sonar_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sonar_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sonar_report_t* sonar_report)
{
    return mavlink_msg_sonar_report_pack_chan(system_id, component_id, chan, msg, sonar_report->objectDetected_flag, sonar_report->objectDistance_cm);
}

/**
 * @brief Send a sonar_report message
 * @param chan MAVLink channel to send the message
 *
 * @param objectDetected_flag 
 * @param objectDistance_cm 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sonar_report_send(mavlink_channel_t chan, uint8_t objectDetected_flag, float objectDistance_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SONAR_REPORT_LEN];
    _mav_put_float(buf, 0, objectDistance_cm);
    _mav_put_uint8_t(buf, 4, objectDetected_flag);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_REPORT, buf, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
#else
    mavlink_sonar_report_t packet;
    packet.objectDistance_cm = objectDistance_cm;
    packet.objectDetected_flag = objectDetected_flag;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_REPORT, (const char *)&packet, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
#endif
}

/**
 * @brief Send a sonar_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sonar_report_send_struct(mavlink_channel_t chan, const mavlink_sonar_report_t* sonar_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sonar_report_send(chan, sonar_report->objectDetected_flag, sonar_report->objectDistance_cm);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_REPORT, (const char *)sonar_report, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_SONAR_REPORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sonar_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t objectDetected_flag, float objectDistance_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, objectDistance_cm);
    _mav_put_uint8_t(buf, 4, objectDetected_flag);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_REPORT, buf, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
#else
    mavlink_sonar_report_t *packet = (mavlink_sonar_report_t *)msgbuf;
    packet->objectDistance_cm = objectDistance_cm;
    packet->objectDetected_flag = objectDetected_flag;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SONAR_REPORT, (const char *)packet, MAVLINK_MSG_ID_SONAR_REPORT_MIN_LEN, MAVLINK_MSG_ID_SONAR_REPORT_LEN, MAVLINK_MSG_ID_SONAR_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE SONAR_REPORT UNPACKING


/**
 * @brief Get field objectDetected_flag from sonar_report message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_sonar_report_get_objectDetected_flag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field objectDistance_cm from sonar_report message
 *
 * @return 
 */
static inline float mavlink_msg_sonar_report_get_objectDistance_cm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a sonar_report message into a struct
 *
 * @param msg The message to decode
 * @param sonar_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_sonar_report_decode(const mavlink_message_t* msg, mavlink_sonar_report_t* sonar_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sonar_report->objectDistance_cm = mavlink_msg_sonar_report_get_objectDistance_cm(msg);
    sonar_report->objectDetected_flag = mavlink_msg_sonar_report_get_objectDetected_flag(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SONAR_REPORT_LEN? msg->len : MAVLINK_MSG_ID_SONAR_REPORT_LEN;
        memset(sonar_report, 0, MAVLINK_MSG_ID_SONAR_REPORT_LEN);
    memcpy(sonar_report, _MAV_PAYLOAD(msg), len);
#endif
}
