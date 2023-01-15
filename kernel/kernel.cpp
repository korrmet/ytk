/** \file kernel.cpp
 *  \brief implementation of necessary kernel functions */

#include <cstdint>
#include "containers/automatic_list.hpp"
#include "kernel/kernel.h"
#include "kernel/module.hpp"
#include "kernel/init.hpp"

void kernel_step(uint32_t ticks)
{ static bool greeting = false;
  if (!greeting)
  { /* greet the user */
    greeting = true; }
  
  static bool dependencies_handled = false;

  if (!dependencies_handled)
  { process_dependencies();
    dependencies_handled = true;
    return; }
  
  i_kernel_module* mod = automatic_list<i_kernel_module>::root;

  while (mod)
  { init_module(*mod, ticks);

    if (ticks - mod->polled >= mod->period)
    { mod->poll(); mod->polled = ticks; }
    mod = mod->automatic_list<i_kernel_module>::next; } }
