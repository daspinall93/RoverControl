// MESSAGE SONAR_REPORT support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief SONAR_REPORT message
 *
 * 
 */
struct SONAR_REPORT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 27;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 32;
    static constexpr auto NAME = "SONAR_REPORT";


    uint8_t objectDetected_flag; /*<  */
    float objectDistance_cm; /*<  */


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
        ss << "  objectDetected_flag: " << +objectDetected_flag << std::endl;
        ss << "  objectDistance_cm: " << objectDistance_cm << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << objectDistance_cm;             // offset: 0
        map << objectDetected_flag;           // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> objectDistance_cm;             // offset: 0
        map >> objectDetected_flag;           // offset: 4
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
