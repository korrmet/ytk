/** \file  sysbus.cpp
 *  \brief system bus implementation */

#include <cstdint>
#include "bsp/bsp.h"
#include "containers/arrayed_buffer.hpp"
#include "containers/automatic_list.hpp"
#include "core/sysbus.hpp"
#include "tools/serializer.hpp"
#include "core/errcode.hpp"

/** \brief maximum length of the message */
#define MESSAGE_SIZE 19

/** \brief   transmit function for the system bus
 *  \details adapter for bsp function
 *
 *  \param arg  not used
 *  \param byte byte to send on a system bus */
static void sysbus_tx(void* arg, uint8_t byte) { bsp_sysbus_tx(byte); }

/** \brief significator for system bus protocol
 *
 *  \param arg   not used
 *  \param start start of the message to sign
 *  \param len   length of the message */
bool sysbus_sign(void* arg, void* start, uint32_t len) { return true; }

/** \brief retranslate message to external bus
 *  
 *  \param data pointer to the data that should be sent
 *  \param size size of the data that should be sent
 *  \param src  source node on the bus
 *  \param dst  destination node on the bus
 *  \param ttl  time to live of the message */
static void retranslate(uint8_t* data,
                        uint8_t size,
                        uint8_t src,
                        uint8_t dst,
                        uint8_t ttl)
{ if (!data) { return; }

  if (size > 15) { return; }

  uint8_t tx_mess[MESSAGE_SIZE];
  serializer send_stream(tx_mess, sizeof(tx_mess));
  send_stream
  .u8(dst).u8(src).bf(size, 4).bf(ttl, 4).a(data, size).sign(sysbus_sign);

  for (uint32_t i = 0; i < send_stream.pos; i++)
  { bsp_sysbus_tx(tx_mess[i]); } }

/** \brief   sends message
 *  \details firt loopback would be shanned for recepients and if there
 *           is no any recepient it would be sent to the bus
 *
 *  \param data pointer to the data that should be sent
 *  \param size size of the data that should be sent
 *  \param src  source node on the bus
 *  \param dst  destination node on the bus
 *  \param ttl  time to live of the message */
static void send_signal(uint8_t* data,
                        uint8_t size,
                        uint8_t src,
                        uint8_t dst,
                        uint8_t ttl)
{ if (!data) { return; }

  if (size > 15) { return; }

  if (!ttl) { return; }

  i_sysbus_node* loopback = automatic_list<i_sysbus_node>::root;

  while (loopback)
  { if (loopback->addr == dst)
    { loopback->handler(data, size, src);
      return; }

    loopback = loopback->next; }

  retranslate(data, size, src, dst, ttl - 1); }

/** \brief implementation of bsp sysbus callback
 *
 *  \param byte received byte */
void bsp_sysbus_rx_cb(uint8_t byte)
{ static uint8_t rx_message[MESSAGE_SIZE];
  static deserializer input_stream(rx_message, sizeof(rx_message));
  input_stream.put(&byte, 1);

  if (input_stream.validate())
  { uint8_t src = 0;
    uint8_t dst = 0;
    uint8_t ttl = 0;
    uint8_t size = 0;
    uint8_t* data = nullptr;
    input_stream.pos = 0;
    input_stream.u8(dst).u8(src).bf(size, 4).bf(ttl, 4);
    data = &rx_message[input_stream.pos];
    send_signal(data, size, src, dst, ttl); } }

void i_sysbus_node::signal(uint8_t* data,
                           uint8_t size,
                           uint8_t dst,
                           uint8_t ttl)
{ send_signal(data, size, addr, dst, ttl); }
