CC = gcc
CXX = g++

docs:
	doxygen

test:

.PHONY: clean format

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

ASTYLE_SRCS += $(shell find . -name "*.cpp")
ASTYLE_SRCS += $(shell find . -name "*.hpp")
ASTYLE_SRCS += $(shell find . -name "*.h")
ASTYLE_SRCS += $(shell find . -name "*.c")

format:
	@astyle $(ASTYLE_FLAGS) $(ASTYLE_SRCS)
	@rm -rf $(shell find . -name "*.orig")

clean:
	@rm -rf docs
