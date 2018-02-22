// MESSAGE LOCOM_COMMAND support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief LOCOM_COMMAND message
 *
 * A command to the locomotion module
 */
struct LOCOM_COMMAND : mavlink::Message {
    static constexpr msgid_t MSG_ID = 3;
    static constexpr size_t LENGTH = 10;
    static constexpr size_t MIN_LENGTH = 10;
    static constexpr uint8_t CRC_EXTRA = 60;
    static constexpr auto NAME = "LOCOM_COMMAND";


    uint8_t command_id; /*< The ID of the locomotion module command */
    uint32_t duration_ms; /*< duration of the locomotion command */
    uint32_t power; /*< Power (0-100%) of the commanded locomotion manoeuvre */
    uint8_t new_command; /*< new command boolean */


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
        ss << "  command_id: " << +command_id << std::endl;
        ss << "  duration_ms: " << duration_ms << std::endl;
        ss << "  power: " << power << std::endl;
        ss << "  new_command: " << +new_command << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << duration_ms;                   // offset: 0
        map << power;                         // offset: 4
        map << command_id;                    // offset: 8
        map << new_command;                   // offset: 9
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> duration_ms;                   // offset: 0
        map >> power;                         // offset: 4
        map >> command_id;                    // offset: 8
        map >> new_command;                   // offset: 9
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
