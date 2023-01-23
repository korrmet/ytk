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

    /** \brief add uint8_t to sequence
     *
     *  \param val value to be added
     *
     *  \return reference to the current serializer object */
    serializer& u8(uint8_t val);

    /** \brief add uint16_t to sequence
     *
     *  \parm val value to be added
     *
     *  \return reference to the current serializer object */
    serializer& u16(uint16_t val);

    /** \brief add uint32_t to sequence
     *
     *  \param val value to be added
     *
     *  \return reference to the current serializer object */
    serializer& u32(uint32_t val);

    /** \brief add array to the sequence
     *
     *  \param buf pointer to the buffer that should be added
     *  \param len size of the buffer
     *
     *  \return reference to the current serializer object */
    serializer& a(void* buf, uint32_t len);

    /** \brief add c-string to the sequence
     *
     *  \param str pointer to the null-terminated string literal
     *  \param len maximum size of the string
     *
     *  \return reference to the current serializer object */
    serializer& s(const char* str, uint32_t len = NO_LIMITS);

    /** \brief add c-string to the sequence
     *
     *  \param str pointer to the string buffer
     *  \param len maximum size of the string
     *
     *  \return reference to the current serializer object */
    serializer& s(char* str, uint32_t len = NO_LIMITS);

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

    /** \brief make sign of the sequence
     *
     *  \param sign pointer to significator function
     *  \param arg  user argument that will be passed into significator
     *
     *  \return reference to the current serializer object */
    serializer& sign(significator_t sign, void* arg);

    /** \brief move through the sequence forwards or backwards
     *
     *  \param step number and direction of steps according the current point
     *
     *  \return reference to the current serializer object */
    serializer& seek(int32_t step);

    /** \brief insert single bit
     *
     *  \param bit bit value
     *
     *  \return reference to the current serializer object */
    serializer& b(bool bit);

    /** \brief insert set of bits less or equal one bit
     *
     *  \param bitfield set of bits
     *  \param size     length of the set of bits
     *
     *  \return reference to the current serializer object */
    serializer& bf(uint8_t bitfield, uint8_t size);

    /** \brief last error code */
    uint8_t errcode;

  private:
    /** \brief pointer to the external buffer where the serial data would be
     *         placed */
    void* buffer;

    /** \brief size of the external buffer */
    uint32_t buffer_size;

    /** \brief current bit */
    uint8_t bit_count; };

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
