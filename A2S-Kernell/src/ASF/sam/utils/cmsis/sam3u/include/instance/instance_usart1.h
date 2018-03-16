/**
 * \file
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _SAM3U_usart1_INSTANCE_
#define _SAM3U_usart1_INSTANCE_

/* ========== Register definition for usart1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_usart1_CR          (0x40094000U) /**< \brief (usart1) Control Register */
#define REG_usart1_MR          (0x40094004U) /**< \brief (usart1) Mode Register */
#define REG_usart1_IER          (0x40094008U) /**< \brief (usart1) Interrupt Enable Register */
#define REG_usart1_IDR          (0x4009400CU) /**< \brief (usart1) Interrupt Disable Register */
#define REG_usart1_IMR          (0x40094010U) /**< \brief (usart1) Interrupt Mask Register */
#define REG_usart1_CSR          (0x40094014U) /**< \brief (usart1) Channel Status Register */
#define REG_usart1_RHR          (0x40094018U) /**< \brief (usart1) Receiver Holding Register */
#define REG_usart1_THR          (0x4009401CU) /**< \brief (usart1) Transmitter Holding Register */
#define REG_usart1_BRGR          (0x40094020U) /**< \brief (usart1) Baud Rate Generator Register */
#define REG_usart1_RTOR          (0x40094024U) /**< \brief (usart1) Receiver Time-out Register */
#define REG_usart1_TTGR          (0x40094028U) /**< \brief (usart1) Transmitter Timeguard Register */
#define REG_usart1_FIDI          (0x40094040U) /**< \brief (usart1) FI DI Ratio Register */
#define REG_usart1_NER          (0x40094044U) /**< \brief (usart1) Number of Errors Register */
#define REG_usart1_IF          (0x4009404CU) /**< \brief (usart1) IrDA Filter Register */
#define REG_usart1_MAN          (0x40094050U) /**< \brief (usart1) Manchester Encoder Decoder Register */
#define REG_usart1_WPMR          (0x400940E4U) /**< \brief (usart1) Write Protect Mode Register */
#define REG_usart1_WPSR          (0x400940E8U) /**< \brief (usart1) Write Protect Status Register */
#define REG_usart1_RPR          (0x40094100U) /**< \brief (usart1) Receive Pointer Register */
#define REG_usart1_RCR          (0x40094104U) /**< \brief (usart1) Receive Counter Register */
#define REG_usart1_TPR          (0x40094108U) /**< \brief (usart1) Transmit Pointer Register */
#define REG_usart1_TCR          (0x4009410CU) /**< \brief (usart1) Transmit Counter Register */
#define REG_usart1_RNPR          (0x40094110U) /**< \brief (usart1) Receive Next Pointer Register */
#define REG_usart1_RNCR          (0x40094114U) /**< \brief (usart1) Receive Next Counter Register */
#define REG_usart1_TNPR          (0x40094118U) /**< \brief (usart1) Transmit Next Pointer Register */
#define REG_usart1_TNCR          (0x4009411CU) /**< \brief (usart1) Transmit Next Counter Register */
#define REG_usart1_PTCR          (0x40094120U) /**< \brief (usart1) Transfer Control Register */
#define REG_usart1_PTSR          (0x40094124U) /**< \brief (usart1) Transfer Status Register */
#else
#define REG_usart1_CR (*(WoReg*)0x40094000U) /**< \brief (usart1) Control Register */
#define REG_usart1_MR (*(RwReg*)0x40094004U) /**< \brief (usart1) Mode Register */
#define REG_usart1_IER (*(WoReg*)0x40094008U) /**< \brief (usart1) Interrupt Enable Register */
#define REG_usart1_IDR (*(WoReg*)0x4009400CU) /**< \brief (usart1) Interrupt Disable Register */
#define REG_usart1_IMR (*(RoReg*)0x40094010U) /**< \brief (usart1) Interrupt Mask Register */
#define REG_usart1_CSR (*(RoReg*)0x40094014U) /**< \brief (usart1) Channel Status Register */
#define REG_usart1_RHR (*(RoReg*)0x40094018U) /**< \brief (usart1) Receiver Holding Register */
#define REG_usart1_THR (*(WoReg*)0x4009401CU) /**< \brief (usart1) Transmitter Holding Register */
#define REG_usart1_BRGR (*(RwReg*)0x40094020U) /**< \brief (usart1) Baud Rate Generator Register */
#define REG_usart1_RTOR (*(RwReg*)0x40094024U) /**< \brief (usart1) Receiver Time-out Register */
#define REG_usart1_TTGR (*(RwReg*)0x40094028U) /**< \brief (usart1) Transmitter Timeguard Register */
#define REG_usart1_FIDI (*(RwReg*)0x40094040U) /**< \brief (usart1) FI DI Ratio Register */
#define REG_usart1_NER (*(RoReg*)0x40094044U) /**< \brief (usart1) Number of Errors Register */
#define REG_usart1_IF (*(RwReg*)0x4009404CU) /**< \brief (usart1) IrDA Filter Register */
#define REG_usart1_MAN (*(RwReg*)0x40094050U) /**< \brief (usart1) Manchester Encoder Decoder Register */
#define REG_usart1_WPMR (*(RwReg*)0x400940E4U) /**< \brief (usart1) Write Protect Mode Register */
#define REG_usart1_WPSR (*(RoReg*)0x400940E8U) /**< \brief (usart1) Write Protect Status Register */
#define REG_usart1_RPR (*(RwReg*)0x40094100U) /**< \brief (usart1) Receive Pointer Register */
#define REG_usart1_RCR (*(RwReg*)0x40094104U) /**< \brief (usart1) Receive Counter Register */
#define REG_usart1_TPR (*(RwReg*)0x40094108U) /**< \brief (usart1) Transmit Pointer Register */
#define REG_usart1_TCR (*(RwReg*)0x4009410CU) /**< \brief (usart1) Transmit Counter Register */
#define REG_usart1_RNPR (*(RwReg*)0x40094110U) /**< \brief (usart1) Receive Next Pointer Register */
#define REG_usart1_RNCR (*(RwReg*)0x40094114U) /**< \brief (usart1) Receive Next Counter Register */
#define REG_usart1_TNPR (*(RwReg*)0x40094118U) /**< \brief (usart1) Transmit Next Pointer Register */
#define REG_usart1_TNCR (*(RwReg*)0x4009411CU) /**< \brief (usart1) Transmit Next Counter Register */
#define REG_usart1_PTCR (*(WoReg*)0x40094120U) /**< \brief (usart1) Transfer Control Register */
#define REG_usart1_PTSR (*(RoReg*)0x40094124U) /**< \brief (usart1) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3U_usart1_INSTANCE_ */
