/** \file module.hpp
 *  \brief interface of kernel module */

#ifndef MODULE_HPP
#define MODULE_HPP

#include <cstdint>
#include <containers/automatic_list.hpp>

class i_kernel_module : public virtual automatic_list<i_kernel_module>
{ public:
  /** \brief   this method will be periodically called with specified period
   *           to set up the module
   *  \details determine when the module is ready */
  virtual void init() = 0;

  /** \brief   this method will be periodically called with specified period
   *  \details it's represent actual runtime of your module, works only
   *           when module is ready */
  virtual void poll() = 0;
  
  /** \brief   name of the module
   *  \details shall be string literal or be constantly accessable */
  const char* name;

  /** \brief   version of the module
   *  \details shall be string literal of be constantly accessable */
  const char* version;

  uint32_t period;
  uint32_t polled;
  bool ready;
};

#endif // MODULE_HPP
