#include "FactoryExample.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string channel = "email";
    if (argc > 1) channel = argv[1];

    auto sender = NotificationFactory::create(channel);
    if (!sender) {
        std::cerr << "Unknown channel: " << channel << std::endl;
        return 1;
    }

    // In a real app these values would come from business logic / configuration.
    sender->send("user@example.com", "Hello from FactoryExample (real-world)");
    return 0;
}
