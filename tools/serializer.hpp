/** \file    serializer.hpp
 *  \brief   a toolset that can help to convert anything to sequence of bytes or
 *           sequence of bytes in everything
 *  \details main purpose of these tools is build parsers and generators that
 *           would work on almost every platform
 *  \todo think more about signification, validation, transmit and receive
 *        mechanisms. already existing stuff was deleted */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include "containers/arrayed_buffer.hpp"

#define NO_LIMITS 0

/** \brief a tool to make the generic serial data generator */
class serializer
{ public:
    /** \brief constructor for buffered output variant
     *
     *  \param buffer      pointer to buffer to store sequence
     *  \param buffer_size size of buffer */
    serializer(void* buffer, uint32_t buffer_size);

    /** \brief changes byte order (host to network or network to host)
     *
     *  \return reference to the current serializer object */
    serializer& hn();

    /** \brief   insert the value in the data stream
     *  \warning be careful using the type that actually is an array.
     *           this method uses sizeof, but not all compilers can
     *           get size of type, size of the value might be diffirent than
     *           you expect. at present moment only gcc is preferred compiler
     *
     *  \tparam TYPE type of the variable
     *  \param  val  reference to the variable
     *
     *  \return reference to the current serializer object */
    template <typename TYPE>
    serializer& v(TYPE val) { return a(&val, sizeof(TYPE)); }

    /** \brief   insert the value by pointer in the data stream
     *  \warning be careful using the type that actually is an array.
     *           this method uses sizeof, but not all compilers can
     *           get size of type, size of the value might be diffirent than
     *           you expect. at present moment only gcc is preferred compiler
     *
     *  \tparam TYPE type of the variable
     *  \param  val  reference to the variable
     *
     *  \return reference to the current serializer object */
    template <typename TYPE>
    serializer& v(TYPE* val) { return a(val, sizeof(TYPE)); }

    /** \brief add array to the sequence
     *
     *  \param buf pointer to the buffer that should be added
     *  \param len size of the buffer
     *
     *  \return reference to the current serializer object */
    serializer& a(void* buf, uint32_t len);

    /** \brief   add c-string to the sequence
     *  \details this method guarantees that all available data would be
     *           written in buffer in borders of requested field size.
     *           also the string termination is guaranteed
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

    /** \brief move through the sequence forwards or backwards
     *
     *  \param step number and direction of steps according the current point
     *
     *  \return reference to the current serializer object */
    serializer& seek(int32_t step);

    /** \brief current position in the buffer */
    uint32_t pos;

    /** \brief last error code */
    uint8_t errcode;

  private:
    /** \brief current byte order
     *  \note true for straign system order, false for reverse order */
    bool byte_order;

    /** \brief pointer to the external buffer where the serial data would be
     *         placed */
    void* buffer;

    /** \brief size of the external buffer */
    uint32_t buffer_size; };

/** \brief tool to make generic serial data parser */
class deserializer
{ public:
    /** \brief constructor for buffered input variant
     *
     *  \param buffer      pointer to the buffer to store a sequence
     *  \param buffer_size size of the buffer */
    deserializer(void* buffer, uint32_t buffer_size);

    /** \brief changes byte order (host to network or network to host
     *
     *  \return reference to the current deserializer object */
    deserializer& hn();

    /** \brief   extracts the value by reference form the sequence
     *  \warning be careful using the type that actually is an array.
     *           this method uses sizeof, but not all compilers can
     *           get size of type, size of the value might be diffirent than
     *           you expect. at present moment only gcc is preferred compiler
     *
     *  \tparam TYPE type of the variable
     *  \param  val  reference to the variable
     *
     *  \return reference to the current deserializer object */
    template <typename TYPE>
    deserializer& v(TYPE& val) { return a(&val, sizeof(TYPE)); }

    /** \brief   extracts the value by pointer form the sequence
     *  \warning be careful using the type that actually is an array.
     *           this method uses sizeof, but not all compilers can
     *           get size of type, size of the value might be diffirent than
     *           you expect. at present moment only gcc is preferred compiler
     *
     *  \tparam TYPE type of the variable
     *  \param  val  pointer to the variable
     *
     *  \return reference to the current deserializer object */
    template <typename TYPE>
    deserializer& v(TYPE* val) { return a(val, sizeof(TYPE)); }

    /** \brief extracts array from the sequence
     *  \warning there is no any check for buffer size, I hope you can deal
     *           with it
     *
     *  \param buf pointer to the buffer for array
     *  \param len size of array in the sequence
     *
     *  \return reference to the current deserializer object */
    deserializer& a(void* buf, uint32_t len);

    /** \brief   extracts string from the sequence
     *  \details guarantees that current point would be straight after the
     *           string terminator
     *  \warning there is no any chek for the buffer size until len parameter.
     *           I think you can deal with it.
     *
     *  \param buf pointer to the bufer for the string
     *  \param len size of the string in the sequence
     *
     *  \return reference to the curren deserializer object */
    deserializer& s(char* buf, uint32_t len = NO_LIMITS);

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
    /** \brief current byte order
     *  \note true for straign system order, false for reverse order */
    bool byte_order;

    /** \brief pointer to the external buffer where the sequence is placed */
    void* buffer;

    /** \brief size of the external buffer */
    uint32_t buffer_size; };

#endif // SERIALIZER_HPP
