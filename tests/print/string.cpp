#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTestExt/MockNamedValue.h>

#include "serialization/print.hpp"

TEST_GROUP(print_string_tests)
{ void setup() {}
  void teardown() {} };

TEST(print_string_tests, fake_test) {}

int main(int argc, char** argv)
{ return CommandLineTestRunner::RunAllTests(argc, argv); }
