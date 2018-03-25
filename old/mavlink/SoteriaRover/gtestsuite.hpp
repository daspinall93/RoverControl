/** @file
 *	@brief MAVLink comm testsuite protocol generated from SoteriaRover.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "SoteriaRover.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(SoteriaRover, HEARTBEAT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::HEARTBEAT packet_in{};
    packet_in.locom_mode = 5;
    packet_in.motor1_mode = 72;
    packet_in.motor2_mode = 139;
    packet_in.mavlink_version = 3;

    mavlink::SoteriaRover::msg::HEARTBEAT packet1{};
    mavlink::SoteriaRover::msg::HEARTBEAT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.locom_mode, packet2.locom_mode);
    EXPECT_EQ(packet1.motor1_mode, packet2.motor1_mode);
    EXPECT_EQ(packet1.motor2_mode, packet2.motor2_mode);
    EXPECT_EQ(packet1.mavlink_version, packet2.mavlink_version);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, HEARTBEAT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_heartbeat_t packet_c {
         5, 72, 139, 3
    };

    mavlink::SoteriaRover::msg::HEARTBEAT packet_in{};
    packet_in.locom_mode = 5;
    packet_in.motor1_mode = 72;
    packet_in.motor2_mode = 139;
    packet_in.mavlink_version = 3;

    mavlink::SoteriaRover::msg::HEARTBEAT packet2{};

    mavlink_msg_heartbeat_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.locom_mode, packet2.locom_mode);
    EXPECT_EQ(packet_in.motor1_mode, packet2.motor1_mode);
    EXPECT_EQ(packet_in.motor2_mode, packet2.motor2_mode);
    EXPECT_EQ(packet_in.mavlink_version, packet2.mavlink_version);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, MOTOR_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::MOTOR_COMMAND packet_in{};
    packet_in.commandid = 41;
    packet_in.duration_ms = 93372036854775807ULL;
    packet_in.power_per = 963497880;
    packet_in.newCommand = 108;

    mavlink::SoteriaRover::msg::MOTOR_COMMAND packet1{};
    mavlink::SoteriaRover::msg::MOTOR_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.commandid, packet2.commandid);
    EXPECT_EQ(packet1.duration_ms, packet2.duration_ms);
    EXPECT_EQ(packet1.power_per, packet2.power_per);
    EXPECT_EQ(packet1.newCommand, packet2.newCommand);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, MOTOR_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_motor_command_t packet_c {
         93372036854775807ULL, 963497880, 41, 108
    };

    mavlink::SoteriaRover::msg::MOTOR_COMMAND packet_in{};
    packet_in.commandid = 41;
    packet_in.duration_ms = 93372036854775807ULL;
    packet_in.power_per = 963497880;
    packet_in.newCommand = 108;

    mavlink::SoteriaRover::msg::MOTOR_COMMAND packet2{};

    mavlink_msg_motor_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.commandid, packet2.commandid);
    EXPECT_EQ(packet_in.duration_ms, packet2.duration_ms);
    EXPECT_EQ(packet_in.power_per, packet2.power_per);
    EXPECT_EQ(packet_in.newCommand, packet2.newCommand);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, MOTOR_REPORT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::MOTOR_REPORT packet_in{};
    packet_in.m1_sub_mode = 53;
    packet_in.m1_pwmInput = 963497880;
    packet_in.m2_sub_mode = 120;
    packet_in.m2_pwmInput = 963498088;
    packet_in.modeElapsedTime_ms = 93372036854775807ULL;
    packet_in.mode = 187;

    mavlink::SoteriaRover::msg::MOTOR_REPORT packet1{};
    mavlink::SoteriaRover::msg::MOTOR_REPORT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.m1_sub_mode, packet2.m1_sub_mode);
    EXPECT_EQ(packet1.m1_pwmInput, packet2.m1_pwmInput);
    EXPECT_EQ(packet1.m2_sub_mode, packet2.m2_sub_mode);
    EXPECT_EQ(packet1.m2_pwmInput, packet2.m2_pwmInput);
    EXPECT_EQ(packet1.modeElapsedTime_ms, packet2.modeElapsedTime_ms);
    EXPECT_EQ(packet1.mode, packet2.mode);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, MOTOR_REPORT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_motor_report_t packet_c {
         93372036854775807ULL, 963497880, 963498088, 53, 120, 187
    };

    mavlink::SoteriaRover::msg::MOTOR_REPORT packet_in{};
    packet_in.m1_sub_mode = 53;
    packet_in.m1_pwmInput = 963497880;
    packet_in.m2_sub_mode = 120;
    packet_in.m2_pwmInput = 963498088;
    packet_in.modeElapsedTime_ms = 93372036854775807ULL;
    packet_in.mode = 187;

    mavlink::SoteriaRover::msg::MOTOR_REPORT packet2{};

    mavlink_msg_motor_report_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.m1_sub_mode, packet2.m1_sub_mode);
    EXPECT_EQ(packet_in.m1_pwmInput, packet2.m1_pwmInput);
    EXPECT_EQ(packet_in.m2_sub_mode, packet2.m2_sub_mode);
    EXPECT_EQ(packet_in.m2_pwmInput, packet2.m2_pwmInput);
    EXPECT_EQ(packet_in.modeElapsedTime_ms, packet2.modeElapsedTime_ms);
    EXPECT_EQ(packet_in.mode, packet2.mode);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, INERT_REPORT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::INERT_REPORT packet_in{};
    packet_in.roll_deg = 17.0;
    packet_in.pitch_deg = 45.0;
    packet_in.yaw_deg = 73.0;
    packet_in.tiltFlag = 41;

    mavlink::SoteriaRover::msg::INERT_REPORT packet1{};
    mavlink::SoteriaRover::msg::INERT_REPORT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.roll_deg, packet2.roll_deg);
    EXPECT_EQ(packet1.pitch_deg, packet2.pitch_deg);
    EXPECT_EQ(packet1.yaw_deg, packet2.yaw_deg);
    EXPECT_EQ(packet1.tiltFlag, packet2.tiltFlag);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, INERT_REPORT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_inert_report_t packet_c {
         17.0, 45.0, 73.0, 41
    };

    mavlink::SoteriaRover::msg::INERT_REPORT packet_in{};
    packet_in.roll_deg = 17.0;
    packet_in.pitch_deg = 45.0;
    packet_in.yaw_deg = 73.0;
    packet_in.tiltFlag = 41;

    mavlink::SoteriaRover::msg::INERT_REPORT packet2{};

    mavlink_msg_inert_report_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.roll_deg, packet2.roll_deg);
    EXPECT_EQ(packet_in.pitch_deg, packet2.pitch_deg);
    EXPECT_EQ(packet_in.yaw_deg, packet2.yaw_deg);
    EXPECT_EQ(packet_in.tiltFlag, packet2.tiltFlag);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, INERT_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::INERT_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::INERT_COMMAND packet1{};
    mavlink::SoteriaRover::msg::INERT_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.newCommand, packet2.newCommand);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, INERT_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_inert_command_t packet_c {
         5
    };

    mavlink::SoteriaRover::msg::INERT_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::INERT_COMMAND packet2{};

    mavlink_msg_inert_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.newCommand, packet2.newCommand);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, SONAR_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::SONAR_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::SONAR_COMMAND packet1{};
    mavlink::SoteriaRover::msg::SONAR_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.newCommand, packet2.newCommand);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, SONAR_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_sonar_command_t packet_c {
         5
    };

    mavlink::SoteriaRover::msg::SONAR_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::SONAR_COMMAND packet2{};

    mavlink_msg_sonar_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.newCommand, packet2.newCommand);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, SONAR_REPORT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::SONAR_REPORT packet_in{};
    packet_in.objectDetected_flag = 17;
    packet_in.objectDistance_cm = 17.0;

    mavlink::SoteriaRover::msg::SONAR_REPORT packet1{};
    mavlink::SoteriaRover::msg::SONAR_REPORT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.objectDetected_flag, packet2.objectDetected_flag);
    EXPECT_EQ(packet1.objectDistance_cm, packet2.objectDistance_cm);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, SONAR_REPORT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_sonar_report_t packet_c {
         17.0, 17
    };

    mavlink::SoteriaRover::msg::SONAR_REPORT packet_in{};
    packet_in.objectDetected_flag = 17;
    packet_in.objectDistance_cm = 17.0;

    mavlink::SoteriaRover::msg::SONAR_REPORT packet2{};

    mavlink_msg_sonar_report_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.objectDetected_flag, packet2.objectDetected_flag);
    EXPECT_EQ(packet_in.objectDistance_cm, packet2.objectDistance_cm);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, CAMERA_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::CAMERA_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::CAMERA_COMMAND packet1{};
    mavlink::SoteriaRover::msg::CAMERA_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.newCommand, packet2.newCommand);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, CAMERA_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_camera_command_t packet_c {
         5
    };

    mavlink::SoteriaRover::msg::CAMERA_COMMAND packet_in{};
    packet_in.newCommand = 5;

    mavlink::SoteriaRover::msg::CAMERA_COMMAND packet2{};

    mavlink_msg_camera_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.newCommand, packet2.newCommand);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
