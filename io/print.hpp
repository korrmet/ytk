/** \file print.hpp
 *  \details interface of better printf or cout replacement */

#ifndef PRINT_HPP
#define PRINT_HPP

#include <cstdint>
#include "bsp/bsp.h"

/** \defgroup print_flags
 *  \brief    set of flags that used in print
 *  \{ */

/** \brief size that disables limitation for print space size */
#define PRINT_NO_LIMITS 0

/** \brief standard spacer */
#define STD_SPACER ' '

/** \brief standard precision for print floating-point numbers */
#define STD_PRECISION_DIGITS 2

/** \brief left alignment */
#define ALIGN_LEFT 0

/** \brief rignt alignment */
#define ALIGN_RIGHT 1

/** \brief center alignment */
#define ALIGN_CENTER 2

/** \brief default alignment */
#define STD_ALIGN ALIGN_LEFT

/** \} */

/** \brief tool to formatted print to service interface or to buffer */
class print
{ public:

    /** \brief constructor for printing in buffer
     *
     *  \param buffer pointer to byte array to print
     *  \param size   maximum available space to print */
    print(char* buffer, uint32_t size);

    /** \brief generic constructor for printing to dsp console */
    print();

    /** \brief   flush output buffer of dsp console
     *  \details doesn't work in buffered mode */
    print& flush();

    /** \brief in case of printing in buffer automatically terminates printed
     *         string */
    print& terminate();

    /** \brief prints the c-string terminated by null
     *  \note  version for string literals
     *
     *  \param str   pointer to string literal
     *  \param len   length of space for the string
     *  \param align alignment inside printing space
     *  \param spc   free space filler
     *
     *  \return reference to the printing object */
    print& operator()(const char* str,
                      uint32_t len = PRINT_NO_LIMITS,
                      uint8_t align = STD_ALIGN,
                      char spc = STD_SPACER);

    /** \brief prints the c-string terminated by null
     *  \note same as operator() overload but explicit
     *  \note version for string literals
     *
     *  \param str   pointer to string literal
     *  \param len   length of space for the string
     *  \param align alignment inside printing space
     *  \param spc   free space filler
     *
     *  \return reference to the printing object */
    print& s(const char* str,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief prints the c-string terminated by null
     *
     *  \param str   pointer to string
     *  \param len   length of space for the string
     *  \param align alignment inside printing space
     *  \param spc   free space filler
     *
     *  \return reference to the printing object */
    print& operator()(char* str,
                      uint32_t len = PRINT_NO_LIMITS,
                      uint8_t align = STD_ALIGN,
                      char spc = STD_SPACER);

    /** \brief prints the c-string terminated by null
     *  \note same as operator() overload but explicit
     *
     *  \param str   pointer to string
     *  \param len   length of space for the string
     *  \param align alignment inside printing space
     *  \param spc   free space filler
     *
     *  \return reference to the printing object */
    print& s(char* str,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief print unsigned integer
     *
     *  \param uint         value to be printed
     *  \param separate_num number characters between separator spaces
     *                      \note 0 if you don't need any separator
     *  \param len          length of space tor the value string
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& u(uint32_t uint,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief   print unsigned integer in hex
     *  \details lowercase variant
     *
     *  \param uint         value to be printed
     *  \param digits       number of digits to print
     *  \param len          length of space for the value sting
     *  \param separate_num number of characters between separator spaces
     *                      \note 0 if you don't need any separator
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& x(uint32_t uint,
             uint8_t digits = 32,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief   print unsigned integer in hex
     *  \details uppercase variant
     *
     *  \param uint         value to be printed
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *                      \note 0 if you don't need any separator
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& X(uint32_t uint,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief   print unsigned integer in octal
     *
     *  \param uint         value to be printed
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *                      \note 0 if you don't need any separator
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& o(uint32_t uint,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief print unsigned in as binary
     *
     *  \param uint         value to be printed
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& b(uint32_t uint,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief print signed integer
     *
     *  \param sint         value to be printed
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *  \param print_plus   turn on explicit plus
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& i(int32_t sint,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             bool print_plus = false,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief print floating point value
     *
     *  \param flt          floating point value
     *  \param prec         precision, volume of numbers after floating point
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *  \param print_plus   turn on explicit plus
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& f(float flt,
             uint32_t prec = STD_PRECISION_DIGITS,
             uint32_t len = PRINT_NO_LIMITS,
             uint8_t separate_num = 0,
             bool print_plus = false,
             uint8_t align = STD_ALIGN,
             char spc = STD_SPACER);

    /** \brief   print pointer
     *  \details print memory address in hex between '<' and '>' characters
     *  \warning result size is machine dependent
     *
     *  \param ptr          pointer that should be printed
     *  \param len          length of space for the value string
     *  \param separate_num number of characters between separator spaces
     *  \param align        alignment inside printing space
     *  \param spc          free space filler
     *
     *  \return reference to the printing object */
    print& p(void* ptr);

    /** \brief terminates the string by null
     *  \note  main purpose of using it is printing in buffer */
    print& t();

    /** \brief last error code
     *  \param if this variable would be not equal ERR_OK, the execution would
     *         be canceled */
    uint8_t errcode;

  private:
    /** \brief pointer to the buffer that used to print */
    char* buffer;

    /** \brief size of the buffer */
    uint32_t size;

    /** \brief current position inside buffer */
    uint32_t counter;

    /** \brief actually prints the string
     *  \note all other methods are just wrappers for your comfort
     *
     *  \param str   pointer to string
     *  \param len   length of space for the string
     *  \param align alignment inside printing space
     *  \param spc   free space filler */
    void print_string(char* str,
                      uint32_t len,
                      uint8_t align,
                      char spc);

    /** \brief combines routines to write in buffer and bsp console
     *
     *  \param ch char to be txed or written in buffer */
    void tx(char ch); };

#endif // PRINT_HPP
