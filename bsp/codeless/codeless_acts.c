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
 *  \file       codeless_act.c
 *  \brief      Murata BLE Codeless AT command SSP´ actions routines.
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

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "codeless_acts.h"
#include "codeless_tree.h"

/* ----------------------------- Local macros ------------------------------ */
#define rxBufferEnd     (rxBuffer+sizeof(rxBuffer)/sizeof(char)-1)

/* ------------------------------- Constants ------------------------------- */
#define CLESS_RXBUFF_SIZE   20

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static Codeless_rcvMsgHook rcv_cb;
static char rxBuffer[CLESS_RXBUFF_SIZE];
static char *prx;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
codeless_sspInit(Codeless_rcvMsgHook p)
{
    rcv_cb = p;
	ssp_init(&root);
    prx = rxBuffer;
}



char inSync = 0;

void
cmdOk(unsigned char pos)
{
    inSync = 1;
}

void
cmdError(unsigned char pos)
{

}

void
inRPrint(unsigned char data)
{

}

void
rPrintOk(unsigned char pos)
{

}

void
gapStatusCollect(unsigned char data)
{

}

void
gapStatusOk(unsigned char data)
{

}

void
rcvCollect(unsigned char data)
{
    if(prx < rxBufferEnd)
        *prx++ = data;
}

void
rcvOk(unsigned char data)
{
    *prx = '\0';
    prx=rxBuffer;
    (*rcv_cb)(rxBuffer);

}

/* ------------------------------ End of file ------------------------------ */
