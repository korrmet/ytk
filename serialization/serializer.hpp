/** \file    serializer.hpp
 *  \brief   a toolset that can help to convert anything to sequence of bytes or
 *           sequence of bytes in everything
 *  \details main purpose of these tools is build parsers and generators that
 *           would work on almost every platform */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include "containers/arrayed_buffer.hpp"

#define NO_LIMITS 0

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

    /** \brief changes byte order (host to network or network to host) */
    serializer& hn();

    serializer& u8(uint8_t val);

    serializer& u16(uint16_t val);

    serializer& u32(uint32_t val);


    serializer& a(void* buf, uint32_t len);

    serializer& s(const char* str, uint32_t len = NO_LIMITS);
    serializer& s(char* std, uint32_t len = NO_LIMITS);

    /** \brief   pointer to function that perform data signification
     *  \details serializer provide piece of data that can be used without
     *           any limits, you can change any byte inside in this function,
     *           but you shouldn't take out the borders. you can place here
     *           routines to calculate crc and paste it in necessary point,
     *           or perform filling length field of protocol message, etc.
     *
     *  \param arg   user argument
     *  \param start pointer to the data array
     *  \param len   length of the data array
     *
     *  \return result of signification
     *  \retval true  data signed
     *  \retval false error occured, data may be corrupted */
    typedef bool (*significator_t)(void* arg, void* start, uint32_t len);
    serializer& sign(significator_t sign, void* arg);

    serializer& seek(int32_t step);

    uint8_t errcode;

  private:
    void* buffer;
    uint32_t buffer_size; };

class deserializer
{ public:
    /** \brief   pointer to validate function
     *  \details deserializer provide piece of data that you can chech any
     *           method you can think. there you can check data by crc or
     *           perform checks of counters field of the protocol message, etc.
     *
     *  \param arg   pointer to user argument
     *  \param start pointer to data array
     *  \param len   length of data array
     *
     *  \return result of validation
     *  \retval true  data is valid
     *  \retval false data is not valid */
    typedef bool (*validator_t)(void* arg, void* start, uint32_t len);

    deserializer& validate();

    deserializer& seek(int32_t step);
  private: };

#endif // SERIALIZER_HPP
