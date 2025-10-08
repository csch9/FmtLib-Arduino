#include <Arduino.h>
#include "fmt.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    static int i = 0;

    // fmt::memory_buffer buffer; // 500 bytes
    fmt::basic_memory_buffer<char, 64> buffer; // 64 bytes
    fmt::format_to(fmt::appender(buffer), "Counter {}", i++);
    buffer.push_back('\0'); // need to null-terminate manually
    Serial.println(buffer.data());

    char c_buffer[64];
    auto result = fmt::format_to_n(c_buffer, sizeof(c_buffer) - 1, "Counter {}", i++);
    *result.out = '\0'; // need to null-terminate manually
    Serial.println(c_buffer);

    delay(1000);
}
