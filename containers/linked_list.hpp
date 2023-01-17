/** \file  linked_list.hpp
 *  \brief linked list implementation */

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename TYPE>
class linked_list
{ public:
    linked_list() : next(nullptr) {}

    TYPE* next; };

#endif // LINKED_LIST_HPP
