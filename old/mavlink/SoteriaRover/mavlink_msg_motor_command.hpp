// MESSAGE MOTOR_COMMAND support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief MOTOR_COMMAND message
 *
 * A command to the locomotion module
 */
struct MOTOR_COMMAND : mavlink::Message {
    static constexpr msgid_t MSG_ID = 3;
    static constexpr size_t LENGTH = 14;
    static constexpr size_t MIN_LENGTH = 14;
    static constexpr uint8_t CRC_EXTRA = 119;
    static constexpr auto NAME = "MOTOR_COMMAND";


    uint8_t commandid; /*< The ID of the locomotion module command */
    uint64_t duration_ms; /*< duration of the locomotion command */
    uint32_t power_per; /*< Power (0-100%) of the commanded locomotion manoeuvre */
    uint8_t newCommand; /*< new command boolean */


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
        ss << "  commandid: " << +commandid << std::endl;
        ss << "  duration_ms: " << duration_ms << std::endl;
        ss << "  power_per: " << power_per << std::endl;
        ss << "  newCommand: " << +newCommand << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << duration_ms;                   // offset: 0
        map << power_per;                     // offset: 8
        map << commandid;                     // offset: 12
        map << newCommand;                    // offset: 13
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> duration_ms;                   // offset: 0
        map >> power_per;                     // offset: 8
        map >> commandid;                     // offset: 12
        map >> newCommand;                    // offset: 13
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
