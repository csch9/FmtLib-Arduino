# FmtLib

> A port of the {fmt} library for Arduino.

This port is based on {fmt} 11.2.0 and is provided as a header-only wrapper to play nicely with the Arduino build system while keeping the binary size small.

This library depends on the STL. Therefore will not work with Arduino Uno.

## Usage

Include the wrapper header:

```c++
#include "FmtLib.h"
```

Basic formatting to Serial:

```c++
Serial.println(fmt::format("Hello, {}!", "World").c_str());
```

Formatting to a fmt buffer:

```c++
// fmt::memory_buffer buffer;           // 500 bytes default capacity
fmt::basic_memory_buffer<char, 64> buffer; // 64 bytes static capacity
fmt::format_to(fmt::appender(buffer), "Counter {}", 42);
buffer.push_back('\0'); // buffer is not null-terminate
Serial.println(buffer.data());
```

Formatting to a c buffer:

```c++
char c_buffer[64];
auto result = fmt::format_to_n(c_buffer, sizeof(c_buffer) - 1, "Counter {}", i++);
*result.out = '\0'; // need to null-terminate manually
Serial.println(c_buffer);
```

## Notes on configuration

For smaller binaries this port sets:
- `FMT_USE_LOCALE` to `0` (locale support disabled)
- `FMT_BUILTIN_TYPES` to `0` (only instantiate formatting for used types)

## Examples

Arduino sketches demonstrating usage are in `examples/basic` and `examples/buffer`. Tested on an ESP32S3.

## Update

To update the vendored headers, clone [{fmt}](https://github.com/fmtlib/fmt) and copy the folder `include/fmt` into this repository at `src/fmt` (replace the existing folder).

## License

FmtLib is Arduino port of [{fmt}](https://github.com/fmtlib/fmt) which is distributed under the MIT license.