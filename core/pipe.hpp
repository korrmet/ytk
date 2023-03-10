/** \file pipe.hpp
 *  \brief pipe templates to implement pipeline architecture */

#ifndef PIPE_HPP
#define PIPE_HPP

#include <cstdint>
#include "core/module.hpp"
#include "containers/automatic_list.hpp"
#include "containers/circular_buffer.hpp"

/** \brief pipe interface for inner usage */
class i_pipe
{ public:

    /** \brief   write data in pipe
     *  \details implemented in actual pipe class
     *
     *  \param data pointer to data
     *  \param size size of data
     *
     *  \return size of written data */
    virtual uint32_t write(void* data, uint32_t size) = 0;

    /** \brief   read data from pipe
     *  \details implemented in actual pipe class
     *
     *  \param data pointer to data buffer to store
     *  \param size size of data
     *
     *  \return size of readen data */
    virtual uint32_t read(void* data, uint32_t size) = 0;

    /** \brief   get used data size
     *  \details implemented in actual pipe class
     *  \details used for writing in pipe and for monitoring pipeline system
     *           usage
     *
     *  \return size of currently used data */
    virtual uint32_t fullness() = 0;

    /** \brief   total size of data that pipe can contain
     *  \details implemented in actual pipe class
     *  \details used for monitoring pipeline system usage
     *
     *  \return total size of data that pipe can contain */
    virtual uint32_t size() = 0;

    /** \brief   name of pipe
     *  \details used for monitoring pipeline system usage */
    const char* name; };

/** \brief pipe with variable size
 *
 *  \tparam VOLUME size of data that can the pipe contain */
template <uint32_t VOLUME>
class pipe : public i_pipe
{ public:
    /** \brief write data chunk in pipe
     *
     *  \param data pointer to data to write
     *  \param size size of data to write
     *
     *  \return size of data that has been written */
    virtual uint32_t write(void* data, uint32_t size) override
    { if (!data) { return 0; }

      uint8_t* d = (uint8_t*)data;
      uint32_t written = 0;

      while (size)
      { if (!buf.push_head(d)) { return written; }

        d++; size--; written++; }

      return written; }

    /** \brief read data from pipe
     *
     *  \param data pointer to the buffer to store readen data
     *  \param size size of the buffer to store readen data
     *
     *  \return size of data that has been readen */
    virtual uint32_t read(void* data, uint32_t size) override
    { if (!data) { return 0; }

      uint8_t* d = (uint8_t*)data;
      uint32_t readen = 0;

      while (size)
      { uint8_t* tail = buf.fetch_tail();

        if (!tail) { return readen; }

        *d = *tail;
        buf.pop_tail();
        d++; size--; readen++; }

      return readen; }

    /** \brief get used data size
     *
     *  \return used data size */
    virtual uint32_t fullness() override { return buf.fullness; }

    /** \brief get total size
     *
     *  \return total size of data that pipe can contain */
    virtual uint32_t size() override { return VOLUME; }

    /** \brief   data buffer to store pipe data
     *  \details used as FIFO */
    circular_buffer_static<uint8_t, VOLUME> buf; };

/** \brief   output of the data
 *  \details mostly used inside modules. it help isolate module from another
 *           ones. it is primary communication mechanism */
template <typename TYPE>
class output
{ public:
    /** \brief   writes data to connected pipe
     *  \details unconnected output do nothing. be careful, it can block
     *           module execution
     *
     *  \param val   pointer to value array to transmit throuh connected pipe
     *  \param count size of the pointer to value array to transmit through
     *               connected pipe
     *
     *  \return number of values that transmitted to another module */
    uint32_t operator()(TYPE* val, uint32_t count)
    { if (!p) { return 0; }

      uint32_t written = 0;

      while (p->fullness() >= sizeof(TYPE) && count)
      { if (p->write(val, sizeof(TYPE)) != sizeof(TYPE)) { return written; }

        val++; count--; written++; }

      return written; }

    /** \brief pointer to pipe that connected to another module */
    i_pipe* p; };

/** \brief   input of the data
 *  \details mostly used inside modules. it help isolate module from another
 *           ones. it is primary communication mechanism */
template <typename TYPE>
class input
{ public:
    /** \brief
     *  \details unconnected input do nothing. be careful, it can block the
     *           module execution
     *
     *  \param val   pointer to value array to store received data through
     *               connected pipe
     *  \param count size of the pointer to the value array to store received
     *               data through connected pipe
     *
     *  \return number of received values */
    uint32_t operator()(TYPE* val, uint32_t count)
    { if (!p) { return 0; }

      uint32_t readen = 0;

      while (p->fullness() >= sizeof(TYPE) && count)
      { if (p->read(val, sizeof(TYPE)) != sizeof(TYPE)) { return readen; }

        val++; count--; readen++; }

      return readen; }

    /** \brief pointer to pipe that connected to another module */
    i_pipe* p; };

/** \brief   connect input and output with a pipe
 *  \details input and output should be same type
 *
 *  \param out output
 *  \param in  input
 *  \param vol size of data in bytes which pipe can store inside */
#define CONNECT(out, in, vol)          \
pipe<vol> pipe_##__FILE__##__LINE__##; \
in.p = &pipe_##__FILE__##__LINE__##;   \
out.p = &pipe_##__FILE__##__LINE__##;

#endif // PIPE_HPP
