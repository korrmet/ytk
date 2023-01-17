/** \file init.cpp
 *  \brief implementation of initialization system */

#include <cstdint>
#include "containers/automatic_list.hpp"
#include "containers/linked_list.hpp"
#include "kernel/init.hpp"
#include "kernel/module.hpp"

void init_module(i_kernel_module& mod, uint32_t ticks)
{ if (mod.ready) { return; }

  i_kernel_module* dep = mod.linked_list::next;

  while (dep)
  { init_module(*dep, ticks);
    dep = dep->linked_list::next; }

  if (ticks - mod.polled >= mod.period)
  { mod.init(); mod.polled = ticks; } }

/** \brief   checks module for cyclic dependency
 *  \details scans dependency tree in depth using recursive algorithm
 *  \warning this algorithm isn't correct, it can't find the loop of any other
 *           node than given.
 *
 *  \param mod   module to seek in tree
 *  \param start start point of searching */
bool check_cyclic(i_kernel_module* mod, i_kernel_module* start)
{ i_kernel_module* dep = start->linked_list::next;

  while (dep)
  { if (dep == mod) { return true; }

    if (check_cyclic(mod, start)) { return true; }

    dep = dep->linked_list::next; }

  return false; }

bool process_dependencies()
{ init_dependency* deps = automatic_list<init_dependency>::root;

  while (deps)
  { if (deps->source.linked_list::next == nullptr)
    { deps->source.linked_list::next = &deps->target; }
    else
    { i_kernel_module* last = deps->source.linked_list::next;

      while (last->linked_list::next != nullptr)
      { last = last->linked_list::next; }

      last->linked_list::next = &deps->target; }

    // check for cyclic dependencies
    i_kernel_module* mods = automatic_list<i_kernel_module>::root;

    while (mods)
    { if (check_cyclic(mods, mods))
      { /* print the module name */
        return false; }

      mods = mods->automatic_list::next; }

    deps = deps->next; }

  return true; }
