/*
  Declarations for the Factory Method example.
  Moved out of the .cpp so tests and other translation units can include it.
*/

#pragma once

#include <memory>
#include <string>

class NotificationSender {
public:
    virtual ~NotificationSender() = default;
    virtual void send(const std::string& recipient, const std::string& message) = 0;
};

class EmailSender : public NotificationSender {
public:
    void send(const std::string& recipient, const std::string& message) override;
};

class SMSSender : public NotificationSender {
public:
    void send(const std::string& recipient, const std::string& message) override;
};

class PushSender : public NotificationSender {
public:
    void send(const std::string& recipient, const std::string& message) override;
};

class NotificationFactory {
public:
    static std::unique_ptr<NotificationSender> create(const std::string& channel);
};
