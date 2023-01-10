/** \file  circular_buffer.hpp
 *  \brief implementations of circular buffer */

#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cstdint>
#include "bsp/bsp.h"

/** \brief   generic circular buffer implementation
 *  \details uses external memory to store data
 *
 *  \tparam TYPE   type of elements stored in buffer
 *  \tparam VOLUME maximum number of the elements to store */
template <typename TYPE, uint32_t VOLUME>
class circular_buffer
{ public:
    explicit circular_buffer(TYPE* mem)
      : memory(mem),
        head(0),
        tail(0),
        fullness(0)
    {}

    virtual ~circular_buffer() {}

    bool push_head(TYPE& val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[head] = val;
      fullness++; head++;

      if (head >= VOLUME) { head = 0; }

      bsp_leave_critical();

      return true; }

    bool push_head(TYPE* val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[head] = *val;
      fullness++; head++;
      
      if (head >= VOLUME) { head = 0; }

      bsp_leave_critical();

      return true; }

    TYPE* fetch_head(void)
    { if (!fullness) { return nullptr; }
      return &memory[head]; }

    bool pop_head(void)
    { if (!fullness) { return false; }

      bsp_enter_critical();

      fullness--; head--;

      if (head >= VOLUME) { head = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    bool push_tail(TYPE& val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[tail] = val;
      fullness++; tail--;

      if (tail >= VOLUME) { tail = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    bool push_tail(TYPE* val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[tail] = *val;
      fullness++; tail--;

      if (tail >= VOLUME) { tail = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    TYPE* fetch_tail(void)
    { if (!fullness) { return nullptr; }
      return &memory[tail]; }

    bool pop_tail(void)
    { if (!fullness) { return false; }

      bsp_enter_critical();

      fullness--; tail++;

      if (tail >= VOLUME) { tail = 0; }

      bsp_leave_critical();

      return true; }

    uint32_t memory_used() { return fullness; }

    uint32_t memory_available() { return VOLUME - fullness; }

  private:
    TYPE* memory;
    uint32_t head;
    uint32_t tail;
    uint32_t fullness;
};

/** \brief   circular buffer wrapper with it's own memory
 *  
 *  \tparam TYPE   type of elements stored in buffer
 *  \tparam VOLUME maximum number of the elements to store */
template <typename TYPE, uint32_t VOLUME>
class circular_buffer_static : public circular_buffer<TYPE, VOLUME>
{ public:
  circular_buffer_static()
    : circular_buffer<TYPE, VOLUME>(memory)
  {}

  virtual ~circular_buffer_static() {}

  private:
    TYPE memory[VOLUME];
};

#endif // CIRCULAR_BUFFER_HPP
