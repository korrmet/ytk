/** \file  kernel.h
 *  \brief core functionality of semi-multitasking */

#ifndef KERNEL_H
#define KERNEL_H

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif // __cplusplus

/** \brief poll it with determined period (or constantly) */
void kernel_step(uint32_t ticks);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KERNEL_H
