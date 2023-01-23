/** \file  sysbus.hpp
 *  \brief interface of system bus */

#ifndef SYSBUS_HPP
#define SYSBUS_HPP

#include <cstdint>
#include "containers/automatic_list.hpp"

#ifndef SYSBUS_VOLUME
  #define SYSBUS_VOLUME 1024
#endif // SYSBUS_VOLUME

class i_sysbus_node : public automatic_list<i_sysbus_node>
{ public:
    uint16_t addr;

    virtual void handler(uint8_t* data,
                         uint8_t size,
                         uint16_t src,
                         bool rw,
                         bool rq) = 0;

    bool signal(uint8_t* data,
                uint8_t size,
                uint16_t dst,
                bool rw,
                bool rq); };

#endif // SYSBUS_HPP
