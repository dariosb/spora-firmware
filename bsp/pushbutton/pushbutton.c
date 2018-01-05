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
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "bsp.h"
#include "fsl_gpio.h"
#include "spora.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
BOARD_PUSH_BUTTON_IRQ_Handler(void)
{
    GPIO_PortClearInterruptFlags(BOARD_PUSH_BUTTON_GPIO,
                                 1U << BOARD_PUSH_BUTTON_GPIO_PIN);

    spora_wakeup();
}

void
pushbutton_init(void)
{
    port_pin_config_t sw_port_config = {kPORT_PullUp,
                                        kPORT_SlowSlewRate,
                                        kPORT_PassiveFilterDisable,
                                        kPORT_LowDriveStrength,
                                        kPORT_MuxAsGpio};

    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinConfig(BOARD_PUSH_BUTTON_PORT,
                      BOARD_PUSH_BUTTON_GPIO_PIN,
                      &sw_port_config);

    PORT_SetPinInterruptConfig(BOARD_PUSH_BUTTON_PORT,
                               BOARD_PUSH_BUTTON_GPIO_PIN,
                               kPORT_InterruptFallingEdge);

    EnableIRQ(BOARD_PUSH_BUTTON_IRQ);

    GPIO_PinInit(BOARD_PUSH_BUTTON_GPIO,
                 BOARD_PUSH_BUTTON_GPIO_PIN,
                 &sw_config);
}

/* ------------------------------ End of file ------------------------------ */
