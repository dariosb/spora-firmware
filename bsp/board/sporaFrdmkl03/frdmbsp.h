/*
 *  --------------------------------------------------------------------------
 *
 *                                    Spora
 *                                -------------
 *
 *                  Coin-sized programmable multi-sensor node
 *
 *                      Copyright (C) 2018  Enye Tech.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  Spora is an open-source, programmable multi-sensor node,
 *  specifically designed for wearables but with endless opportunities.
 *
 *  Spora is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  Spora is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  Spora web site: http://www.sporaio.com
 *  e-mail:         hello@sporaio.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       sporafrdm.h
 *  \brief      Board Support Package Spora on FRDMKL03 kit.
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.5  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Module -------------------------------- */

#ifndef __SPORAFRDM_H__
#define __SPORAFRDM_H__

/* ----------------------------- Include files ----------------------------- */
#include "board.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#ifdef BOARD_NAME
#undef BOARD_NAME
#define BOARD_NAME "SPORA-FRDMKL03"
#endif

#ifndef BOARD_EXT_WAKE_UP_GPIO
#define BOARD_EXT_WAKE_UP_GPIO          GPIOB
#endif
#ifndef BOARD_EXT_WAKE_UP_PORT
#define BOARD_EXT_WAKE_UP_PORT          PORTB
#endif
#ifndef BOARD_EXT_WAKE_UP_GPIO_PIN
#define BOARD_EXT_WAKE_UP_GPIO_PIN      5U
#endif
#define BOARD_EXT_WAKE_UP_IRQ           PORTB_IRQn
#define BOARD_EXT_WAKE_UP_IRQ_Handler   PORTB_IRQHandler
#define BOARD_EXT_WAKE_UP_NAME          "EXT_WAKE_UP"

#ifndef BOARD_PUSH_BUTTON_GPIO
#define BOARD_PUSH_BUTTON_GPIO          GPIOA
#endif
#ifndef BOARD_PUSH_BUTTON_PORT
#define BOARD_PUSH_BUTTON_PORT          PORTA
#endif
#ifndef BOARD_PUSH_BUTTON_GPIO_PIN
#define BOARD_PUSH_BUTTON_GPIO_PIN      7U
#endif
#define BOARD_PUSH_BUTTON_IRQ           PORTA_IRQn
#define BOARD_PUSH_BUTTON_IRQ_Handler   PORTA_IRQHandler
#define BOARD_PUSH_BUTTON_NAME          "PUSH_BUTTON"

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
