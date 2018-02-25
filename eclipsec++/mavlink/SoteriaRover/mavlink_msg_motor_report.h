#pragma once
// MESSAGE MOTOR_REPORT PACKING

#define MAVLINK_MSG_ID_MOTOR_REPORT 11

MAVPACKED(
typedef struct __mavlink_motor_report_t {
 uint32_t m1_pwmInput; /*< */
 uint32_t m2_pwmInput; /*< */
 uint8_t m1_mode; /*< */
 uint8_t m2_mode; /*< */
}) mavlink_motor_report_t;

#define MAVLINK_MSG_ID_MOTOR_REPORT_LEN 10
#define MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN 10
#define MAVLINK_MSG_ID_11_LEN 10
#define MAVLINK_MSG_ID_11_MIN_LEN 10

#define MAVLINK_MSG_ID_MOTOR_REPORT_CRC 43
#define MAVLINK_MSG_ID_11_CRC 43



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_REPORT { \
    11, \
    "MOTOR_REPORT", \
    4, \
    {  { "m1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_motor_report_t, m1_mode) }, \
         { "m1_pwmInput", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_report_t, m1_pwmInput) }, \
         { "m2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_motor_report_t, m2_mode) }, \
         { "m2_pwmInput", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motor_report_t, m2_pwmInput) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_REPORT { \
    "MOTOR_REPORT", \
    4, \
    {  { "m1_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_motor_report_t, m1_mode) }, \
         { "m1_pwmInput", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_report_t, m1_pwmInput) }, \
         { "m2_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_motor_report_t, m2_mode) }, \
         { "m2_pwmInput", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motor_report_t, m2_pwmInput) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param m1_mode 
 * @param m1_pwmInput 
 * @param m2_mode 
 * @param m2_pwmInput 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t m1_mode, uint32_t m1_pwmInput, uint8_t m2_mode, uint32_t m2_pwmInput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_REPORT_LEN];
    _mav_put_uint32_t(buf, 0, m1_pwmInput);
    _mav_put_uint32_t(buf, 4, m2_pwmInput);
    _mav_put_uint8_t(buf, 8, m1_mode);
    _mav_put_uint8_t(buf, 9, m2_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_REPORT_LEN);
#else
    mavlink_motor_report_t packet;
    packet.m1_pwmInput = m1_pwmInput;
    packet.m2_pwmInput = m2_pwmInput;
    packet.m1_mode = m1_mode;
    packet.m2_mode = m2_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_REPORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
}

/**
 * @brief Pack a motor_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param m1_mode 
 * @param m1_pwmInput 
 * @param m2_mode 
 * @param m2_pwmInput 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t m1_mode,uint32_t m1_pwmInput,uint8_t m2_mode,uint32_t m2_pwmInput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_REPORT_LEN];
    _mav_put_uint32_t(buf, 0, m1_pwmInput);
    _mav_put_uint32_t(buf, 4, m2_pwmInput);
    _mav_put_uint8_t(buf, 8, m1_mode);
    _mav_put_uint8_t(buf, 9, m2_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_REPORT_LEN);
#else
    mavlink_motor_report_t packet;
    packet.m1_pwmInput = m1_pwmInput;
    packet.m2_pwmInput = m2_pwmInput;
    packet.m1_mode = m1_mode;
    packet.m2_mode = m2_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_REPORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
}

/**
 * @brief Encode a motor_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_report_t* motor_report)
{
    return mavlink_msg_motor_report_pack(system_id, component_id, msg, motor_report->m1_mode, motor_report->m1_pwmInput, motor_report->m2_mode, motor_report->m2_pwmInput);
}

/**
 * @brief Encode a motor_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_report_t* motor_report)
{
    return mavlink_msg_motor_report_pack_chan(system_id, component_id, chan, msg, motor_report->m1_mode, motor_report->m1_pwmInput, motor_report->m2_mode, motor_report->m2_pwmInput);
}

/**
 * @brief Send a motor_report message
 * @param chan MAVLink channel to send the message
 *
 * @param m1_mode 
 * @param m1_pwmInput 
 * @param m2_mode 
 * @param m2_pwmInput 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_report_send(mavlink_channel_t chan, uint8_t m1_mode, uint32_t m1_pwmInput, uint8_t m2_mode, uint32_t m2_pwmInput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_REPORT_LEN];
    _mav_put_uint32_t(buf, 0, m1_pwmInput);
    _mav_put_uint32_t(buf, 4, m2_pwmInput);
    _mav_put_uint8_t(buf, 8, m1_mode);
    _mav_put_uint8_t(buf, 9, m2_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_REPORT, buf, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
#else
    mavlink_motor_report_t packet;
    packet.m1_pwmInput = m1_pwmInput;
    packet.m2_pwmInput = m2_pwmInput;
    packet.m1_mode = m1_mode;
    packet.m2_mode = m2_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_REPORT, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
#endif
}

/**
 * @brief Send a motor_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_report_send_struct(mavlink_channel_t chan, const mavlink_motor_report_t* motor_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_report_send(chan, motor_report->m1_mode, motor_report->m1_pwmInput, motor_report->m2_mode, motor_report->m2_pwmInput);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_REPORT, (const char *)motor_report, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_REPORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t m1_mode, uint32_t m1_pwmInput, uint8_t m2_mode, uint32_t m2_pwmInput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, m1_pwmInput);
    _mav_put_uint32_t(buf, 4, m2_pwmInput);
    _mav_put_uint8_t(buf, 8, m1_mode);
    _mav_put_uint8_t(buf, 9, m2_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_REPORT, buf, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
#else
    mavlink_motor_report_t *packet = (mavlink_motor_report_t *)msgbuf;
    packet->m1_pwmInput = m1_pwmInput;
    packet->m2_pwmInput = m2_pwmInput;
    packet->m1_mode = m1_mode;
    packet->m2_mode = m2_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_REPORT, (const char *)packet, MAVLINK_MSG_ID_MOTOR_REPORT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_LEN, MAVLINK_MSG_ID_MOTOR_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_REPORT UNPACKING


/**
 * @brief Get field m1_mode from motor_report message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_report_get_m1_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field m1_pwmInput from motor_report message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_motor_report_get_m1_pwmInput(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field m2_mode from motor_report message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_motor_report_get_m2_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field m2_pwmInput from motor_report message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_motor_report_get_m2_pwmInput(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Decode a motor_report message into a struct
 *
 * @param msg The message to decode
 * @param motor_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_report_decode(const mavlink_message_t* msg, mavlink_motor_report_t* motor_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_report->m1_pwmInput = mavlink_msg_motor_report_get_m1_pwmInput(msg);
    motor_report->m2_pwmInput = mavlink_msg_motor_report_get_m2_pwmInput(msg);
    motor_report->m1_mode = mavlink_msg_motor_report_get_m1_mode(msg);
    motor_report->m2_mode = mavlink_msg_motor_report_get_m2_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_REPORT_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_REPORT_LEN;
        memset(motor_report, 0, MAVLINK_MSG_ID_MOTOR_REPORT_LEN);
    memcpy(motor_report, _MAV_PAYLOAD(msg), len);
#endif
}
