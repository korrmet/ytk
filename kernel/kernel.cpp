/** \file kernel.cpp
 *  \brief implementation of necessary kernel functions */

#include <cstdint>
#include "kernel/kernel.h"
#include "kernel/module.hpp"
#include "kernel/init.hpp"

// TODO: make initialization subsystem

void kernel_step(uint32_t ticks)
{ init_dep* dep = automatic_list<init_dep>::root;

  while (dep)
  {
    dep = dep->next; }
  
  i_kernel_module* mod = automatic_list<i_kernel_module>::root;

  while (mod)
  { if (ticks - mod->polled >= mod->period)
    { mod->poll(); mod->polled = ticks; }
    mod = mod->next; } }
