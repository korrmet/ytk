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

/** \brief a tool to make data series generator
 *  \todo think about how to perform signification and transmission of messages
 *        using tx function. seems to be the buffer is always needed
 *        may be it should be used with single-step crc every byte operation
 *  \todo serializer shall return the length of signed field */
class serializer
{ public:
    /** \brief constructor for buffered output variant
     *
     *  \param buffer      pointer to buffer to store sequence
     *  \param buffer_size size of buffer */
    serializer(void* buffer, uint32_t buffer_size);

    /** \brief pointer to the function to transmit a single byte
     *
     *  \param arg  user argument
     *  \param byte byte to transmit */
    typedef void (*tx_func_t)(void* arg, uint8_t byte);

    /** \brief pointer to the function to transmit a single byte */
    tx_func_t tx_func;

    /** \brief user argument value to transmit function */
    void* tx_func_arg;

    /** \brief constructor for callback variant
     *
     *  \param tx  pointer to function that will call when serializer will
     *             be ready
     *  \param arg value of the user argument that will be passed to tx
     *             function */
    serializer(tx_func_t tx, void* arg = nullptr);

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

    /** \brief pointer to function that perform data signification */
    significator_t significator;

    /** \brief user argument value to the significator function */
    void* significator_arg;

    /** \brief make sign of the sequence
     *
     *  \return reference to the current serializer object */
    serializer& sign(significator_t sign, void* arg = nullptr);

    /** \brief changes byte order (host to network or network to host)
     *
     *  \return reference to the current serializer object */
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

    /** \brief move through the sequence forwards or backwards
     *
     *  \param step number and direction of steps according the current point
     *
     *  \return reference to the current serializer object */
    serializer& seek(int32_t step);

    /** \brief invokes a transmit function call
     *
     *  \return reference to the current serializer object */
    serializer& tx();

    /** \brief last error code */
    uint8_t errcode;

    /** \brief current position in the buffer */
    uint32_t pos;

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
    /** \brief constructor for buffered input variant
     *
     *  \param buffer      pointer to the buffer to store a sequence
     *  \param buffer_size size of the buffer */
    deserializer(void* buffer, uint32_t buffer_size);

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

    validator_t validator;

    void* validator_arg;

    /** \brief   pointer to validated data event callback
     *
     *  \param arg pointer to the user argument */
    typedef void (*validated_callback_t)(void* arg);

    validated_callback_t validated_callback;

    void* validated_callback_arg;

    /** \brief   checks if data inside valid
     *  \details force validator call
     *
     *  \return result of the check
     *  \retval true  data is valid
     *  \retval false data is invalid */
    bool validate();

    /** \brief input of the deserializer
     *
     *  \param data pointer to the data that should be added to deserializer
     *  \param size size of the data
     *
     *  \return size of actually inserted data */
    uint32_t put(void* data, uint32_t size);

    /** \brief changes byte order (host to network or network to host
     *
     *  \return reference to the current deserializer object */
    deserializer& hn();

    /** \brief extracts uint8_t from the sequence
     *
     *  \param val reference to the buffer for value
     *
     *  \return reference to the current deserializer object */
    deserializer& u8(uint8_t& val);

    /** \brief extracts uint16_t from the sequence
     *
     *  \param val reference to the buffer for the value
     *
     *  \return reference to the current deserializer object */
    deserializer& u16(uint16_t& val);

    /** \brief extracts uint32_t from the sequence
     *
     *  \param val referenc to the buffer for the value
     *
     *  \return reference to the current deserializer object */
    deserializer& u32(uint32_t& val);

    /** \brief extracts array from the sequence
     *  \warning there is no any check for buffer size, I hope you can deal
     *           with it
     *
     *  \param buf pointer to the buffer for array
     *  \param len size of array in the sequence
     *
     *  \return reference to the current deserializer object */
    deserializer& a(void* buf, uint32_t len);

    /** \brief extracts string from the sequence
     *  \warning there is no any chek for the buffer size, I hope you can deal
     *           with it
     *
     *  \param buf pointer to the bufer for the string
     *  \param len size of the string in the sequence
     *
     *  \return reference to the curren deserializer object */
    deserializer& s(char* buf, uint32_t len = NO_LIMITS);

    /** \brief extracts a single bit from the sequence
     *
     *  \param bit pointer to the buffer for the bit in the sequence
     *
     *  \return reference to the current deserializer object */
    deserializer& b(bool& bit);

    /** \brief extracts a bitfield from the sequence
     *  \details bitfield count will be reset after calling non-bit method
     *  \details maximum length of bitfield is 8 bits
     *  \details bitfield can belong to two bytes
     *
     *  \param bitfield reference to the buffer for bitfield
     *  \param size     size of bitfield in bits
     *
     *  \return reference to the current deserializer object */
    deserializer& bf(uint8_t& bitfield, uint8_t size);

    /** \brief move through the sequence forwards of backwards
     *
     *  \param step number and direction of steps according the current point
     *
     *  \return reference to the current serializer object */
    deserializer& seek(int32_t step);

    /** \brief current position inside the buffer */
    uint32_t pos;

    /** \brief last error code */
    uint8_t errcode;
  private:
    /** \brief pointer to the external buffer where the sequence is placed */
    void* buffer;

    /** \brief size of the external buffer */
    uint32_t buffer_size;

    /** \brief current bit */
    uint8_t bit_count; };

#endif // SERIALIZER_HPP
