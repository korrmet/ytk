/** \file  bsp.h
 *  \brief board support package interface */

#ifndef BSP_HPP
#define BSP_HPP

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** \bref    enter critical section
 *  \details you should implement this function yourself, it's only declaration
 *  \details after this call bsp guarantees that current thread will not be
 *           interrupted */
void bsp_enter_critical();

/** \brief   leave critical section
 *  \details you should implement this function yourself, it's only declaration
 *  \details after this call bsp allows thead interrupting */
void bsp_leave_critical();

/** \brief   transmit char via service interface
 *  \details you should guarantee that the character will be transmitted */
void bsp_tx_char(char ch);

/** \brief   receive char via service interface
 *  \details as the service interface is human readable console
 *           you can use zero as no character at present moment
 *  \details will be better if your implementation will be bufferized */
char bsp_rx_char();

/** \brief   request for force sent of bufferized data */
void bsp_tx_flush();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BSP_HPP
