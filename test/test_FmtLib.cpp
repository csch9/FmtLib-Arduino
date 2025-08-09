// More information about PlatformIO Unit Testing:
// https://docs.platformio.org/en/latest/advanced/unit-testing/index.html

#include <Arduino.h>
#include "unity.h"
#include "FmtLib.h"

/*------------------------------------------------------------------------------
 * TESTS FOR format (std::string)
 *----------------------------------------------------------------------------*/

void test_format_basic_string()
{
	std::string result = fmt::format("Hello, {}!", "world");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, world!", result.c_str(), "format basic string");
}

void test_format_integers()
{
	std::string result = fmt::format("Number: {}, Hex: {:x}", 42, 255);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Number: 42, Hex: ff", result.c_str(), "format integers");
}

void test_format_floats()
{
	std::string result = fmt::format("Pi: {:.3f}", 3.14159);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Pi: 3.142", result.c_str(), "format floats");
}

void test_format_complex()
{
	std::string result =
		fmt::format("User: {}, ID: {:0>4}, Active: {}, Score: {:.1f}%", "Bob", 123, true, 87.6);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("User: Bob, ID: 0123, Active: true, Score: 87.6%",
									 result.c_str(), "format complex");
}

/*------------------------------------------------------------------------------
 * TESTS FOR format_to
 *----------------------------------------------------------------------------*/

void test_format_to_basic_string()
{
	char buffer[20] = {0};
	auto result = fmt::format_to(buffer, "Hello, {}!", "world");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, world!", buffer, "format_to basic string");
	TEST_ASSERT_EQUAL_MESSAGE(13, result - buffer, "format_to return pointer position");
}

void test_format_to_integers()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "Dec: {}, Hex: {:x}, Oct: {:o}", 255, 255, 255);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Dec: 255, Hex: ff, Oct: 377", buffer, "format_to integers");
}

void test_format_to_hex()
{
	char buffer[25] = {0}; // Increased buffer size to prevent overflow
	fmt::format_to(buffer, "Hex: 0x{:X}", 255);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Hex: 0xFF", buffer, "format_to hex uppercase");
}

void test_format_to_octal_binary()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "Oct: {:o}, Bin: {:b}", 8, 5);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Oct: 10, Bin: 101", buffer, "format_to octal and binary");
}

void test_format_to_floats()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "Pi: {:.3f}, E: {:.2f}", 3.14159, 2.71828);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Pi: 3.142, E: 2.72", buffer, "format_to floats");
}

void test_format_to_alignment()
{
	char buffer[30] = {0}; // Increased buffer size to prevent overflow
	fmt::format_to(buffer, "Left: {:<5}, Right: {:>5}", "Hi", "Hi");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Left: Hi   , Right:    Hi", buffer, "format_to alignment");
}

void test_format_to_zero_padding()
{
	char buffer[25] = {0}; // Increased buffer size to prevent overflow
	fmt::format_to(buffer, "Padded: {:04d}", 42);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Padded: 0042", buffer, "format_to zero padding");
}

void test_format_to_scientific_notation()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "Scientific: {:.2e}", 1234.5);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Scientific: 1.23e+03", buffer, "format_to scientific notation");
}

void test_format_to_general_notation()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "General: {:.3g}", 0.000123);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("General: 0.000123", buffer, "format_to general notation");
}

void test_format_to_scientific_edge_cases()
{
	char buffer[30] = {0};
	fmt::format_to(buffer, "Large: {:.1e}", 1000000.0);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Large: 1.0e+06", buffer, "format_to scientific large numbers");
}

/*------------------------------------------------------------------------------
 * TESTS FOR format_to_n
 *----------------------------------------------------------------------------*/

void test_format_to_n_basic()
{
	char buffer[10] = {0};
	auto result = fmt::format_to_n(buffer, 9, "Hello, {}!", "world");
	TEST_ASSERT_EQUAL_MESSAGE(13, result.size, "format_to_n size calculation");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, wo", buffer, "format_to_n basic truncation");
}

