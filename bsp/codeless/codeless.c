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
 *  \file       codeless.c
 *  \brief      Murata BLE Codeless routines.
 *
 *  \ingroup    ble
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.5  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Bali�a       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "fsl_lpuart.h"
#include "bsp.h"
#include "codeless.h"
#include "codeless_tree.h"
#include "ssp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static Codeless_rcvMsgHook rcv_cb;

/* ----------------------- Local function prototypes ----------------------- */
void CODELESS_LPUART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(CODELESS_LPUART))
    {
        data = LPUART_ReadByte(CODELESS_LPUART);
        ssp_do_search(data);
    }
    /* Add for ARM errata 838869, affects Cortex-M4, 
     * Cortex-M4F Store immediate overlapping exception return operation 
     * might vector to incorrect interrupt
     */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif    
}

static
void
lpuart_init(void)
{
    lpuart_config_t config;

    CLOCK_SetLpuart0Clock(0x1U);
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kLPUART_ParityDisabled;
     * config.stopBitCount = kLPUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    LPUART_GetDefaultConfig(&config);

    config.baudRate_Bps = CODELESS_LPUART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(CODELESS_LPUART, &config, CODELESS_LPUART_CLK_FREQ);    

    /* Enable RX interrupt. */
    LPUART_EnableInterrupts(CODELESS_LPUART, 
                            kLPUART_RxDataRegFullInterruptEnable);
    EnableIRQ(CODELESS_LPUART_IRQn);
}

/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
bool
codeless_init(Codeless_rcvMsgHook p)
{
    rcv_cb = p;

    ssp_init(&root);

    lpuart_init();

    LPUART_WriteBlocking(CODELESS_LPUART, "AT\r", 3);

    return true;
}

void
codeless_reset(void)
{

}

void
codeles_advertisementStart(void)
{

}

void
codeles_advertisementStop(void)
{

}

void codeles_gapDisconnect(void)
{

}

void codeles_sendData(char *p)
{

}

/* ------------------------------ End of file ------------------------------ */
