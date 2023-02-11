/** \file  arrayed_buffer.hpp
 *  \brief this container automates the most common buffer operations
 *  \todo make arrayed buffer but for external memory */

#ifndef ARRAYED_BUFFER_HPP
#define ARRAYED_BUFFER_HPP

#include <cstdint>

/** \brief   container with extra tools that ease using arrays and you still
 *           able to use it as regular array
 *  \details use an external memory to operate
 *  \details front of the buffer has index 0, bask is the last element that
 *           contains actual data. this container controls it's fullness and
 *           notify you if any error occured
 *
 *  \tparam TYPE type of the elementf of the array */
template <typename TYPE>
class arrayed_buffer
{ public:
    explicit arrayed_buffer(TYPE* mem, uint32_t volume)
      : used(0),
        mem(mem),
        mem_size(volume)
    {}

    /** \brief inset one element in front of an array
     *
     *  \param data data element that should be added
     *
     *  \return result of insertion
     *  \retval true  element successfully inserted
     *  \retval false error occured, maybe buffer is overflowed */
    bool push_front(TYPE data)
    { if (used >= mem_size) { return false; }

      shift_right(1);
      mem[0] = data;
      used++;
      return true; }

    /** \brief currently used memory */
    uint32_t used;

    /** \brief insert one element in front of an array
     *
     *  \param data pointer to data element that should be added
     *
     *  \return result of insertion
     *  \retval true  element successfully inserted
     *  \retval false error occured, maybe buffer is overflowed or null
     *                pointer given */
    bool push_front(const TYPE* data)
    { if (!data) { return false; }

      if (used >= mem_size) { return false; }

      shift_right(1);
      mem[0] = *data;
      used++;
      return true; }

    /** \brief delete one element in front of an array
     *
     *  \return result of deletion
     *  \retval true  one element deleted
     *  \retval false error occured, maybe buffer is empty */
    bool pop_front()
    { if (!used) { return false; }

      shift_left(1);
      return true; }

    /** \brief copy element in front of the array
     *
     *  \param buf reference to the buffer for the requested element
     *
     *  \return result of fetching
     *  \retval true  element copied
     *  \retval false error occured, maybe buffer is empty */
    bool fetch_front(TYPE& buf) const
    { if (!used) { return false; }

      buf = mem[0];
      return true; }

    /** \brief insert element in back of the array
     *
     *  \param data element that should be added
     *
     *  \return result of addition
     *  \retval true  element added
     *  \retval false error occure, maybe buffer is full */
    bool push_back(TYPE data)
    { if (used >= mem_size) { return false; }

      mem[used] = data;
      used++;
      return true; }

    /** \brief insert element in back of the array
     *
     *  \param data pointer to the element that should be added
     *
     *  \return result of addition
     *  \retval true  element added
     *  \retval false error occured, mybe buffer is full or null pointer
     *                given */
    bool push_back(const TYPE* data)
    { if (!data) { return false; }

      if (used >= mem_size) { return false; }

      mem[used] = *data;
      used++;
      return true; }

    /** \brief delete last element of the array
     *
     *  \return result of deletion
     *  \return true  element deleted
     *  \return false error occured, maybe buffer is empty */
    bool pop_back()
    { if (!used) { return false; }

      used--;
      return true; }

    /** \brief copy last element of the array
     *
     *  \param buf reference to data buffer to store last element
     *
     *  \return result of fetching
     *  \retval true  element copied
     *  \retval false error occured, maybe buffer is empty */
    bool fetch_back(TYPE& buf) const
    { if (!used) { return false; }

      buf = mem[used - 1];
      return true; }

    /** \brief insert element in random position of the array
     *
     *  \param data reference to element that should be inserted
     *  \param pos  index of element inside the array
     *
     *  \return result of insertion
     *  \retval true  element inserted
     *  \retval false error occured, maybe buffer is full or incorrect index
     *                given */
    bool insert(const TYPE& data, uint32_t pos)
    { if (pos >=  used) { return false; }

      if (used >= mem_size) { return false; }

      shift_right(1, pos);
      mem[pos] = data;
      used++;
      return true; }

    /** \brief insert element in random position of the array
     *
     *  \param data pointer to element that should be inserted
     *  \param pos  index of element inside the array
     *
     *  \return result of insertion
     *  \retval true  element inserted
     *  \retval false error occured, maybe buffer is full or incorrect index
     *                given of null pointer given */
    bool insert(const TYPE* data, uint32_t pos)
    { if (!data) { return false; }

      if (pos >= used) { return false; }

      if (used >= mem_size) { return false; }

      shift_right(1, pos);
      mem[pos] = *data;
      used++;
      return true; }

    /** \brief reset the buffer */
    void reset() { used = 0; }

    /** \brief shifts data in the array left
     *
     *  \param num number of shifts
     *  \param pos index of the array that would be first shifted byte
     *
     *  \return result of shifting
     *  \retval true  data shifted
     *  \retval false error occured, maybe incorrect num or pos given */
    bool shift_left(uint32_t num, uint32_t pos = 0)
    { if (pos >= used) { return false; }

      if (num >= used) { return false; }

      for (uint32_t i = 0; i < pos - num; i++) { mem[i] = mem[i + num]; }

      return true; }

    /** \brief shifts data in the array right
     *
     *  \param num number of shifts
     *  \param pos index of the array that would be first shifted byte
     *
     *  \return result of shifting
     *  \retval true  data shifted
     *  \retval false error occured, maybe incorrect num or por given */
    bool shift_right(uint32_t num, uint32_t pos = 0)
    { if (pos >= used) { return false; }

      if (num >= used) { return false; }

      for (uint32_t i = used - 1; i >= pos + num; i--)
      { mem[i] = mem[i - num]; }

      return true; }

  private:
    /** \brief external memory that this buffer will manage */
    TYPE* mem;

    /** \brief size of the external memory */
    uint32_t mem_size; };

/** \brief   container with extra tools that ease using array and you still able
 *           to use it as regular array;
 *  \details contains its own memory
 *  \details front of the buffer has index 0, back is the last element that
 *           contains actual data. this container controls it's fullness and
 *           note you if any error occured.
 *
 *  \tparam TYPE   type of elements of array
 *  \tparam VOLUME number of elements in array */
template <typename TYPE, uint32_t VOLUME>
class arrayed_buffer_static : public arrayed_buffer<TYPE>
{ public:
    // cppcheck-suppress uninitMemberVar
    arrayed_buffer_static()
      : arrayed_buffer<TYPE>(memory, VOLUME)
    {}

    /** \brief memory that buffer manage */
    TYPE memory[VOLUME]; };

#endif // ARRAYED_BUFFER_HPP
