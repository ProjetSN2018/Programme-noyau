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

#ifndef _SAM3U_usart2_INSTANCE_
#define _SAM3U_usart2_INSTANCE_

/* ========== Register definition for usart2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_usart2_CR          (0x40098000U) /**< \brief (usart2) Control Register */
#define REG_usart2_MR          (0x40098004U) /**< \brief (usart2) Mode Register */
#define REG_usart2_IER          (0x40098008U) /**< \brief (usart2) Interrupt Enable Register */
#define REG_usart2_IDR          (0x4009800CU) /**< \brief (usart2) Interrupt Disable Register */
#define REG_usart2_IMR          (0x40098010U) /**< \brief (usart2) Interrupt Mask Register */
#define REG_usart2_CSR          (0x40098014U) /**< \brief (usart2) Channel Status Register */
#define REG_usart2_RHR          (0x40098018U) /**< \brief (usart2) Receiver Holding Register */
#define REG_usart2_THR          (0x4009801CU) /**< \brief (usart2) Transmitter Holding Register */
#define REG_usart2_BRGR          (0x40098020U) /**< \brief (usart2) Baud Rate Generator Register */
#define REG_usart2_RTOR          (0x40098024U) /**< \brief (usart2) Receiver Time-out Register */
#define REG_usart2_TTGR          (0x40098028U) /**< \brief (usart2) Transmitter Timeguard Register */
#define REG_usart2_FIDI          (0x40098040U) /**< \brief (usart2) FI DI Ratio Register */
#define REG_usart2_NER          (0x40098044U) /**< \brief (usart2) Number of Errors Register */
#define REG_usart2_IF          (0x4009804CU) /**< \brief (usart2) IrDA Filter Register */
#define REG_usart2_MAN          (0x40098050U) /**< \brief (usart2) Manchester Encoder Decoder Register */
#define REG_usart2_WPMR          (0x400980E4U) /**< \brief (usart2) Write Protect Mode Register */
#define REG_usart2_WPSR          (0x400980E8U) /**< \brief (usart2) Write Protect Status Register */
#define REG_usart2_RPR          (0x40098100U) /**< \brief (usart2) Receive Pointer Register */
#define REG_usart2_RCR          (0x40098104U) /**< \brief (usart2) Receive Counter Register */
#define REG_usart2_TPR          (0x40098108U) /**< \brief (usart2) Transmit Pointer Register */
#define REG_usart2_TCR          (0x4009810CU) /**< \brief (usart2) Transmit Counter Register */
#define REG_usart2_RNPR          (0x40098110U) /**< \brief (usart2) Receive Next Pointer Register */
#define REG_usart2_RNCR          (0x40098114U) /**< \brief (usart2) Receive Next Counter Register */
#define REG_usart2_TNPR          (0x40098118U) /**< \brief (usart2) Transmit Next Pointer Register */
#define REG_usart2_TNCR          (0x4009811CU) /**< \brief (usart2) Transmit Next Counter Register */
#define REG_usart2_PTCR          (0x40098120U) /**< \brief (usart2) Transfer Control Register */
#define REG_usart2_PTSR          (0x40098124U) /**< \brief (usart2) Transfer Status Register */
#else
#define REG_usart2_CR (*(WoReg*)0x40098000U) /**< \brief (usart2) Control Register */
#define REG_usart2_MR (*(RwReg*)0x40098004U) /**< \brief (usart2) Mode Register */
#define REG_usart2_IER (*(WoReg*)0x40098008U) /**< \brief (usart2) Interrupt Enable Register */
#define REG_usart2_IDR (*(WoReg*)0x4009800CU) /**< \brief (usart2) Interrupt Disable Register */
#define REG_usart2_IMR (*(RoReg*)0x40098010U) /**< \brief (usart2) Interrupt Mask Register */
#define REG_usart2_CSR (*(RoReg*)0x40098014U) /**< \brief (usart2) Channel Status Register */
#define REG_usart2_RHR (*(RoReg*)0x40098018U) /**< \brief (usart2) Receiver Holding Register */
#define REG_usart2_THR (*(WoReg*)0x4009801CU) /**< \brief (usart2) Transmitter Holding Register */
#define REG_usart2_BRGR (*(RwReg*)0x40098020U) /**< \brief (usart2) Baud Rate Generator Register */
#define REG_usart2_RTOR (*(RwReg*)0x40098024U) /**< \brief (usart2) Receiver Time-out Register */
#define REG_usart2_TTGR (*(RwReg*)0x40098028U) /**< \brief (usart2) Transmitter Timeguard Register */
#define REG_usart2_FIDI (*(RwReg*)0x40098040U) /**< \brief (usart2) FI DI Ratio Register */
#define REG_usart2_NER (*(RoReg*)0x40098044U) /**< \brief (usart2) Number of Errors Register */
#define REG_usart2_IF (*(RwReg*)0x4009804CU) /**< \brief (usart2) IrDA Filter Register */
#define REG_usart2_MAN (*(RwReg*)0x40098050U) /**< \brief (usart2) Manchester Encoder Decoder Register */
#define REG_usart2_WPMR (*(RwReg*)0x400980E4U) /**< \brief (usart2) Write Protect Mode Register */
#define REG_usart2_WPSR (*(RoReg*)0x400980E8U) /**< \brief (usart2) Write Protect Status Register */
#define REG_usart2_RPR (*(RwReg*)0x40098100U) /**< \brief (usart2) Receive Pointer Register */
#define REG_usart2_RCR (*(RwReg*)0x40098104U) /**< \brief (usart2) Receive Counter Register */
#define REG_usart2_TPR (*(RwReg*)0x40098108U) /**< \brief (usart2) Transmit Pointer Register */
#define REG_usart2_TCR (*(RwReg*)0x4009810CU) /**< \brief (usart2) Transmit Counter Register */
#define REG_usart2_RNPR (*(RwReg*)0x40098110U) /**< \brief (usart2) Receive Next Pointer Register */
#define REG_usart2_RNCR (*(RwReg*)0x40098114U) /**< \brief (usart2) Receive Next Counter Register */
#define REG_usart2_TNPR (*(RwReg*)0x40098118U) /**< \brief (usart2) Transmit Next Pointer Register */
#define REG_usart2_TNCR (*(RwReg*)0x4009811CU) /**< \brief (usart2) Transmit Next Counter Register */
#define REG_usart2_PTCR (*(WoReg*)0x40098120U) /**< \brief (usart2) Transfer Control Register */
#define REG_usart2_PTSR (*(RoReg*)0x40098124U) /**< \brief (usart2) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3U_usart2_INSTANCE_ */