void test_format_to_n_truncation()
{
	char buffer[6] = {0};
	auto result = fmt::format_to_n(buffer, 5, "Number: {}", 12345);
	TEST_ASSERT_EQUAL_MESSAGE(13, result.size, "format_to_n full size"); // "Number: 12345" is 13 chars
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Numbe", buffer, "format_to_n truncated output");
}

void test_format_to_n_zero_size()
{
	char buffer[10] = {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'};
	auto result = fmt::format_to_n(buffer, 0, "Hello");
	TEST_ASSERT_EQUAL_MESSAGE(5, result.size, "format_to_n zero size calculation");
	TEST_ASSERT_EQUAL_MESSAGE('x', buffer[0], "format_to_n zero size no modification");
}

/*------------------------------------------------------------------------------
 * TESTS FOR formatted_size
 *----------------------------------------------------------------------------*/

void test_formatted_size()
{
	size_t size = fmt::formatted_size("Hello, {}!", "world");
	TEST_ASSERT_EQUAL_MESSAGE(13, size, "formatted_size calculation"); // "Hello, world!"
}

void test_formatted_size_complex()
{
	size_t size = fmt::formatted_size("Number: {}, Float: {:.2f}", 12345, 3.14159);
	std::string actual = fmt::format("Number: {}, Float: {:.2f}", 12345, 3.14159);
	TEST_ASSERT_EQUAL_MESSAGE(actual.length(), size, "formatted_size complex");
}

/*------------------------------------------------------------------------------
 * TESTS FOR edge cases
 *----------------------------------------------------------------------------*/

void test_empty_format_string()
{
	std::string result = fmt::format("");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("", result.c_str(), "empty format string");
}

void test_no_arguments()
{
	std::string result = fmt::format("Just text, no placeholders");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Just text, no placeholders", result.c_str(), "no arguments");
}

void test_unmatched_braces()
{
	// Test single opening brace
	std::string result = fmt::format("Single {{ brace");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Single { brace", result.c_str(), "single opening brace");
	
	// Test single closing brace
	result = fmt::format("Single }} brace");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Single } brace", result.c_str(), "single closing brace");
}

void test_nested_braces()
{
	// Test nested braces
	std::string result = fmt::format("Nested: {{{}}}", "value");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Nested: {value}", result.c_str(), "nested braces");
	
	// Test multiple nested braces
	result = fmt::format("Multiple: {{{{{}}}}}", "test");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Multiple: {{test}}", result.c_str(), "multiple nested braces");
}

void test_zero_values()
{
	// Test zero integers
	std::string result = fmt::format("Zero int: {}", 0);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero int: 0", result.c_str(), "zero integer");
	
	// Test zero float
	result = fmt::format("Zero float: {:.2f}", 0.0f);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero float: 0.00", result.c_str(), "zero float");
	
	// Test zero with padding
	char buffer[20] = {0};
	fmt::format_to(buffer, "Zero padded: {:05d}", 0);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero padded: 00000", buffer, "zero with padding");
}

void test_negative_values()
{
	// Test negative integers
	std::string result = fmt::format("Negative: {}", -42);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Negative: -42", result.c_str(), "negative integer");
	
	// Test negative float
	result = fmt::format("Negative float: {:.2f}", -3.14159);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Negative float: -3.14", result.c_str(), "negative float");
	
	// Test negative with alignment
	char buffer[25] = {0};
	fmt::format_to(buffer, "Neg aligned: {:>8}", -123);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Neg aligned:     -123", buffer, "negative with alignment");
}

void test_large_numbers()
{
	// Test large integers
	std::string result = fmt::format("Large: {}", 2147483647);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Large: 2147483647", result.c_str(), "large integer");
	
	// Test large float
	result = fmt::format("Large float: {:.2e}", 1.23e+10);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Large float: 1.23e+10", result.c_str(), "large float");
	
	// Test large hex
	char buffer[25] = {0};
	fmt::format_to(buffer, "Large hex: 0x{:X}", 0xFFFFFFFF);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Large hex: 0xFFFFFFFF", buffer, "large hex");
}

void test_small_numbers()
{
	// Test very small float
	std::string result = fmt::format("Small: {:.6f}", 0.000001);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Small: 0.000001", result.c_str(), "small float");
	
	// Test small scientific notation
	result = fmt::format("Small sci: {:.2e}", 1.23e-10);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Small sci: 1.23e-10", result.c_str(), "small scientific");
}

void test_special_characters()
{
	// Test special characters in format string
	std::string result = fmt::format("Special: {} {} {}", "tab\t", "newline\n", "quote\"");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Special: tab\t newline\n quote\"", result.c_str(), "special characters");
	
	// Test unicode characters
	result = fmt::format("Unicode: {} {}", "café", "naïve");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Unicode: café naïve", result.c_str(), "unicode characters");
}

