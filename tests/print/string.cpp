#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTest/UtestMacros.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTestExt/MockNamedValue.h>

#include <cstring>
#include "bsp/bsp.h"
#include "serialization/print.hpp"

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

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
