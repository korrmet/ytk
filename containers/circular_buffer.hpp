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

    /** \brief push referenced value to head of the buffer 
     *
     *  \param val reference to value that need to add
     *
     *  \return adding result
     *  \retval true  value was added
     *  \retval false value was not added */
    bool push_head(TYPE& val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[head] = val;
      fullness++; head++;

      if (head >= VOLUME) { head = 0; }

      bsp_leave_critical();

      return true; }

    /** \brief push value by pointer to head of the buffer
     *  
     *  \param val pointer to value that need to add
     *
     *  \return adding result
     *  \retval true  value was added
     *  \retval false value was not added */
    bool push_head(TYPE* val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[head] = *val;
      fullness++; head++;
      
      if (head >= VOLUME) { head = 0; }

      bsp_leave_critical();

      return true; }

    /** \brief returns value on the top of the buffer
     *
     *  \return pointer to the value
     *  \retval !nullptr valid pointer to the value
     *  \retval nullptr  no value */
    TYPE* fetch_head(void)
    { if (!fullness) { return nullptr; }
      return &memory[head]; }

    /** \brief deletes one value from the top of the buffer
     *
     *  \return result of deletion
     *  \retval true  value was deleted
     *  \retval false value was not deleted (nothing to delete) */
    bool pop_head(void)
    { if (!fullness) { return false; }

      bsp_enter_critical();

      fullness--; head--;

      if (head >= VOLUME) { head = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    /** \brief add referenced value to the tail of the buffer
     *  
     *  \param val reference to value that need to add
     *
     *  \return result of addition
     *  \retval true  value is added
     *  \retval false value is not added (no place to add) */
    bool push_tail(TYPE& val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[tail] = val;
      fullness++; tail--;

      if (tail >= VOLUME) { tail = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    /** \brief add value by pointer to the tail of the buffer
     *
     *  \param val reference to value that need to add
     *  
     *  \return result of addition
     *  \retval true  value is added
     *  \retval false value is not added */
    bool push_tail(TYPE* val)
    { if (fullness >= VOLUME) { return false; }

      bsp_enter_critical();

      memory[tail] = *val;
      fullness++; tail--;

      if (tail >= VOLUME) { tail = VOLUME - 1; }

      bsp_leave_critical();

      return true; }

    /** \brief returns value on the bottom of buffer
     * 
     *  \return pointer to value
     *  \retval !nullptr valid pointer to the value
     *  \retval nullptr  no value */
    TYPE* fetch_tail(void)
    { if (!fullness) { return nullptr; }
      return &memory[tail]; }

    /** \brief deletes value on the tail of the buffer
     *
     *  \return result of deletion
     *  \retval truea value is deleted
     *  \retval false value isn't deleted (nothing to delete) */
    bool pop_tail(void)
    { if (!fullness) { return false; }

      bsp_enter_critical();

      fullness--; tail++;

      if (tail >= VOLUME) { tail = 0; }

      bsp_leave_critical();

      return true; }

    /** \brief returns memory volume that is already used
     *
     *  \return number of elements */
    uint32_t memory_used() { return fullness; }

    /** \brief returns free memory volume
     *  
     *  \return number of elements */
    uint32_t memory_available() { return VOLUME - fullness; }

  private:
    /** \brief pointer to the memory that this buffer serves */
    TYPE* memory;
    
    /** \brief index of head element */
    uint32_t head;

    /** \brief idex of tail memory */
    uint32_t tail;

    /** \brief number of used elements */
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
    /** \brief internal memory of the buffer */
    TYPE memory[VOLUME];
};

#endif // CIRCULAR_BUFFER_HPP
