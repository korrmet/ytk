#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "serialization/print.hpp"
#include "common/errcode.hpp"
#include "bsp/bsp.h"

void bsp_tx_char(char ch) {}

TEST_GROUP(print_uint_tests)
{ void setup() {}
  void teardown() {} };

TEST(print_uint_tests, simple_print)
{ char buffer[10] = { 0 };
  print p(buffer, sizeof(buffer));
  p.u(123);
  char expected[10] = { '1', '2', '3', 0, 0, 0, 0, 0, 0, 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(p.counter == 3);
  CHECK(p.errcode == ERR_OK); }

TEST(print_uint_tests, maximum_value)
{ char buffer[11] = { 0 };
  print p(buffer, sizeof(buffer));
  p.u(0xFFFFFFFF);
  char expected[11] = { '4', '2', '9', '4', '9', '6', '7', '2', '9', '5', 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(p.counter == 10);
  CHECK(p.errcode == ERR_OK); }

TEST(print_uint_tests, maximum_value_separated)
{ char buffer[14] = { 0 };
  print p(buffer, sizeof(buffer));
  p.u(0xFFFFFFFF, PRINT_NO_LIMITS, 3);
  char expected[14] =
  { '4', ' ', '2', '9', '4', ' ', '9', '6', '7', ' ', '2', '9', '5', 0 };
  MEMCMP_EQUAL(expected, buffer, sizeof(buffer));
  CHECK(p.counter == 13);
  CHECK(p.errcode == ERR_OK); }

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
