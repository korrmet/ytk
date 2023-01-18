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

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
