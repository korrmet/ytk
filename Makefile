CC = gcc
CXX = g++
INCLUDES += -I./

ifeq ($(DISTR), Full)
MODULES += kernel
MODULES += print
MODULES += scan
MODULES += shell
MODULES += crc
endif

OBJECTS = $(MODULES:=.o)

DEPS = $(shell find -name "*.d")
DEPFLAGS += -MMD

all: format check test ytk.a docs

ytk.a: $(OBJECTS)
	touch ytk.a

kernel.o:
	touch kernel.o

print.o:
	touch print.o

scan.o:
	touch scan.o

shell.o:
	touch shell.o

crc.o:
	touch crc.o

docs:
	@doxygen
	@cp logo_big.png docs/html

TEST_LIBS += -lCppUTest
TEST_LIBS += -lCppUTestExt

TEST_FLAG += -Wall
TEST_FLAG += -Werror
TEST_FLAG += -Dprivate=public
TEST_FLAG += -g3
TEST_FLAG += -ggdb

TEST_OPTS += -v
TEST_OPTS += -c

TESTS += tests/print/string.cpp.test
TESTS += tests/print/uint.cpp.test
TESTS += tests/containers/arrayed_buffer.cpp.test

.PHONY: clean format test

ifeq ($(FAILED_TEST), Enable)
.PRECIOUS: $(TESTS)
endif

test: clean $(TESTS)

tests/print/string.cpp.test: tests/print/string.cpp \
	                           serialization/print.cpp
	@g++ $? -o $@ $(INCLUDES) $(TEST_FLAG) $(TEST_LIBS) $(DEPFLAGS)
	@./$@ $(TEST_OPTS)

tests/print/uint.cpp.test: tests/print/uint.cpp \
	                         serialization/print.cpp
	@g++ $? -o $@ $(INCLUDES) $(TEST_FLAG) $(TEST_LIBS) $(DEPFLAGS)
	@./$@ $(TEST_OPTS)

tests/containers/arrayed_buffer.cpp.test: tests/containers/arrayed_buffer.cpp
	@g++ $? -o $@ $(INCLUDES) $(TEST_FLAG) $(TEST_LIBS) $(DEPFLAGS)
	@./$@ $(TEST_OPTS)

ASTYLE_FLAGS += --style=pico
ASTYLE_FLAGS += --indent=spaces=2
ASTYLE_FLAGS += --attach-extern-c
ASTYLE_FLAGS += --indent-classes
ASTYLE_FLAGS += --indent-modifiers
ASTYLE_FLAGS += --indent-switches
ASTYLE_FLAGS += --indent-cases
ASTYLE_FLAGS += --indent-namespaces
ASTYLE_FLAGS += --indent-preproc-block
ASTYLE_FLAGS += --indent-preproc-cond
ASTYLE_FLAGS += --indent-col1-comments
ASTYLE_FLAGS += --min-conditional-indent=0
ASTYLE_FLAGS += --break-blocks
ASTYLE_FLAGS += --pad-oper
ASTYLE_FLAGS += --pad-comma
ASTYLE_FLAGS += --pad-header
ASTYLE_FLAGS += --delete-empty-lines
ASTYLE_FLAGS += --align-pointer=type
ASTYLE_FLAGS += --align-reference=type
ASTYLE_FLAGS += --add-braces
ASTYLE_FLAGS += --attach-return-type
ASTYLE_FLAGS += --keep-one-line-blocks
ASTYLE_FLAGS += --keep-one-line-statements
ASTYLE_FLAGS += --convert-tabs
ASTYLE_FLAGS += --max-code-length=80
ASTYLE_FLAGS += --break-after-logical
ASTYLE_FLAGS += --lineend=linux

ASTYLE_SRCS += $(shell find -name "*.cpp")
ASTYLE_SRCS += $(shell find -name "*.hpp")
ASTYLE_SRCS += $(shell find -name "*.h")
ASTYLE_SRCS += $(shell find -name "*.c")

format:
	@astyle $(ASTYLE_FLAGS) $(ASTYLE_SRCS)
	@rm -rf $(shell find -name "*.orig")

CHECK_FLAGS += --enable=all
CHECK_FLAGS += --inconclusive
CHECK_FLAGS += --std=c++17
CHECK_FLAGS += --report-progress
CHECK_FLAGS += --suppress=missingIncludeSystem
CHECK_FLAGS += --suppress=cstyleCast
ifeq ($(BUGHUNT), Enable)
CHECK_FLAGS += --bug-hunting
endif

CHECK_FLAGS += --force
CHECK_SRCS = $(ASTYLE_SRCS)

check:
	@cppcheck $(CHECK_FLAGS) $(INCLUDES) $(CHECK_SRCS)

clean:
	@rm -rf ytk.a 
	@rm -rf docs 
	@rm -rf $(shell find -name "*.test")
	@rm -rf $(shell find -name "*.o")
	@rm -rf $(shell find -name "*.d")

-include $(DEPS)
