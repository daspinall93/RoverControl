#pragma once
// MESSAGE CAMERA_COMMAND PACKING

#define MAVLINK_MSG_ID_CAMERA_COMMAND 28

MAVPACKED(
typedef struct __mavlink_camera_command_t {
 uint8_t new_command; /*< */
}) mavlink_camera_command_t;

#define MAVLINK_MSG_ID_CAMERA_COMMAND_LEN 1
#define MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN 1
#define MAVLINK_MSG_ID_28_LEN 1
#define MAVLINK_MSG_ID_28_MIN_LEN 1

#define MAVLINK_MSG_ID_CAMERA_COMMAND_CRC 25
#define MAVLINK_MSG_ID_28_CRC 25



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CAMERA_COMMAND { \
    28, \
    "CAMERA_COMMAND", \
    1, \
    {  { "new_command", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_camera_command_t, new_command) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CAMERA_COMMAND { \
    "CAMERA_COMMAND", \
    1, \
    {  { "new_command", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_camera_command_t, new_command) }, \
         } \
}
#endif

/**
 * @brief Pack a camera_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param new_command 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_camera_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t new_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAMERA_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, new_command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN);
#else
    mavlink_camera_command_t packet;
    packet.new_command = new_command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CAMERA_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
}

/**
 * @brief Pack a camera_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param new_command 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_camera_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t new_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAMERA_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, new_command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN);
#else
    mavlink_camera_command_t packet;
    packet.new_command = new_command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CAMERA_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
}

/**
 * @brief Encode a camera_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param camera_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_camera_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_camera_command_t* camera_command)
{
    return mavlink_msg_camera_command_pack(system_id, component_id, msg, camera_command->new_command);
}

/**
 * @brief Encode a camera_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param camera_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_camera_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_camera_command_t* camera_command)
{
    return mavlink_msg_camera_command_pack_chan(system_id, component_id, chan, msg, camera_command->new_command);
}

/**
 * @brief Send a camera_command message
 * @param chan MAVLink channel to send the message
 *
 * @param new_command 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_camera_command_send(mavlink_channel_t chan, uint8_t new_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAMERA_COMMAND_LEN];
    _mav_put_uint8_t(buf, 0, new_command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAMERA_COMMAND, buf, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
#else
    mavlink_camera_command_t packet;
    packet.new_command = new_command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAMERA_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
#endif
}

/**
 * @brief Send a camera_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_camera_command_send_struct(mavlink_channel_t chan, const mavlink_camera_command_t* camera_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_camera_command_send(chan, camera_command->new_command);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAMERA_COMMAND, (const char *)camera_command, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_CAMERA_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_camera_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t new_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, new_command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAMERA_COMMAND, buf, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
#else
    mavlink_camera_command_t *packet = (mavlink_camera_command_t *)msgbuf;
    packet->new_command = new_command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAMERA_COMMAND, (const char *)packet, MAVLINK_MSG_ID_CAMERA_COMMAND_MIN_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN, MAVLINK_MSG_ID_CAMERA_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE CAMERA_COMMAND UNPACKING


/**
 * @brief Get field new_command from camera_command message
 *
 * @return 
 */
static inline uint8_t mavlink_msg_camera_command_get_new_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a camera_command message into a struct
 *
 * @param msg The message to decode
 * @param camera_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_camera_command_decode(const mavlink_message_t* msg, mavlink_camera_command_t* camera_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    camera_command->new_command = mavlink_msg_camera_command_get_new_command(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CAMERA_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_CAMERA_COMMAND_LEN;
        memset(camera_command, 0, MAVLINK_MSG_ID_CAMERA_COMMAND_LEN);
    memcpy(camera_command, _MAV_PAYLOAD(msg), len);
#endif
}
