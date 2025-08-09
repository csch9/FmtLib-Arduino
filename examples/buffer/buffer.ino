#include "FmtLib.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    static int i = 0;

    // fmt::basic_memory_buffer<char, 64> buffer; // 64 bytes
    fmt::memory_buffer buffer; // 500 bytes
    fmt::format_to(fmt::appender(buffer), "A counter {}", i++);
    buffer.push_back('\0'); // need to null-terminate manually
    Serial.println(buffer.data());

    delay(1000);
}
