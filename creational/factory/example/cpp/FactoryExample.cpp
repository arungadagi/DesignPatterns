/*
Real-world Factory Method example: Notification sender factory.

Mapping to pattern participants:
- `NotificationFactory` : Creator
- `NotificationSender`  : Product
- `EmailSender` / `SMSSender` / `PushSender` : ConcreteProduct implementations

This example shows selecting a concrete sender at runtime (e.g., based on configuration).
*/

#include "FactoryExample.h"
#include <iostream>

void EmailSender::send(const std::string& recipient, const std::string& message) {
    std::cout << "[EMAIL] To: " << recipient << " | " << message << std::endl;
}

void SMSSender::send(const std::string& recipient, const std::string& message) {
    std::cout << "[SMS] To: " << recipient << " | " << message << std::endl;
}

void PushSender::send(const std::string& recipient, const std::string& message) {
    std::cout << "[PUSH] To: " << recipient << " | " << message << std::endl;
}

std::unique_ptr<NotificationSender> NotificationFactory::create(const std::string& channel) {
    if (channel == "email") return std::make_unique<EmailSender>();
    if (channel == "sms") return std::make_unique<SMSSender>();
    if (channel == "push") return std::make_unique<PushSender>();
    return nullptr;
}
