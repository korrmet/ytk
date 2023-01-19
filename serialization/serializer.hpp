/** \file    serializer.hpp
 *  \brief   a toolset that can help to convert anything to sequence of bytes or
 *           sequence of bytes in everything
 *  \details main purpose of these tools is build parsers and generators that
 *           would work on almost every platform */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include "containers/arrayed_buffer.hpp"

class serializer
{ public:
    /** \brief pointer to the function to transmit a single byte
     *
     *  \param arg  user argument
     *  \param byte byte to transmit */
    typedef void (*tx_func_t)(void* arg, uint8_t byte);

    /** \brief constructor for buffered output variant
     *
     *  \param buffer      pointer to buffer to store sequence
     *  \param buffer_size size of buffer */
    serializer(void* buffer, uint32_t buffer_size);

    /** \brief constructor for callback variant
     *
     *  \param tx  pointer to function that will call when serializer will
     *             be ready
     *  \param arg value of the user argument that will be passed to tx
     *             function */
    serializer(tx_func_t tx, void* arg);

  private:
    void* buffer;
    uint32_t buffer_size; };

class deserializer
{ public:
  private: };

#endif // SERIALIZER_HPP
