/** \file  init.cpp
 *  \brief initialization system */

#ifndef INIT_HPP
#define INIT_HPP

#include "containers/automatic_list.hpp"
#include "kernel/module.hpp"

class init_dependency : virtual public automatic_list<init_dependency>
{ public:
  init_dependency(i_kernel_module& source, i_kernel_module& target)
    : source(source), target(target) {}

  i_kernel_module& source;
  i_kernel_module& target; };

#define DEPEND(source, target) \
  init_dep dependency_##__FILE__##__LINE__##(source, target);

/** \brief   scans dependency rules and process it in modules.
 *  \details in each step it scans for cyclic dependencies and if
 *           something wrong prints the name of cycled module */
bool process_dependencies();

/** \brief   scans in depth the dependency tree for the uninitialized modules
 *           and call their init method according period of polling
 *  \details this method use recursive algorithm to scan tree
 *
 *  \param mod   reference to current module
 *  \param ticks current timestamp */
void init_module(i_kernel_module& mod, uint32_t ticks);

#endif // INIT_HPP
