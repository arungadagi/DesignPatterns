#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <iostream>

// Use the production header generated for the example.
#include "../FactoryExample.h"

// ============================================================================
// Google Test Suite (TDD approach)
// ============================================================================

class NotificationFactoryTest : public ::testing::Test {
protected:
    // Setup/teardown if needed
};

// TEST 1: Factory creates EmailSender for 'email' channel
TEST_F(NotificationFactoryTest, CreateEmailSender) {
    auto sender = NotificationFactory::create("email");
    ASSERT_NE(sender, nullptr);
}

// TEST 2: Factory creates SMSSender for 'sms' channel
TEST_F(NotificationFactoryTest, CreateSMSSender) {
    auto sender = NotificationFactory::create("sms");
    ASSERT_NE(sender, nullptr);
}

// TEST 3: Factory creates PushSender for 'push' channel
TEST_F(NotificationFactoryTest, CreatePushSender) {
    auto sender = NotificationFactory::create("push");
    ASSERT_NE(sender, nullptr);
}

// TEST 4: Factory returns nullptr for unknown channel
TEST_F(NotificationFactoryTest, UnknownChannelReturnsNull) {
    auto sender = NotificationFactory::create("unknown");
    ASSERT_EQ(sender, nullptr);
}

// TEST 5: Factory is case-sensitive
TEST_F(NotificationFactoryTest, FactoryIsCaseSensitive) {
    auto sender = NotificationFactory::create("EMAIL");
    ASSERT_EQ(sender, nullptr);
}

// TEST 6: Factory returns nullptr for empty channel
TEST_F(NotificationFactoryTest, EmptyChannelReturnsNull) {
    auto sender = NotificationFactory::create("");
    ASSERT_EQ(sender, nullptr);
}

// TEST 7: EmailSender sends without exception
TEST_F(NotificationFactoryTest, EmailSenderSendsMessage) {
    auto sender = NotificationFactory::create("email");
    ASSERT_NE(sender, nullptr);
    EXPECT_NO_THROW(sender->send("test@example.com", "Test message"));
}

// TEST 8: SMSSender sends without exception
TEST_F(NotificationFactoryTest, SMSSenderSendsMessage) {
    auto sender = NotificationFactory::create("sms");
    ASSERT_NE(sender, nullptr);
    EXPECT_NO_THROW(sender->send("+1234567890", "Test SMS"));
}

// TEST 9: PushSender sends without exception
TEST_F(NotificationFactoryTest, PushSenderSendsMessage) {
    auto sender = NotificationFactory::create("push");
    ASSERT_NE(sender, nullptr);
    EXPECT_NO_THROW(sender->send("device-123", "Test push"));
}

// TEST 10: Polymorphism - sender is a NotificationSender
TEST_F(NotificationFactoryTest, SenderIsNotificationSender) {
    auto sender = NotificationFactory::create("email");
    NotificationSender* base_ptr = sender.get();
    ASSERT_NE(base_ptr, nullptr);
}

// TEST 11: Factory output type verification with output capture
TEST_F(NotificationFactoryTest, EmailSenderOutputFormat) {
    auto sender = NotificationFactory::create("email");
    
    testing::internal::CaptureStdout();
    sender->send("user@example.com", "Hello");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[EMAIL]") != std::string::npos);
    EXPECT_TRUE(output.find("user@example.com") != std::string::npos);
    EXPECT_TRUE(output.find("Hello") != std::string::npos);
}

// TEST 12: Factory output type verification for SMS
TEST_F(NotificationFactoryTest, SMSSenderOutputFormat) {
    auto sender = NotificationFactory::create("sms");
    
    testing::internal::CaptureStdout();
    sender->send("+1111111111", "SMS Text");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[SMS]") != std::string::npos);
    EXPECT_TRUE(output.find("+1111111111") != std::string::npos);
    EXPECT_TRUE(output.find("SMS Text") != std::string::npos);
}

// TEST 13: Factory output type verification for Push
TEST_F(NotificationFactoryTest, PushSenderOutputFormat) {
    auto sender = NotificationFactory::create("push");
    
    testing::internal::CaptureStdout();
    sender->send("device-xyz", "Push Msg");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[PUSH]") != std::string::npos);
    EXPECT_TRUE(output.find("device-xyz") != std::string::npos);
    EXPECT_TRUE(output.find("Push Msg") != std::string::npos);
}
