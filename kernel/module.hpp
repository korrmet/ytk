/** \file module.hpp
 *  \brief interface of kernel module */

#ifndef MODULE_HPP
#define MODULE_HPP

#include <cstdint>
#include <containers/automatic_list.hpp>

class i_kernel_module : public virtual automatic_list<i_kernel_module>
{ public:
  virtual void poll() = 0;
  uint32_t period;
  uint32_t polled;
};

#endif // MODULE_HPP
