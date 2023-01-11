/** \file  shell.hpp
 *  \brief contains shell api and declaration */

#ifndef SHELL_HPP
#define SHELL_HPP

#include <cstdint>
#include "containers/automatic_list.hpp"

class i_shell_command : public virtual automatic_list<i_shell_command>
{ public:

  /** \brief name of the command, standard null-terminated string */
  const char* name;

  /** \brief handle shell argument
   *
   *  \param arg     argument of the command
   *  \param argsize size of the argument
   *
   *  \return result of handling
   *  \retval true  argument handled
   *  \retval false argument is not handled or it's invalid, execution of the
   *                command stops */
  virtual bool argument_handle(char* arg, uint32_t argsize) = 0;

  /** \brief handle shell command
   *
   *  \return result of handing
   *  \retval true  command is executed successfully
   *  \retval false command is not executed of error occured */
  virtual bool command_handle() = 0;
};

/** \brief   simple shell with support of the user commands
 *  \details this shell apply just simplest behavior of command line interface.
 *           it includes just calling of the function with few argument and
 *           prints back it's output. user commands should be pretty tiny
 *           because it blocks execution of other code. use this feature wisely
 *  \note    see i_shell_command interface
 *
 *  \tparam VOLUME volume of the input buffer */
template <uint32_t VOLUME>
class shell
{ public:

  private:
};

#endif // SHELL_HPP
