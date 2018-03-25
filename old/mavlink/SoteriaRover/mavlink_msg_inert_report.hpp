// MESSAGE INERT_REPORT support class

#pragma once

namespace mavlink {
namespace SoteriaRover {
namespace msg {

/**
 * @brief INERT_REPORT message
 *
 * 
 */
struct INERT_REPORT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 20;
    static constexpr size_t LENGTH = 13;
    static constexpr size_t MIN_LENGTH = 13;
    static constexpr uint8_t CRC_EXTRA = 173;
    static constexpr auto NAME = "INERT_REPORT";


    float roll_deg; /*<  */
    float pitch_deg; /*<  */
    float yaw_deg; /*<  */
    uint8_t tiltFlag; /*<  */


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
        ss << "  roll_deg: " << roll_deg << std::endl;
        ss << "  pitch_deg: " << pitch_deg << std::endl;
        ss << "  yaw_deg: " << yaw_deg << std::endl;
        ss << "  tiltFlag: " << +tiltFlag << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << roll_deg;                      // offset: 0
        map << pitch_deg;                     // offset: 4
        map << yaw_deg;                       // offset: 8
        map << tiltFlag;                      // offset: 12
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> roll_deg;                      // offset: 0
        map >> pitch_deg;                     // offset: 4
        map >> yaw_deg;                       // offset: 8
        map >> tiltFlag;                      // offset: 12
    }
};

} // namespace msg
} // namespace SoteriaRover
} // namespace mavlink
