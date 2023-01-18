/** \file print.cpp
 *  \brief implementation of better printf or cout replacement  */

#include <cstdint>
#include <cstring>
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

/** \brief   table of 10 power
 *  \details as this printing methow 32-only bit maximum used power is 9 */
static uint32_t pow10[10] =
{ /*  0 */ 1,
  /*  1 */ 10,
  /*  2 */ 100,
  /*  3 */ 1000,
  /*  4 */ 10000,
  /*  5 */ 100000,
  /*  6 */ 1000000,
  /*  7 */ 10000000,
  /*  8 */ 100000000,
  /*  9 */ 1000000000 };

/** \brief table for integer to char transform, uppercase variant */
static char asciitab_uppercase[16] =
{ '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

// TODO: uncomment to implement x()
// /** \brief table for integer to char transform, lowercase variant */
// static char asciitab_lowercase[16] =
// { '0', '1', '2', '3', '4', '5', '6', '7',
//   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

print& print::u(uint32_t uint,
                uint32_t len,
                uint8_t separate_num,
                uint8_t align,
                char spc)
{ uint32_t rest = uint;
  uint8_t digit_counter = 0;
  uint8_t current_digit = 0;
  char temp[9 + 9] = { 0 };
  bool first_significant_arrived = false;

  for (uint8_t i = 9; i <= 9; i--)
  { current_digit = rest / pow10[i];
    rest -= current_digit * pow10[i];

    if (current_digit) { first_significant_arrived = true; }

    if (!current_digit && !first_significant_arrived) { continue; }

    temp[digit_counter] = asciitab_uppercase[current_digit];
    digit_counter++; }

  // insert separators
  uint32_t actual_len = digit_counter;

  if (separate_num && separate_num < digit_counter)
  { uint32_t current_pos = digit_counter;

    for (uint32_t i = 0; i < digit_counter; i++)
    { if (i && (i % separate_num == 0))
      { memcpy(&temp[current_pos + 1],
               &temp[current_pos],
               actual_len - current_pos);
        temp[current_pos] = ' ';
        actual_len++; }

      current_pos--; } }

  s(temp, len, align, spc);
  return *this; }

void print::tx(char ch)
{ if (!buffer) { bsp_tx_char(ch); }
  else if (counter < size) { buffer[counter] = ch; counter++; }
  else { errcode = ERR_BUFFER_OVERFLOW; } }
