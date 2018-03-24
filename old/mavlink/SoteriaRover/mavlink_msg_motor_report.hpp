// MESSAGE MOTOR_REPORT support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief MOTOR_REPORT message
 *
 * 
 */
struct MOTOR_REPORT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 11;
    static constexpr size_t LENGTH = 19;
    static constexpr size_t MIN_LENGTH = 19;
    static constexpr uint8_t CRC_EXTRA = 87;
    static constexpr auto NAME = "MOTOR_REPORT";


    uint8_t m1_sub_mode; /*<  */
    uint32_t m1_pwmInput; /*<  */
    uint8_t m2_sub_mode; /*<  */
    uint32_t m2_pwmInput; /*<  */
    uint64_t modeElapsedTime_ms; /*< The ID of the locomotion module command */
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
        ss << "  m1_sub_mode: " << +m1_sub_mode << std::endl;
        ss << "  m1_pwmInput: " << m1_pwmInput << std::endl;
        ss << "  m2_sub_mode: " << +m2_sub_mode << std::endl;
        ss << "  m2_pwmInput: " << m2_pwmInput << std::endl;
        ss << "  modeElapsedTime_ms: " << modeElapsedTime_ms << std::endl;
        ss << "  mode: " << +mode << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << modeElapsedTime_ms;            // offset: 0
        map << m1_pwmInput;                   // offset: 8
        map << m2_pwmInput;                   // offset: 12
        map << m1_sub_mode;                   // offset: 16
        map << m2_sub_mode;                   // offset: 17
        map << mode;                          // offset: 18
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> modeElapsedTime_ms;            // offset: 0
        map >> m1_pwmInput;                   // offset: 8
        map >> m2_pwmInput;                   // offset: 12
        map >> m1_sub_mode;                   // offset: 16
        map >> m2_sub_mode;                   // offset: 17
        map >> mode;                          // offset: 18
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
