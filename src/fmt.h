// Use the header only because compiling the source with the Arduino build system is difficult.
#define FMT_HEADER_ONLY

// Significantly reduce binary size - https://vitaut.net/posts/2024/binary-size/
#define FMT_USE_LOCALE 0    // Disable locale support
#define FMT_BUILTIN_TYPES 0 // Only include formatting types when they are used (increase per call size, but reduces library size)

// Backup conflicting macros
#pragma push_macro("F")
#pragma push_macro("B1")

// Disable conflicting macros
#undef B1
#undef F

// Include the library
#include <fmt/format.h>

// Restore conflicting macros
#pragma pop_macro("F")
#pragma pop_macro("B1")