/** \file kernel.cpp
 *  \brief implementation of necessary kernel functions */

#include <cstdint>
#include "kernel/kernel.h"
#include "kernel/module.hpp"

void kernel_step(uint32_t ticks)
{ i_kernel_module* mod = automatic_list<i_kernel_module>::root;

  while (mod)
  { if (ticks - mod->polled >= mod->period)
    { mod->poll(); mod->polled = ticks; }
    mod = mod->next; } }
