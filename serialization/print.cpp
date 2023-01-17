/** \file print.cpp
 *  \brief implementation of better printf or cout replacement  */

#include <cstdint>
#include "serialization/print.hpp"
#include "bsp/bsp.h"

print::print() : buffer(nullptr), size(0), counter(0), errcode(0) { }

print::print(uint8_t* buffer, uint32_t size)
  : buffer(buffer),
    size(size),
    counter(0),
    errcode(0)
{ }

print& print::operator()(const char* str,
                         uint32_t len,
                         uint8_t align,
                         char spc)
{ print_string((char*)str, len, align, spc);
  return *this; }

print& print::operator()(char* str,
                         uint32_t len,
                         uint8_t align,
                         char spc)
{ print_string((char*)str, len, align, spc);
  return *this; }

print& print::s(const char* str,
                uint32_t len,
                uint8_t align,
                char spc)
{ print_string((char*)str, len, align, spc);
  return *this; }

print& print::s(char* str,
                uint32_t len,
                uint8_t align,
                char spc)
{ print_string((char*)str, len, align, spc);
  return *this; }

void print::print_string(char* str,
                         uint32_t len,
                         uint8_t align,
                         char spc)
{ uint32_t actual_len = 0;

  char* _str = str;
  while (*_str) { actual_len++; str++; }

  if (actual_len > len)
  {
  }

  uint32_t space = len - actual_len;
  uint32_t space_before = 0;

  switch (align)
  { case ALIGN_RIGHT:  space_before = space;     break;
    case ALIGN_CENTER: space_before = space / 2; break;
    // ALIGN_LEFT, it's no require any spaces before string
    default:                                     break; }
 
  for (uint32_t i = 0; i < space_before; i++) { tx(spc); } 
  
  for (uint32_t i = 0; i < actual_len; i++) { tx(str[i]); }

  for (uint32_t i = 0; i < actual_len - space_before; i++) { tx(spc); } }

