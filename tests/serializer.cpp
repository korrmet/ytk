#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "tools/serializer.hpp"
#include "core/errcode.hpp"
#include <cstdint>

TEST_GROUP(serializer_unit_tests)
{ void setup() {}
  void teardown() {} };

TEST(serializer_unit_tests, serialize_char)
{ char buffer[10] = { 0 };
  serializer s(buffer, sizeof(buffer));
  s.v<char>('a').v<char>('b').v<char>('c').v<char>('d').v<char>('e')
  .v<char>('f').v<char>('g').v<char>('h').v<char>('i').v<char>('j');
  char expected[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
  CHECK(s.pos == 10);
  CHECK(s.errcode == ERR_OK);
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

TEST(serializer_unit_tests, deserialize_char)
{ char buffer[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
  deserializer ds(buffer, sizeof(buffer));
  char a = 0;
  char b = 0;
  char c = 0;
  char d = 0;
  char e = 0;
  char f = 0;
  char g = 0;
  char h = 0;
  char i = 0;
  char j = 0;
  ds.v<char>(a).v<char>(b).v<char>(c).v<char>(d).v<char>(e)
  .v<char>(f).v<char>(g).v<char>(h).v<char>(i).v<char>(j);
  CHECK(a == 'a');
  CHECK(b == 'b');
  CHECK(c == 'c');
  CHECK(d == 'd');
  CHECK(e == 'e');
  CHECK(f == 'f');
  CHECK(g == 'g');
  CHECK(h == 'h');
  CHECK(i == 'i');
  CHECK(j == 'j');
  CHECK(ds.pos == 10);
  CHECK(ds.errcode == ERR_OK); }

TEST(serializer_unit_tests, serializer_hn_switch)
{ uint8_t buffer[8] = { 0 };
  serializer s(buffer, sizeof(buffer));
  uint32_t number = 0x12345678;
  s.v<uint32_t>(number).hn().v<uint32_t>(number);
  uint8_t expected[8] = { 0x78, 0x56, 0x34, 0x12, 0x12, 0x34, 0x56, 0x78 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(s.pos == 8);
  CHECK(s.errcode == ERR_OK); }

TEST(serializer_unit_tests, deserializer_hn_switch)
{ uint8_t buffer[8] = { 0x78, 0x56, 0x34, 0x12, 0x12, 0x34, 0x56, 0x78 };
  deserializer ds(buffer, sizeof(buffer));
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  ds.v<uint32_t>(number1).hn().v<uint32_t>(number2);
  CHECK(ds.pos == 8);
  CHECK(ds.errcode == ERR_OK);
  CHECK(number1 == 0x12345678);
  CHECK(number2 == 0x12345678); }

TEST(serializer_unit_tests, serializer_string_no_limits_normal)
{ char buffer[5] = { 0 };
  serializer s(buffer, sizeof(buffer));
  s.s("abcd");
  CHECK(s.pos == 5);
  CHECK(s.errcode == ERR_OK);
  char expected[5] = { 'a', 'b', 'c', 'd', 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

TEST(serializer_unit_tests, serializer_string_limited)
{ char buffer[5] = { 0 };
  serializer s(buffer, sizeof(buffer));
  s.s("abcd", 3);
  CHECK(s.pos == 4);
  CHECK(s.errcode == ERR_OK);
  char expected[5] = { 'a', 'b', 'c', 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

IGNORE_TEST(serializer_unit_tests, serializer_string_overflow)
{ char buffer[5] = { 0 };
  serializer s(buffer, sizeof(buffer));
  s.s("abcdefg", 8);
  CHECK(s.pos == 5);
  CHECK(s.errcode == ERR_BUFFER_OVERFLOW);
  char expected[5] = { 'a', 'b', 'c', 'd', 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