void test_boolean_values()
{
	// Test boolean true
	std::string result = fmt::format("Bool: {}", true);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Bool: true", result.c_str(), "boolean true");
	
	// Test boolean false
	result = fmt::format("Bool: {}", false);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Bool: false", result.c_str(), "boolean false");
	
	// Test boolean with custom format
	char buffer[20] = {0};
	fmt::format_to(buffer, "Bool: {:>5}", true);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Bool:  true", buffer, "boolean with alignment");
}

void test_empty_strings()
{
	// Test empty string argument
	std::string result = fmt::format("Empty: '{}'", "");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Empty: ''", result.c_str(), "empty string argument");
	
	// Test empty string with width
	char buffer[25] = {0};
	fmt::format_to(buffer, "Empty width: '{:>5}'", "");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Empty width: '     '", buffer, "empty string with width");
}

void test_precision_edge_cases()
{
	// Test zero precision
	std::string result = fmt::format("Zero prec: {:.0f}", 3.14159);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero prec: 3", result.c_str(), "zero precision");
	
	// Test high precision
	result = fmt::format("High prec: {:.10f}", 3.14159);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("High prec: 3.1415900000", result.c_str(), "high precision");
	
	// Test precision with zero value
	char buffer[30] = {0};
	fmt::format_to(buffer, "Zero with prec: {:.3f}", 0.0);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero with prec: 0.000", buffer, "zero with precision");
}

void test_width_edge_cases()
{
	// Test zero width
	std::string result = fmt::format("Zero width: {:0}", 42);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Zero width: 42", result.c_str(), "zero width");
	
	// Test very large width
	char buffer[50] = {0};
	fmt::format_to(buffer, "Large width: {:>20}", "test");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Large width:                 test", buffer, "large width");
	
	// Test width smaller than content
	result = fmt::format("Small width: {:>2}", "longer");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Small width: longer", result.c_str(), "width smaller than content");
}

void test_mixed_types()
{
	// Test mixing with formatting
	char buffer[50] = {0};
	fmt::format_to(buffer, "Mixed fmt: {:>5} {:.2f} {:>6}", 42, 3.14159, true);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Mixed fmt:    42 3.14   true", buffer, "mixed types with formatting");
}

void test_repeated_placeholders()
{
	// Test same argument used multiple times
	std::string result = fmt::format("Repeat: {} {} {}", "same", "same", "same");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Repeat: same same same", result.c_str(), "repeated placeholders");
	
	// Test indexed placeholders
	result = fmt::format("Indexed: {0} {1} {0}", "first", "second");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Indexed: first second first", result.c_str(), "indexed placeholders");
}

void test_format_to_edge_cases()
{
	// Test format_to with empty format
	char buffer[10] = {0};
	auto result = fmt::format_to(buffer, "");
	TEST_ASSERT_EQUAL_MESSAGE(0, result - buffer, "format_to empty format");
	
	// Test format_to with no placeholders
	char buffer2[20] = {0};
	result = fmt::format_to(buffer2, "no placeholders");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("no placeholders", buffer2, "format_to no placeholders");
	
	// Test format_to with exact buffer size
	char exact_buffer[4] = {0};
	result = fmt::format_to(exact_buffer, "123");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("123", exact_buffer, "format_to exact buffer size");
}

