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
 *  \file       blemgr.c
 *  \brief      BLE Connection Manager.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.28  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña  db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blemgr.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define INIT_TIME            RKH_TIME_SEC(5)
#define SYNC_TIME            RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct BleMgr BleMgr;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE waitSync, reseting, failure, 
                     disconnected, connected, waitConnStatus,
                     advertisementOff;

RKH_DCLR_COMP_STATE init, advertisementOn;

/* ........................ Declares initial action ........................ */
static void bleInit(BleMgr *const me);

/* ........................ Declares effect actions ........................ */
static void sendReset(BleMgr *const me, RKH_EVT_T *pe);
static void bleError(BleMgr *const me, RKH_EVT_T *pe);
static void sendGetConnStatus(BleMgr *const me, RKH_EVT_T *pe);
static void bleIsDisconnected(BleMgr *const me, RKH_EVT_T *pe);
static void bleIsConnected(BleMgr *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void sendSync(BleMgr *const me);
static void sendAdvertisementOff(BleMgr *const me);

/* ......................... Declares exit actions ......................... */
static void sendAdvertisementOn(BleMgr *const me);

/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_COMP_REGION_STATE(init, NULL, NULL,  RKH_ROOT, &waitSync, NULL,
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL );
RKH_CREATE_TRANS_TABLE(init)
    RKH_TRREG(evInitTout, NULL, bleError, &failure),
    RKH_TRREG(evOk, NULL, sendGetConnStatus, &advertisementOn),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitSync, sendSync, NULL, &init, NULL);
RKH_CREATE_TRANS_TABLE(waitSync)
    RKH_TRINT(evSyncTout, NULL, sendSync),
    RKH_TRREG(evOk, NULL, sendReset, &reseting),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(reseting, NULL, NULL, &init, NULL);
RKH_CREATE_TRANS_TABLE(reseting)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(failure, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(failure)
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(advertisementOn, NULL, NULL, RKH_ROOT,
                             &disconnected, NULL,
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL );
RKH_CREATE_TRANS_TABLE(advertisementOn)
    RKH_TRREG(evStopAdvertisement, NULL, NULL, &advertisementOff),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(disconnected, NULL, NULL, &advertisementOn, NULL);
RKH_CREATE_TRANS_TABLE(disconnected)
    RKH_TRREG(evDisconnectedTout, NULL, NULL, &advertisementOff),
    RKH_TRREG(evConnStatusTout, NULL, sendGetConnStatus, &waitConnStatus),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitConnStatus, NULL, NULL, &advertisementOn, NULL);
RKH_CREATE_TRANS_TABLE(waitConnStatus)
    RKH_TRREG(evDisconnected, NULL, bleIsDisconnected, &disconnected),
    RKH_TRREG(evConnected, NULL, bleIsConnected, &connected),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(connected, NULL, NULL, &advertisementOn, NULL);
RKH_CREATE_TRANS_TABLE(connected)
    RKH_TRREG(evConnStatusTout, NULL, sendGetConnStatus, &waitConnStatus),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(advertisementOff, 
                       sendAdvertisementOff, sendAdvertisementOn,
                       RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(advertisementOff)
    RKH_TRREG(evStartAdvertisement, NULL, NULL, &advertisementOn),
RKH_END_TRANS_TABLE
/* ............................. Active object ............................. */
struct BleMgr
{
    RKH_SMA_T sma;
    RKH_TMR_T tmr1;
    RKH_TMR_T tmr2;
};

RKH_SMA_CREATE(BleMgr, bleMgr, 0, HCAL, &init, bleInit, NULL);
RKH_SMA_DEF_PTR(bleMgr);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/*
 *  Declare and allocate the 'e_tout' event.
 *  The 'e_tout' event with TIMEOUT signal never changes, so it can be
 *  statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */
static RKH_ROM_STATIC_EVENT(e_tmr1, evInitTout);
static RKH_ROM_STATIC_EVENT(e_tmr2, evSyncTout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
bleInit(BleMgr *const me)
{
    RKH_TMR_INIT(&me->tmr1, &e_tmr1, NULL);
    RKH_TMR_INIT(&me->tmr2, &e_tmr2, NULL);

    RKH_TMR_ONESHOT(&me->tmr1,  RKH_UPCAST(RKH_SMA_T, me), INIT_TIME);
}

/* ............................ Effect actions ............................. */
static void
sendReset(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

static void
bleError(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
    bsp_ledOn();
}

static void
sendGetConnStatus(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

static void
bleIsDisconnected(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

static void
bleIsConnected(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

/* ............................. Entry actions ............................. */
static void
sendSync(BleMgr *const me)
{
    (void)me;
    RKH_TMR_ONESHOT(&me->tmr1,  RKH_UPCAST(RKH_SMA_T, me), SYNC_TIME);
}

static void
sendAdvertisementOff(BleMgr *const me)
{
    (void)me;
}

/* ............................. Exit actions .............................. */
static void
sendAdvertisementOn(BleMgr *const me)
{
    (void)me;
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
