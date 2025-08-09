#include "FmtLib.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println(fmt::format("Hello, {}!", "World").c_str());
    delay(5000);
}