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
 *  \file       codeless.h
 *  \brief      Murata BLE Codeless AT command definition.
 *
 *  \ingroup    ble
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
#ifndef __CODELESS_CMD_H__
#define __CODELESS_CMD_H__

/* ----------------------------- Include files ----------------------------- */
#include "fsl_common.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define CLESS_CMD_TBL(name)				const CodelessCmdTbl name[] = {
//#define CLESS_CMD(cmd,tout,delay)  {(cmd), RKH_TIM_MS(tout), RKH_TIM_MS(delay)},
#define CLESS_CMD(cmd,tout,delay)       {(cmd), tout, delay},
#define CLESS_CMD_ENDTBL				{ NULL, 0, 0 } }

/* -------------------------------- Constants ------------------------------ */
#define CODELESS_OK         "\r\nOK\r\n"
#define CODELESS_ERROR      "\r\nERROR\r\n"
#define SPORA_RX_MSJ_START  "+RCV="
#define SPORA_RX_MSJ_END    "\\EOSM\r\n"

/*
 * Codeless AT Command Table index
 */
typedef enum
{
    CLESS_SYNC,
    CLESS_RESET,
    CLESS_SEND,
    CLESS_GSTATUS,
    CLESS_CMDS
}CodelessCmdIx;

#define ClessSync        codelessCmdTbl[CLESS_SYNC]
#define ClessReset       codelessCmdTbl[CLESS_RESET]
#define ClessSendData    codelessCmdTbl[CLESS_SEND]
#define ClessGapStatus   codelessCmdTbl[CLESS_GSTATUS]

/* ------------------------------- Data types ------------------------------ */

typedef struct
{
	const char* cmd;
#if 0
	RKH_TNT_T ntick;
	RKH_TNT_T delay;
#else
    unsigned char tout;
    unsigned char delay;
#endif

}CodelessCmdTbl;

/* -------------------------- External variables --------------------------- */
extern const CodelessCmdTbl codelessCmdTbl[];

/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
