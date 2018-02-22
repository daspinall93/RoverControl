// MESSAGE LOCOM_STATE support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief LOCOM_STATE message
 *
 * The state structure of the locomotion module
 */
struct LOCOM_STATE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 5;
    static constexpr size_t LENGTH = 17;
    static constexpr size_t MIN_LENGTH = 17;
    static constexpr uint8_t CRC_EXTRA = 42;
    static constexpr auto NAME = "LOCOM_STATE";


    uint64_t mode_start_time_ms; /*< The ID of the locomotion module command */
    uint64_t mode_elapsed_time_ms; /*< The ID of the locomotion module command */
    uint8_t mode; /*< duration of the locomotion command */


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
        ss << "  mode_start_time_ms: " << mode_start_time_ms << std::endl;
        ss << "  mode_elapsed_time_ms: " << mode_elapsed_time_ms << std::endl;
        ss << "  mode: " << +mode << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << mode_start_time_ms;            // offset: 0
        map << mode_elapsed_time_ms;          // offset: 8
        map << mode;                          // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> mode_start_time_ms;            // offset: 0
        map >> mode_elapsed_time_ms;          // offset: 8
        map >> mode;                          // offset: 16
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
