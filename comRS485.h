/*
 * comRS485.h
 *
 * Created: 23/03/2018 19:01:05
 *  Author: Thierry
 */

uint32_t ComRS485(uint32_t sc, ...);

#define COMRS485_NEW					100
#define COMRS485_SEND					102
#define COMRS485_FLUSH_RX				103
#define COMRS485_FLUSH_TX				104
#define COMRS485_GET_BUF_PTR			105

#define rs485_Send(frameLen,needAck)	ComRS485(COMRS485_SEND,(uint32_t)(frameLen),(uint32_t)(needAck))
#define rs485_FlushRx()					ComRS485(COMRS485_FLUSH_RX)
#define rs485_FlushTx()					ComRS485(COMRS485_FLUSH_TX)
#define rs485_GetBufPtr()				ComRS485(COMRS485_GET_BUF_PTR)
