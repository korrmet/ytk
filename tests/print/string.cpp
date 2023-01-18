#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include <cstring>
#include "bsp/bsp.h"
#include "serialization/print.hpp"
#include "common/errcode.hpp"

#include <iostream>
char output_buffer[80] = { 0 };
unsigned int counter = 0;

void reset()
{ memset(output_buffer, 0, sizeof(output_buffer));
  counter = 0; }

void bsp_tx_char(char ch)
{ if (counter >= 80) { return; }

  output_buffer[counter] = ch;
  counter++; }

TEST_GROUP(print_string_tests)
{ void setup() { reset(); }
  void teardown() {} };

TEST(print_string_tests, print_no_limits)
{ print().print_string((char*)"123", PRINT_NO_LIMITS, STD_ALIGN, STD_SPACER);
  MEMCMP_EQUAL("123", output_buffer, sizeof("123")); }

TEST(print_string_tests, print_with_left_alignment)
{ print().print_string((char*)"123", 6, ALIGN_LEFT, STD_SPACER);
  MEMCMP_EQUAL("123   ", output_buffer, sizeof("123   ")); }

TEST(print_string_tests, print_with_right_alignment)
{ print().print_string((char*)"123", 6, ALIGN_RIGHT, STD_SPACER);
  MEMCMP_EQUAL("   123", output_buffer, sizeof("   123")); }

TEST(print_string_tests, print_with_center_alignment)
{ print().print_string((char*)"123", 6, ALIGN_CENTER, STD_SPACER);
  MEMCMP_EQUAL(" 123  ", output_buffer, sizeof(" 123  ")); }

TEST(print_string_tests, print_limited)
{ print().print_string((char*)"123456", 4, STD_ALIGN, STD_SPACER);
  MEMCMP_EQUAL("[12]", output_buffer, sizeof("[12]")); }

TEST(print_string_tests, print_with_left_alignment_spacer)
{ print().print_string((char*)"123", 6, ALIGN_LEFT, '_');
  MEMCMP_EQUAL("123___", output_buffer, sizeof("123___")); }

TEST(print_string_tests, print_with_right_alignment_spacer)
{ print().print_string((char*)"123", 6, ALIGN_RIGHT, '_');
  MEMCMP_EQUAL("___123", output_buffer, sizeof("___123")); }

TEST(print_string_tests, print_with_center_alignment_spacer)
{ print().print_string((char*)"123", 6, ALIGN_CENTER, '_');
  MEMCMP_EQUAL("_123__", output_buffer, sizeof("_123__")); }

TEST(print_string_tests, print_no_limits_in_buffer)
{ char buffer[10] = { 0 };
  print p(buffer, sizeof(buffer));
  p.print_string((char*)"123", PRINT_NO_LIMITS, STD_ALIGN, STD_SPACER);
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(p.counter == 3);
  CHECK(p.errcode == ERR_OK); }

TEST(print_string_tests, print_no_limits_in_buffer_overflow)
{ char buffer[5] = { 0 };
  print p(buffer, sizeof(buffer));
  p.print_string((char*)"123456", PRINT_NO_LIMITS, STD_ALIGN, STD_SPACER);
  char expected[5] = { '1', '2', '3', '4', '5' };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(p.counter == 5);
  CHECK(p.errcode == ERR_BUFFER_OVERFLOW); }

TEST(print_string_tests, print_no_limits_in_buffer_wrapped)
{ char buffer[10] = { 0 };
  print(buffer, sizeof(buffer))("123");
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

TEST(print_string_tests, print_no_limits_in_buffer_wrapped_explicit)
{ char buffer[10] = { 0 };
  print(buffer, sizeof(buffer)).s("123");
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

TEST(print_string_tests, print_no_limits_in_buffer_wrapped_non_const)
{ char buffer[10] = { 0 };
  char source[4] = { '1', '2', '3', 0 };
  print(buffer, sizeof(buffer))(source);
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

TEST(print_string_tests, print_no_limits_in_buffer_wrapped_explicit_non_const)
{ char buffer[10] = { 0 };
  char source[4] = { '1', '2', '3', 0 };
  print(buffer, sizeof(buffer)).s(source);
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer)); }

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
