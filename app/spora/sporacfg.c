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
 *  \file       sporacfg.c
 *  \brief      This module handle configuration message an settings.
 *
 *  \ingroup    sporaCfg
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
#include "fsl_common.h"
#include "sporacfg.h"
#include "rwflash.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static SporaCfg *sporaCfg;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
spora_initCfg(void)
{
    if( rwflash_init() != true )
    {
        return;
    }

    if( rwflash_verify() != true )
    {
        rwflash_setDefaults();
    }

    sporaCfg = &RWFlashROM->cfg;
}

void
spora_getCfg(SporaCfg *p)
{
    *p = *sporaCfg;
}

uint8_t
spora_getCfg_motionThr(void)
{
    return sporaCfg->motionThr;
}

char *
spora_getCfg_name(void)
{
    return sporaCfg->name;
}

void
spora_setCfg(SporaCfg *p)
{
    /* Working On It */
    //*sporaCfg = *p;
}

/* ------------------------------ End of file ------------------------------ */
