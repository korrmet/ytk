/** \file print.hpp
 *  \details interface of better printf or stdout replacement */

#ifndef PRINT_HPP
#define PRINT_HPP

#include <cstdint>
#include "bsp/bsp.h"

#define PRINT_NO_LIMITS 0
#define STD_SPACER ' '
#define STD_PRECISION_DIGITS 2

/** \brief left alignment */
#define ALIGN_LEFT 0

/** \brief rignt alignment */
#define ALIGN_RIGHT 1

/** \brief center alignment */
#define ALIGN_CENTER 2

/** \brief justify spaces between words in specified space */
#define ALIGN_JUSTIFY 3

/** \brief default alignment */
#define STD_ALIGN ALIGN_LEFT

/** \brief tool to formatted print to service interface or to buffer */
class print
{ public:

  print(uint8_t* buffer, uint32_t size);

  print& host_order();
  print& network_order();
  print& flush();

  /** \brief prints the c-string terminated by null
   *  
   *  \param str pointer to string literal
   *  \param len length of space for the string
   *  \param spc free space filler
   *
   *  \returns reference to the printing object */
  print& operator()(const char* str, 
                    uint32_t len = PRINT_NO_LIMITS,
                    uint8_t align = STD_ALIGN,
                    char spc = STD_SPACER);
  
  /** \brief same as operator() overload but explicit */
  print& s(const char* str,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t align = STD_ALIGN,
           char spc = STD_SPACER);
  
  print& s(char* str,
           uint32_t len = PRINT_NO_LIMITS,
           char spc = STD_SPACER);
  
  print& u(uint32_t uint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           char spc = STD_SPACER);
  
  print& x(uint32_t uint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           char spc = STD_SPACER);
  
  print& X(uint32_t uint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           char spc = STD_SPACER);

  print& o(uint32_t uint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           char spc = STD_SPACER);

  print& b(uint32_t uint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           char spc = STD_SPACER);
  
  print& i(int32_t sint,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           bool print_plus = false,
           char spc = STD_SPACER);
  
  print& f(float flt,
           uint32_t prec = STD_PRECISION_DIGITS,
           uint32_t len = PRINT_NO_LIMITS,
           uint8_t separate_num = 0,
           bool print_plus = false,
           char spc = STD_SPACER);

  print& p(void* ptr);

  uint8_t errcode;
};

#endif // PRINT_HPP
