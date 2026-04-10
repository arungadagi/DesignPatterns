#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

#include "../FactoryExample.h"

int main() {
    auto e = NotificationFactory::create("email");
    assert(e != nullptr);
    auto s = NotificationFactory::create("sms");
    assert(s != nullptr);
    auto p = NotificationFactory::create("push");
    assert(p != nullptr);
    auto n = NotificationFactory::create("unknown");
    assert(n == nullptr);

    // Test output capture
    auto sender = NotificationFactory::create("email");
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    sender->send("user@example.com", "Hello");
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("[EMAIL]") != std::string::npos);
    assert(out.find("user@example.com") != std::string::npos);
    assert(out.find("Hello") != std::string::npos);

    std::cout << "C++ simple tests passed\n";
    return 0;
}
