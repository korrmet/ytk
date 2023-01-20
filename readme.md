![](./docs/logo_big.png "toolkit for a small systems")

# Idea #

Idea is simple: almost all embedded software required the software that provides functionelity like a boost or stl libraries. Sometimes (almost always) you can't use huge parts of this because there is no solutons to implement machine specific code of standard library or it's will be not effective. Many embedded coders avoid using large part of good code and reintvent the bicycle every time they start to code.

There is no any extra features, just unificated set of tools that combine everyday routines.

# Approach #

Often when we implement complex behavior in embedded platforms we automatically use the multitasking and operating system. But also we need to make device fast and furious. This library provides superloop approach that can easily apply large applications with complex behavior as in the os-based projects, but with another tools and mindset. This behaviour is tightly coupled with state machines and manual control of execution time.

Another key concept is modularity. Tiny code blocks managed by state machines may be gathered in modules. Modules can interact multiple ways. Interaction is focused on pipeline architecture. It's pretty simple and applicable for many embedded projects. Also modules can exchange simple messages that called signals.

I have seen many projects with common problem: initialization chaos. Ytk has initialization subsystem that includes dependencies and semi-parallel execution. You can easily make dependency graphs and initialization system guarantee the order of execution of procedures. As this system is not fast there is the way to make manual initialization routine.

## Features ##

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

# Packaging #

![](./docs/library_structure.png "Packaging")

Library consists of core, container, io, tools and board support packages. Some component are independent but most of them tightly coupled together. Almost all of them depend on BSP interface. If you want use isolated components like containers you still should imlpement BSP calls.

## Core ##

## Containers ##

## IO ##

## Tools ##

## BSP ##
