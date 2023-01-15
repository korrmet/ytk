/** \file  init.cpp
 *  \brief initialization system */

#ifndef INIT_HPP
#define INIT_HPP

#include "containers/automatic_list.hpp"
#include "kernel/module.hpp"

class init_dep : virtual public automatic_list<init_dep>
{ public:
  init_dep(i_kernel_module& source, i_kernel_module& target)
    : source(source), target(target) {}

  i_kernel_module& source;
  i_kernel_module& target; };

#define DEPEND(source, target) \
  init_dep dependency_##__FILE__##__LINE__##(source, target);

#endif // INIT_HPP