void test_format_to_n_edge_cases()
{
	// Test format_to_n with empty format
	char buffer[10] = {0};
	auto result = fmt::format_to_n(buffer, 9, "");
	TEST_ASSERT_EQUAL_MESSAGE(0, result.size, "format_to_n empty format size");
	
	// Test format_to_n with exact size
	result = fmt::format_to_n(buffer, 3, "123");
	TEST_ASSERT_EQUAL_MESSAGE(3, result.size, "format_to_n exact size");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("123", buffer, "format_to_n exact size content");
	
	// Test format_to_n with one char buffer
	char small_buffer[1] = {0};
	result = fmt::format_to_n(small_buffer, 1, "test");
	TEST_ASSERT_EQUAL_MESSAGE(4, result.size, "format_to_n one char size");
	TEST_ASSERT_EQUAL_MESSAGE('t', small_buffer[0], "format_to_n one char content");
}

void test_embedded_specific_edge_cases()
{
	// Test with very limited buffer sizes (common in embedded)
	char tiny_buffer[5] = {0};
	auto result = fmt::format_to_n(tiny_buffer, 4, "Hello World");
	TEST_ASSERT_EQUAL_MESSAGE(11, result.size, "tiny buffer size calculation");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Hell", tiny_buffer, "tiny buffer content");
	
	// Test with exact buffer size needed
	char exact_buffer[8] = {0};
	result = fmt::format_to_n(exact_buffer, 7, "1234567");
	TEST_ASSERT_EQUAL_MESSAGE(7, result.size, "exact buffer size");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("1234567", exact_buffer, "exact buffer content");
	
	// Test with overflow protection
	char overflow_buffer[3] = {0};
	result = fmt::format_to_n(overflow_buffer, 2, "overflow test");
	TEST_ASSERT_EQUAL_MESSAGE(13, result.size, "overflow buffer size");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("ov", overflow_buffer, "overflow buffer content");
}

void test_memory_constrained_scenarios()
{
	// Test with minimal memory usage
	char minimal_buffer[2] = {0};
	auto result = fmt::format_to_n(minimal_buffer, 1, "minimal");
	TEST_ASSERT_EQUAL_MESSAGE(7, result.size, "minimal buffer size");
	TEST_ASSERT_EQUAL_MESSAGE('m', minimal_buffer[0], "minimal buffer content");
	
	// Test with zero buffer size
	char zero_buffer[1] = {'x'};
	result = fmt::format_to_n(zero_buffer, 0, "should not write");
	TEST_ASSERT_EQUAL_MESSAGE(16, result.size, "zero buffer size calculation");
	TEST_ASSERT_EQUAL_MESSAGE('x', zero_buffer[0], "zero buffer unchanged");
}

/*------------------------------------------------------------------------------
 * TESTS FOR Arduino String custom formatter
 *----------------------------------------------------------------------------*/

void test_arduino_string_formatter()
{
	String arduinoStr = "Arduino";
	std::string result = fmt::format("Platform: {}", arduinoStr);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Platform: Arduino", result.c_str(), "Arduino String formatter");
	
	// Test with formatting options
	String shortStr = "Hi";
	char buffer[25] = {0}; // Increased buffer size to prevent overflow
	fmt::format_to(buffer, "Greeting: {:>10}", shortStr);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Greeting:         Hi", buffer, "Arduino String with alignment");
}

/*------------------------------------------------------------------------------
 * TESTS FOR specific scenarios
 *----------------------------------------------------------------------------*/

void test_sensor_data_formatting()
{
	// Simulate sensor readings
	float temperature = 23.44f; // Changed to avoid rounding edge case
	float humidity = 67.8f;
	int pressure = 1013;
	
	char buffer[60] = {0};
	fmt::format_to(buffer, "T:{:.1f}°C H:{:.0f}% P:{}hPa", 
				   temperature, humidity, pressure);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("T:23.4°C H:68% P:1013hPa", buffer, 
									"sensor data formatting");
}

