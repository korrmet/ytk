/** \file serializer.cpp
 *  \details implementation of the serial converters toolset */

#include <cstdint>
#include <cstring>
#include "containers/arrayed_buffer.hpp"
#include "tools/serializer.hpp"
#include "core/errcode.hpp"

/** \brief memcpy with adjustable byte order
 *
 *  \param dst pointer to the destination buffer of data
 *  \param src pointer to the data source
 *  \param len length of the data to copy
 *  \param rev flag to reverse a byte order */
static void copy(void* dst, void* src, uint32_t len, bool rev = false)
{ uint8_t* s = (uint8_t*)src;
  uint8_t* d = (uint8_t*)dst;
  uint32_t s_count = 0;
  uint32_t d_count = (rev) ? len - 1 : 0;
  int step = (rev) ? -1 : 1;

  while (len) { d[d_count] = s[s_count]; s_count++; d_count += step; len--; } }

serializer::serializer(void* buffer, uint32_t buffer_size)
  : pos(0),
    errcode(ERR_OK),
    byte_order(false),
    buffer(buffer),
    buffer_size(buffer_size)
{}

serializer& serializer::hn()
{ byte_order = (byte_order) ? false : true;
  return *this; }

template <typename TYPE>
serializer& serializer::v(TYPE& val) { return a(&val, sizeof(TYPE)); }

template <typename TYPE>
serializer& serializer::v(TYPE* val) { return a(val, sizeof(TYPE)); }

serializer& serializer::a(void* buf, uint32_t len)
{ if (pos + len >= buffer_size)
  { if (errcode == ERR_OK) { errcode = ERR_BUFFER_OVERFLOW; }

    return *this; }

  copy((uint8_t*)buffer + pos, buf, len, byte_order);
  pos += len;
  return *this; }

serializer& serializer::s(const char* str, uint32_t len)
{ if (len != NO_LIMITS && pos + len >= buffer_size)
  { if (errcode == ERR_OK) { errcode = ERR_BUFFER_OVERFLOW; }

    return *this; }

  uint32_t counter = (len == NO_LIMITS) ? 0xFFFFFFFF : len;
  char* buf = (char*)buffer;

  while (*str && counter && pos < buffer_size)
  { *buf = *str;
    str++; buf++; pos++; }

  return *this; }

serializer& serializer::s(char* str, uint32_t len)
{ return s((char*)str, len); }

serializer& serializer::seek(int32_t step)
{ if (step > 0) { pos = (buffer_size - pos < step) ? buffer_size : pos + step; }
  else          { pos = (pos < -step) ? 0 : pos + step; }

  return *this; }

deserializer::deserializer(void* buffer, uint32_t buffer_size)
  : pos(0),
    errcode(ERR_OK),
    byte_order(false),
    buffer(buffer),
    buffer_size(buffer_size)
{}

deserializer& deserializer::hn()
{ byte_order = (byte_order) ? false : true;
  return *this; }

template <typename TYPE>
deserializer& deserializer::v(TYPE& val) { return a(&val, sizeof(TYPE)); }

template <typename TYPE>
deserializer& deserializer::v(TYPE* val) { return a(val, sizeof(TYPE)); }

deserializer& deserializer::a(void* buf, uint32_t len)
{ if (pos + len >= buffer_size)
  { if (errcode == ERR_OK) { errcode = ERR_BUFFER_OVERRUN; }

    return *this; }

  copy(buf, (uint8_t*)buffer + pos, len, byte_order);
  return *this; }

deserializer& deserializer::s(char* buf, uint32_t len)
{ char* str = (char*)buffer;
  uint32_t counter = (len == NO_LIMITS) ? 0xFFFFFFFF : len;

  while (*str && counter && pos < buffer_size)
  { *buf = *str;
    str++; buf++; pos++; }

  return *this; }

deserializer& deserializer::seek(int32_t step)
{ if (step > 0) { pos = (buffer_size - pos < step) ? buffer_size : pos + step; }
  else          { pos = (pos < -step) ? 0 : pos + step; }

  return *this; }
