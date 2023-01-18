/** \file print.cpp
 *  \brief implementation of better printf or cout replacement  */

#include <cstdint>
#include "common/errcode.hpp"
#include "serialization/print.hpp"
#include "bsp/bsp.h"

print::print() : errcode(ERR_OK), buffer(nullptr), size(0), counter(0) { }

print::print(char* buffer, uint32_t size)
  : errcode(ERR_OK),
    buffer(buffer),
    size(size),
    counter(0)
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

  while (*_str) { actual_len++; _str++; }

  uint32_t space = 0;
  bool make_brackets = false;

  if (len)
  { space = len - actual_len;

    if (actual_len > len)
    { actual_len = len - 2;
      space = 0;
      make_brackets = true; } }

  uint32_t space_before = 0;

  switch (align)
  { case ALIGN_RIGHT:  space_before = space;     break;

    case ALIGN_CENTER: space_before = space / 2; break;

    // ALIGN_LEFT, it's no require any spaces before string
    default:                                     break; }

  if (make_brackets) { tx('['); }

  for (uint32_t i = 0; i < space_before; i++) { tx(spc); }

  for (uint32_t i = 0; i < actual_len; i++) { tx(str[i]); }

  for (uint32_t i = 0; i < space - space_before; i++) { tx(spc); }

  if (make_brackets) { tx(']'); } }

void print::tx(char ch)
{ if (!buffer) { bsp_tx_char(ch); }
  else if (counter < size) { buffer[counter] = ch; counter++; }
  else { errcode = ERR_BUFFER_OVERFLOW; } }
