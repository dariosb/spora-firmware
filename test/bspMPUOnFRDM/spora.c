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
 *  \file       spora.c
 *  \brief      Simple test app for Spora BSP on FRDMKL03.
 *
 *  \ingroup    bsp_test
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
#include "spora.h"
#include "mpu9250.h"
#include "fsl_debug_console.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static bool spora_running = false;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
spora_wakeup(void)
{
    spora_running = true;
}


int16_t emaFilter_LowPass(int16_t new, int16_t last, uint8_t alpha)
{
	int16_t out;

    if(alpha == 0)
        return new;

    out = (new / alpha);
    out += last;
    out -= (last / alpha);
    return out;
}

Mpu9250_data_st data_fil;

void
spora_task(void)
{
    Mpu9250_data_st data;

    if (!spora_running)
    {
        return;
    }

    spora_running = false;

    mpu9250_read(&data);

    /* temp[�C] = (temp / 333.87) + 21 */
    PRINTF("Temperature: %i\r\n", data.temp); 

    PRINTF("MPU9250_INT_STATUS: 0x%x\r\n", data.status);
    PRINTF("\tAcc: %i\t%i\t%i\r\n", data.ax, data.ay, data.az );
    PRINTF("\tGyr: %i\t%i\t%i\r\n", data.gx, data.gy, data.gz );

    PRINTF("AK8963_ST1: 0x%x\r\n", data.magnet);
    PRINTF("\tMag: %i\t%i\t%i\r\n", data.mx, data.my, data.mz);

    data_fil.mx = emaFilter_LowPass(data.mx, data_fil.mx, 2);
    data_fil.my = emaFilter_LowPass(data.my, data_fil.my, 2);
    data_fil.mz = emaFilter_LowPass(data.mz, data_fil.mz, 2);

    PRINTF("\tFMag: %i\t%i\t%i\r\n", data_fil.mx, data_fil.my, data_fil.mz);

}

/* ------------------------------ End of file ------------------------------ */
