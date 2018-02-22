#pragma once
// MESSAGE LOCOM_STATE PACKING

#define MAVLINK_MSG_ID_LOCOM_STATE 5

MAVPACKED(
typedef struct __mavlink_locom_state_t {
 uint64_t mode_start_time_ms; /*< The ID of the locomotion module command*/
 uint64_t mode_elapsed_time_ms; /*< The ID of the locomotion module command*/
 uint8_t mode; /*< duration of the locomotion command*/
}) mavlink_locom_state_t;

#define MAVLINK_MSG_ID_LOCOM_STATE_LEN 17
#define MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN 17
#define MAVLINK_MSG_ID_5_LEN 17
#define MAVLINK_MSG_ID_5_MIN_LEN 17

#define MAVLINK_MSG_ID_LOCOM_STATE_CRC 42
#define MAVLINK_MSG_ID_5_CRC 42



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOCOM_STATE { \
    5, \
    "LOCOM_STATE", \
    3, \
    {  { "mode_start_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_locom_state_t, mode_start_time_ms) }, \
         { "mode_elapsed_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_locom_state_t, mode_elapsed_time_ms) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_locom_state_t, mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOCOM_STATE { \
    "LOCOM_STATE", \
    3, \
    {  { "mode_start_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_locom_state_t, mode_start_time_ms) }, \
         { "mode_elapsed_time_ms", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_locom_state_t, mode_elapsed_time_ms) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_locom_state_t, mode) }, \
         } \
}
#endif

/**
 * @brief Pack a locom_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode_start_time_ms The ID of the locomotion module command
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t mode_start_time_ms, uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_STATE_LEN];
    _mav_put_uint64_t(buf, 0, mode_start_time_ms);
    _mav_put_uint64_t(buf, 8, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 16, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_STATE_LEN);
#else
    mavlink_locom_state_t packet;
    packet.mode_start_time_ms = mode_start_time_ms;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
}

/**
 * @brief Pack a locom_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode_start_time_ms The ID of the locomotion module command
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_locom_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t mode_start_time_ms,uint64_t mode_elapsed_time_ms,uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_STATE_LEN];
    _mav_put_uint64_t(buf, 0, mode_start_time_ms);
    _mav_put_uint64_t(buf, 8, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 16, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOCOM_STATE_LEN);
#else
    mavlink_locom_state_t packet;
    packet.mode_start_time_ms = mode_start_time_ms;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOCOM_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOCOM_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
}

/**
 * @brief Encode a locom_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param locom_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_locom_state_t* locom_state)
{
    return mavlink_msg_locom_state_pack(system_id, component_id, msg, locom_state->mode_start_time_ms, locom_state->mode_elapsed_time_ms, locom_state->mode);
}

/**
 * @brief Encode a locom_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param locom_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_locom_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_locom_state_t* locom_state)
{
    return mavlink_msg_locom_state_pack_chan(system_id, component_id, chan, msg, locom_state->mode_start_time_ms, locom_state->mode_elapsed_time_ms, locom_state->mode);
}

/**
 * @brief Send a locom_state message
 * @param chan MAVLink channel to send the message
 *
 * @param mode_start_time_ms The ID of the locomotion module command
 * @param mode_elapsed_time_ms The ID of the locomotion module command
 * @param mode duration of the locomotion command
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_locom_state_send(mavlink_channel_t chan, uint64_t mode_start_time_ms, uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOCOM_STATE_LEN];
    _mav_put_uint64_t(buf, 0, mode_start_time_ms);
    _mav_put_uint64_t(buf, 8, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 16, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_STATE, buf, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
#else
    mavlink_locom_state_t packet;
    packet.mode_start_time_ms = mode_start_time_ms;
    packet.mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet.mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_STATE, (const char *)&packet, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
#endif
}

/**
 * @brief Send a locom_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_locom_state_send_struct(mavlink_channel_t chan, const mavlink_locom_state_t* locom_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_locom_state_send(chan, locom_state->mode_start_time_ms, locom_state->mode_elapsed_time_ms, locom_state->mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_STATE, (const char *)locom_state, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOCOM_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_locom_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t mode_start_time_ms, uint64_t mode_elapsed_time_ms, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, mode_start_time_ms);
    _mav_put_uint64_t(buf, 8, mode_elapsed_time_ms);
    _mav_put_uint8_t(buf, 16, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_STATE, buf, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
#else
    mavlink_locom_state_t *packet = (mavlink_locom_state_t *)msgbuf;
    packet->mode_start_time_ms = mode_start_time_ms;
    packet->mode_elapsed_time_ms = mode_elapsed_time_ms;
    packet->mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOCOM_STATE, (const char *)packet, MAVLINK_MSG_ID_LOCOM_STATE_MIN_LEN, MAVLINK_MSG_ID_LOCOM_STATE_LEN, MAVLINK_MSG_ID_LOCOM_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE LOCOM_STATE UNPACKING


/**
 * @brief Get field mode_start_time_ms from locom_state message
 *
 * @return The ID of the locomotion module command
 */
static inline uint64_t mavlink_msg_locom_state_get_mode_start_time_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field mode_elapsed_time_ms from locom_state message
 *
 * @return The ID of the locomotion module command
 */
static inline uint64_t mavlink_msg_locom_state_get_mode_elapsed_time_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field mode from locom_state message
 *
 * @return duration of the locomotion command
 */
static inline uint8_t mavlink_msg_locom_state_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a locom_state message into a struct
 *
 * @param msg The message to decode
 * @param locom_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_locom_state_decode(const mavlink_message_t* msg, mavlink_locom_state_t* locom_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    locom_state->mode_start_time_ms = mavlink_msg_locom_state_get_mode_start_time_ms(msg);
    locom_state->mode_elapsed_time_ms = mavlink_msg_locom_state_get_mode_elapsed_time_ms(msg);
    locom_state->mode = mavlink_msg_locom_state_get_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LOCOM_STATE_LEN? msg->len : MAVLINK_MSG_ID_LOCOM_STATE_LEN;
        memset(locom_state, 0, MAVLINK_MSG_ID_LOCOM_STATE_LEN);
    memcpy(locom_state, _MAV_PAYLOAD(msg), len);
#endif
}
