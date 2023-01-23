/** \file  sysbus.cpp
 *  \brief system bus implementation */

#include <cstdint>
#include "bsp/bsp.h"
#include "containers/arrayed_buffer.hpp"
#include "core/sysbus.hpp"
#include "tools/serializer.hpp"
#include "core/errcode.hpp"

#define MAX_SIZE    64
#define HEADER_SIZE  5
#define CKSUM_SIZE   2

/** \todo incomplete */
static bool sign_crc(void* arg, void* start, uint32_t len)
{ return false; }

static void tx(void* arg, uint8_t byte) { bsp_sysbus_tx(byte); }

class sysbus_root
{ public:
    uint16_t dst;
    uint16_t src;
    uint8_t len;
    bool rw;
    bool rq;

    void input(uint8_t byte)
    { if (!rx_buffer.push_back(byte))
      { rx_buffer.shift_left(1);
        rx_buffer.push_back(byte); }

      // try deserialize
    }

    bool poll_locals()
    { i_sysbus_node* nodes = automatic_list<i_sysbus_node>::root;

      while (nodes)
      { if (nodes->addr == dst)
        { nodes->handler(&rx_buffer.mem[HEADER_SIZE], len, src, rw, rq);
          return true; }

        nodes = nodes->next; }

      return false; }

    void retranslate()
    { uint8_t current_byte = 0;

      while (rx_buffer.fetch_back(current_byte))
      { rx_buffer.pop_back();
        bsp_sysbus_tx(current_byte); } }

    void send(void* data, uint8_t size)
    { serializer serial(tx, nullptr);
      serial.u8(dst);
      serial.u8(src);
      serial.bf(size, 6);
      serial.b(rw);
      serial.b(rq);
      serial.a(data, size);
      serial.sign(sign_crc, nullptr); }

  private:
    arrayed_buffer < uint8_t, MAX_SIZE + HEADER_SIZE + CKSUM_SIZE > rx_buffer;

} sb_root;

void bsp_sysbus_rx_cb(uint8_t byte) { sb_root.input(byte); }

static uint8_t tx_buffer[MAX_SIZE + HEADER_SIZE];

bool i_sysbus_node::signal(uint8_t* data,
                           uint8_t size,
                           uint16_t dst,
                           bool rw,
                           bool rq)
{ if (!data) { return false; }

  if (!size) { return false; }

  if (size > MAX_SIZE) { return false; }

  sb_root.len = size;
  sb_root.src = addr;
  sb_root.dst = dst;
  sb_root.rw = rw;
  sb_root.rq = rq;

  if (sb_root.poll_locals()) { return true; }

  sb_root.retranslate();
  return true; }
