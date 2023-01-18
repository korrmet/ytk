# Ytk #
toolkit for a small systems

# Idea #

Idea is simple: almost all embedded software required the software that provides functionelity like a boost or stl libraries. Sometimes (almost always) you can't use huge parts of this because there is no solutons to implement machine specific code of standard library or it's will be not effective. Many embedded coders avoid using large part of good code and reintvent the bicycle every time they start to code.

Ytk is just compilation of many useful tools and abstractions. These tools are parts of whole system so first you should mind how the system works.

# Approach #

Often when we implement complex behavior in embedded platforms we automatically use the multitasking and operating system. But also we need to make device fast and furious. This library provides superloop approach that can easily apply large applications with complex behavior as in the os-based projects, but with another tools and mindset.

## Features ##

* logically code is identical for any platform, so you can migrate between boards and MCUs easy

* board support package requirements are well documented and expected small footprint of this code

## Limitations ##

* to use whole library as base of your project be sure that the projectg is fully deterministic, because you can't load externl code

* there is no any hardware specific tools, you should write it yourself.

* when you use isolated parts of the library, mind that it isn't thread safe

# Licence #

Asshole public licence: if you like this code, just tell your buddies about it or you'll be an asshole.

Yes, it's the full text of the licence. Simple, right?

# Build #

# Testing #

To perform test the CppUTest package required.

# Warning #

This code is written in spare time, maybe it's not documented or tested properly, but I tried to make it usable and robust.
