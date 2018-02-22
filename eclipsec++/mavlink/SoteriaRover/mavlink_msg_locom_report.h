#pragma once
// MESSAGE LOCOM_REPORT PACKING

#define MAVLINK_MSG_ID_LOCOM_REPORT 4

MAVPACKED(
typedef struct __mavlink_locom_report_t {
 uint64_t mode_elapsed_time_ms; /*< The ID of the locomotion module command*/
 uint8_t mode; /*< duration of the locomotion command*/
}) mavlink_locom_report_t;

#define MAVLINK_MSG_ID_LOCOM_REPORT_LEN 9
#define MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN 9
#define MAVLINK_MSG_ID_4_LEN 9
#define MAVLINK_MSG_ID_4_MIN_LEN 9

#define MAVLINK_MSG_ID_LOCOM_REPORT_CRC 213
#define MAVLINK_MSG_ID_4_CRC 213



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOCOM_REPORT { \
    4, \
    "LOCOM_REPORT", \
    2, \
    {  { "mode_elapsed_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_locom_report_t, mode_elapsed_time_ms) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_locom_report_t, mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOCOM_REPORT { \
    "LOCOM_REPORT", \
    2, \
    {  { "mode_elapsed_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_locom_report_t, mode_elapsed_time_ms) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_locom_report_t, mode) }, \
         } \
}
#endif

/**
 * @brief Pack a locom_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_REPORT_LEN];
    _mav_put_uint64_t(buf, 0, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 8, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_REPORT_LEN);
#else
    mavlink_locom_report_t packet;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_REPORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
}

/**
 * @brief Pack a locom_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t mode_elapsed_time_ms,uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_REPORT_LEN];
    _mav_put_uint64_t(buf, 0, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 8, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_REPORT_LEN);
#else
    mavlink_locom_report_t packet;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_REPORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_REPORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
}

/**
 * @brief Encode a locom_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param locom_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_locom_report_t* locom_report)
{
    return mavlink_msg_locom_report_pack(system_id, component_id, msg, locom_report->mode_elapsed_time_ms, locom_report->mode);
}

/**
 * @brief Encode a locom_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param locom_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_locom_report_t* locom_report)
{
    return mavlink_msg_locom_report_pack_chan(system_id, component_id, chan, msg, locom_report->mode_elapsed_time_ms, locom_report->mode);
}

/**
 * @brief Send a locom_report message
 * @param chan MAVLink channel to send the message
 *
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_locom_report_send(mavlink_channel_t chan, uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_REPORT_LEN];
    _mav_put_uint64_t(buf, 0, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 8, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_REPORT, buf, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
#else
    mavlink_locom_report_t packet;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_REPORT, (const char *)&packet, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
#endif
}

/**
 * @brief Send a locom_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_locom_report_send_struct(mavlink_channel_t chan, const mavlink_locom_report_t* locom_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_locom_report_send(chan, locom_report->mode_elapsed_time_ms, locom_report->mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_REPORT, (const char *)locom_report, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOCOM_REPORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_locom_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 8, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_REPORT, buf, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
#else
    mavlink_locom_report_t *packet = (mavlink_locom_report_t *)msgbuf;
    packet->mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet->mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_REPORT, (const char *)packet, MAVLINK_MSG_ID_LOCOM_REPORT_MIN_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_LEN, MAVLINK_MSG_ID_LOCOM_REPORT_CRC);
#endif
}
#endif

#endif

// MESSAGE LOCOM_REPORT UNPACKING


/**
 * @brief Get field mode_elapsed_time_ms from locom_report message
 *
 * @return The ID of the locomotion module command
 */
static inline uint64_t mavlink_msg_locom_report_get_mode_elapsed_time_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field mode from locom_report message
 *
 * @return duration of the locomotion command
 */
static inline uint8_t mavlink_msg_locom_report_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a locom_report message into a struct
 *
 * @param msg The message to decode
 * @param locom_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_locom_report_decode(const mavlink_message_t* msg, mavlink_locom_report_t* locom_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    locom_report->mode_elapsed_time_ms = mavlink_msg_locom_report_get_mode_elapsed_time_ms(msg);
    locom_report->mode = mavlink_msg_locom_report_get_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LOCOM_REPORT_LEN? msg->len : MAVLINK_MSG_ID_LOCOM_REPORT_LEN;
        memset(locom_report, 0, MAVLINK_MSG_ID_LOCOM_REPORT_LEN);
    memcpy(locom_report, _MAV_PAYLOAD(msg), len);
#endif
}
