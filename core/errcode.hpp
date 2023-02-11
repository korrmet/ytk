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

/** \brief invalid argiment given */
#define ERR_INVALID_ARGUMENT 4

/** \brief not ready to process the requested operation */
#define ERR_NOT_READY 5

/** \brief trying to access area that not belong to buffer */
#define ERR_BUFFER_OVERRUN 6
/** \} */

#endif // ERRCODE_HPP
