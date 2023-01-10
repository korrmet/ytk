/** \file  automatic_list.hpp
 *  \brief implementation of automatic list to gather objects together */

#ifndef AUTOMATIC_LIST_HPP
#define AUTOMATIC_LIST_HPP

template <typename TYPE>
class automatic_list
{ public:
  automatic_list() : next(nullptr)
  { if (!root) { root = (TYPE*)this; }
    if (last)  { last->next = (TYPE*)this; }

    last = (TYPE*)this; }

  static TYPE* root;
  static TYPE* last;
  TYPE*        next;
};

template <typename TYPE>
TYPE* automatic_list<TYPE>::root = nullptr;

template <typename TYPE>
TYPE* automatic_list<TYPE>::last = nullptr;

#endif // AUTOMATIC_LIST_HPP
