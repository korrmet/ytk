/** \file  sysbus.hpp
 *  \brief interface of system bus */

#ifndef SYSBUS_HPP
#define SYSBUS_HPP

#include <cstdint>
#include "containers/automatic_list.hpp"

class i_sysbus_node : public automatic_list<i_sysbus_node>
{ public:
    /** \brief address of the current node */
    uint8_t addr;

    /** \brief   handler of the requests to the current node
     *  \details you should implement it in your own node
     *
     *  \param data pointer to the data of the input message
     *  \param size size of the input message
     *  \param src  address of the sender */
    virtual void handler(uint8_t* data, uint8_t size, uint16_t src) = 0;

    /** \brief   send message to the system bus
     *  \details first loopback would be scanned for recepients and if there
     *           is no any recepient it would be sent to the bus
     *
     *  \param data pointer to the data that should be sent
     *  \param size size of the data that should be sent
     *  \param dst  destination node on the bus
     *  \param ttl  time to live of the message */
    void signal(uint8_t* data, uint8_t size, uint8_t dst, uint8_t ttl); };

#endif // SYSBUS_HPP
