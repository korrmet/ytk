/** \file  bsp.h
 *  \brief board support package interface */

#ifndef BSP_HPP
#define BSP_HPP

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** \bref    enter critical section
 *  \details after this call bsp guarantees that current thread will not be
 *           interrupted */
void bsp_enter_critical();

/** \brief   leave critical section
 *  \details after this call bsp allows thead interrupting */
void bsp_leave_critical();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BSP_HPP
