/** \file  bsp.h
 *  \brief board support package interface */

#ifndef BSP_HPP
#define BSP_HPP

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
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

/** \brief   transmit data via system bus
 *  \details generally external system bus is a network with circle loop,
 *           this is output to next device
 *
 *  \param byte byte to transmit */
void bsp_sysbus_tx(uint8_t byte);

/** \brief   receive data from system bus
 *  \details generally external system bus is a network with circle loop,
 *           this is input from previous device
 *           this function is implemented in the library, call it when
 *           byte is received. you can call it in the receive interrupt but be
 *           careful, this function may perform a lot of hard work: it parse
 *           the input stream and as it found correct message it start to
 *           seek the destination node and if it was not found retranslate
 *           message to next device in chain
 *
 *  \param byte received byte */
void bsp_sysbus_rx_cb(uint8_t byte);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BSP_HPP
