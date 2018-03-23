// MESSAGE HEARTBEAT support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief HEARTBEAT message
 *
 * The heartbeat message shows that a system is present and responding. Currently contains the locomotion module mode and mavlink version
 */
struct HEARTBEAT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 0;
    static constexpr size_t LENGTH = 4;
    static constexpr size_t MIN_LENGTH = 4;
    static constexpr uint8_t CRC_EXTRA = 176;
    static constexpr auto NAME = "HEARTBEAT";


    uint8_t locom_mode; /*< Mode of the locomotion module */
    uint8_t motor1_mode; /*< Mode of motor 1 */
    uint8_t motor2_mode; /*< Mode of motor 2 */
    uint8_t mavlink_version; /*< MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  locom_mode: " << +locom_mode << std::endl;
        ss << "  motor1_mode: " << +motor1_mode << std::endl;
        ss << "  motor2_mode: " << +motor2_mode << std::endl;
        ss << "  mavlink_version: " << +mavlink_version << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << locom_mode;                    // offset: 0
        map << motor1_mode;                   // offset: 1
        map << motor2_mode;                   // offset: 2
        map << uint8_t(3);               // offset: 3
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> locom_mode;                    // offset: 0
        map >> motor1_mode;                   // offset: 1
        map >> motor2_mode;                   // offset: 2
        map >> mavlink_version;               // offset: 3
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
