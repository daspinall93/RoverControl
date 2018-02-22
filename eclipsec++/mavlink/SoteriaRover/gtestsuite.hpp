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

TEST(SoteriaRover, LOCOM_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::LOCOM_COMMAND packet_in{};
    packet_in.command_id = 29;
    packet_in.duration_ms = 963497464;
    packet_in.power = 963497672;
    packet_in.new_command = 96;

    mavlink::SoteriaRover::msg::LOCOM_COMMAND packet1{};
    mavlink::SoteriaRover::msg::LOCOM_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.command_id, packet2.command_id);
    EXPECT_EQ(packet1.duration_ms, packet2.duration_ms);
    EXPECT_EQ(packet1.power, packet2.power);
    EXPECT_EQ(packet1.new_command, packet2.new_command);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, LOCOM_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_locom_command_t packet_c {
         963497464, 963497672, 29, 96
    };

    mavlink::SoteriaRover::msg::LOCOM_COMMAND packet_in{};
    packet_in.command_id = 29;
    packet_in.duration_ms = 963497464;
    packet_in.power = 963497672;
    packet_in.new_command = 96;

    mavlink::SoteriaRover::msg::LOCOM_COMMAND packet2{};

    mavlink_msg_locom_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.command_id, packet2.command_id);
    EXPECT_EQ(packet_in.duration_ms, packet2.duration_ms);
    EXPECT_EQ(packet_in.power, packet2.power);
    EXPECT_EQ(packet_in.new_command, packet2.new_command);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, LOCOM_REPORT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::LOCOM_REPORT packet_in{};
    packet_in.mode_elapsed_time_ms = 93372036854775807ULL;
    packet_in.mode = 29;

    mavlink::SoteriaRover::msg::LOCOM_REPORT packet1{};
    mavlink::SoteriaRover::msg::LOCOM_REPORT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.mode_elapsed_time_ms, packet2.mode_elapsed_time_ms);
    EXPECT_EQ(packet1.mode, packet2.mode);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, LOCOM_REPORT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_locom_report_t packet_c {
         93372036854775807ULL, 29
    };

    mavlink::SoteriaRover::msg::LOCOM_REPORT packet_in{};
    packet_in.mode_elapsed_time_ms = 93372036854775807ULL;
    packet_in.mode = 29;

    mavlink::SoteriaRover::msg::LOCOM_REPORT packet2{};

    mavlink_msg_locom_report_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.mode_elapsed_time_ms, packet2.mode_elapsed_time_ms);
    EXPECT_EQ(packet_in.mode, packet2.mode);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(SoteriaRover, LOCOM_STATE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::SoteriaRover::msg::LOCOM_STATE packet_in{};
    packet_in.mode_start_time_ms = 93372036854775807ULL;
    packet_in.mode_elapsed_time_ms = 93372036854776311ULL;
    packet_in.mode = 53;

    mavlink::SoteriaRover::msg::LOCOM_STATE packet1{};
    mavlink::SoteriaRover::msg::LOCOM_STATE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.mode_start_time_ms, packet2.mode_start_time_ms);
    EXPECT_EQ(packet1.mode_elapsed_time_ms, packet2.mode_elapsed_time_ms);
    EXPECT_EQ(packet1.mode, packet2.mode);
}

#ifdef TEST_INTEROP
TEST(SoteriaRover_interop, LOCOM_STATE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_locom_state_t packet_c {
         93372036854775807ULL, 93372036854776311ULL, 53
    };

    mavlink::SoteriaRover::msg::LOCOM_STATE packet_in{};
    packet_in.mode_start_time_ms = 93372036854775807ULL;
    packet_in.mode_elapsed_time_ms = 93372036854776311ULL;
    packet_in.mode = 53;

    mavlink::SoteriaRover::msg::LOCOM_STATE packet2{};

    mavlink_msg_locom_state_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.mode_start_time_ms, packet2.mode_start_time_ms);
    EXPECT_EQ(packet_in.mode_elapsed_time_ms, packet2.mode_elapsed_time_ms);
    EXPECT_EQ(packet_in.mode, packet2.mode);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
