#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include <cstdint>
#include <cstring>
#include "containers/arrayed_buffer.hpp"

TEST_GROUP(arrayed_buffer_tests)
{ void setup() {}
  void teardown() {} };

TEST(arrayed_buffer_tests, push_front)
{ arrayed_buffer<uint8_t, 10> buf;
  memset(buf.mem, 0, sizeof(buf.mem));
  
  for (uint32_t i = 0; i < sizeof(buf.mem); i++)
  { CHECK(buf.push_front(i)); }

  uint8_t expected[sizeof(buf.mem)] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  MEMCMP_EQUAL(expected, buf.mem, sizeof(buf.mem)); }

TEST(arrayed_buffer_tests, push_back)
{ arrayed_buffer<uint8_t, 10> buf;
  memset(buf.mem, 0, sizeof(buf.mem));

  for (uint32_t i = 0; i < sizeof(buf.mem); i++)
  { CHECK(buf.push_back(i)); }

  uint8_t expected[sizeof(buf.mem)] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  MEMCMP_EQUAL(expected, buf.mem, sizeof(buf.mem)); }

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
