# FmtLib

> A port of the {fmt} library for Arduino.

This port is based on {fmt} 11.2.0 and is provided as a header-only wrapper to play nicely with the Arduino build system while keeping the binary size small.

## Usage

Include the library:

```c++
#include "FmtLib.h"
```

Basic formatting to Serial:

```c++
Serial.println(fmt::format("millis: {}", millis()).c_str());
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
