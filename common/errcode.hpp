/** \file    errcode.hpp
 *  \brief   macro definitions of error codes */

#ifndef ERRCODE_HPP
#define ERRCODE_HPP

/** \defgroup errcodes
 *  \brief    error codes
 *  \details  error codes are global in this project, every module use the same
 *            codes. there is no global errno variable, but any code that can
 *            produce error definition has it's own errcode variable. common
 *            name for this variable is "errcode". errcode variable type is
 *            any of unsigned integer
 *  \{ */

/** \brief no error */
#define ERR_OK 0

/** \brief somewhere buffer was overflowed */
#define ERR_BUFFER_OVERFLOW 1

/** \brief data wasn't passed check */
#define ERR_INVALID_DATA 2

/** \brief can't sign piece of data */
#define ERR_NOSIGN 3

/** \} */

#endif // ERRCODE_HPP