void test_mac_address_formatting()
{
	// Simulate MAC address formatting
	uint8_t mac[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	
	std::string result = fmt::format("{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}",
									 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("AA:BB:CC:DD:EE:FF", result.c_str(), 
									"MAC address formatting");
}

void test_json_like_formatting()
{
	// Test JSON-like structure formatting
	const char* deviceName = "ESP32-DevKit";
	int deviceId = 42;
	bool isOnline = true;
	float voltage = 3.3f;
	
	std::string result = fmt::format("{{\"name\":\"{}\",\"id\":{},\"online\":{},\"voltage\":{:.1f}}}",
									 deviceName, deviceId, isOnline, voltage);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("{\"name\":\"ESP32-DevKit\",\"id\":42,\"online\":true,\"voltage\":3.3}",
									result.c_str(), "JSON-like formatting");
}

void test_hex_dump_formatting()
{
	// Test hex dump style formatting
	uint8_t data[4] = {0x01, 0x23, 0x45, 0x67};
	
	char buffer[25] = {0};
	fmt::format_to(buffer, "{:02x} {:02x} {:02x} {:02x}", 
				   data[0], data[1], data[2], data[3]);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("01 23 45 67", buffer, "hex dump formatting");
}

void test_timestamp_formatting()
{
	// Test timestamp formatting (simulating millis())
	uint32_t timestamp = 1234567;
	uint32_t seconds = timestamp / 1000;
	uint32_t milliseconds = timestamp % 1000;
	
	std::string result = fmt::format("Uptime: {}.{:03d}s", seconds, milliseconds);
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Uptime: 1234.567s", result.c_str(), "timestamp formatting");
}

/*------------------------------------------------------------------------------
 * SETUP AND TEST RUNNER
 *----------------------------------------------------------------------------*/

// set stuff up here
void setUp(void)
{
	// Any setup needed before each test
}

// clean stuff up here
void tearDown(void)
{
	// Any cleanup needed after each test
}

// tests here
void tests()
{
	// format_to tests
	RUN_TEST(test_format_to_basic_string);
	RUN_TEST(test_format_to_integers);
	RUN_TEST(test_format_to_hex);
	RUN_TEST(test_format_to_octal_binary);
	RUN_TEST(test_format_to_floats);
	RUN_TEST(test_format_to_alignment);
	RUN_TEST(test_format_to_zero_padding);
	RUN_TEST(test_format_to_scientific_notation);
	RUN_TEST(test_format_to_general_notation);
	RUN_TEST(test_format_to_scientific_edge_cases);

	// format_to_n tests
	RUN_TEST(test_format_to_n_basic);
	RUN_TEST(test_format_to_n_truncation);
	RUN_TEST(test_format_to_n_zero_size);

	// format tests
	RUN_TEST(test_format_basic_string);
	RUN_TEST(test_format_integers);
	RUN_TEST(test_format_floats);
	RUN_TEST(test_format_complex);

	// formatted_size tests
	RUN_TEST(test_formatted_size);
	RUN_TEST(test_formatted_size_complex);

	// Edge cases
	RUN_TEST(test_empty_format_string);
	RUN_TEST(test_no_arguments);
	RUN_TEST(test_unmatched_braces);
	RUN_TEST(test_nested_braces);
	RUN_TEST(test_zero_values);
	RUN_TEST(test_negative_values);
	RUN_TEST(test_large_numbers);
	RUN_TEST(test_small_numbers);
	RUN_TEST(test_special_characters);
	RUN_TEST(test_boolean_values);
	RUN_TEST(test_empty_strings);
	RUN_TEST(test_precision_edge_cases);
	RUN_TEST(test_width_edge_cases);
	RUN_TEST(test_mixed_types);
	RUN_TEST(test_repeated_placeholders);
	RUN_TEST(test_format_to_edge_cases);
	RUN_TEST(test_format_to_n_edge_cases);
	RUN_TEST(test_embedded_specific_edge_cases);
	RUN_TEST(test_memory_constrained_scenarios);

	// Arduino String formatter tests
	RUN_TEST(test_arduino_string_formatter);

	// Specific scenario tests
	RUN_TEST(test_sensor_data_formatting);
	RUN_TEST(test_mac_address_formatting);
	RUN_TEST(test_json_like_formatting);
	RUN_TEST(test_hex_dump_formatting);
	RUN_TEST(test_timestamp_formatting);
}

void setup()
{
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	delay(4000);

	UNITY_BEGIN();
	tests();
	UNITY_END();
}

void loop()
{
}
