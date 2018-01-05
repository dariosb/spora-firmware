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
 *  \file       mpu9250.c
 *  \brief      MPU9250 device routines.
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
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

#include "bsp.h"
#include "mpu9250.h"
#include "spora.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
EXT_WAKE_UP_irqEnable(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinInterruptConfig(BOARD_EXT_WAKE_UP_PORT,
                               BOARD_EXT_WAKE_UP_GPIO_PIN,
                               kPORT_InterruptRisingEdge);

    EnableIRQ(BOARD_EXT_WAKE_UP_IRQ);

    GPIO_PinInit(BOARD_EXT_WAKE_UP_GPIO,
                 BOARD_EXT_WAKE_UP_GPIO_PIN,
                 &gpio_config);
}

/* ---------------------------- Global functions --------------------------- */
void
BOARD_EXT_WAKE_UP_IRQ_Handler(void)
{
    GPIO_PortClearInterruptFlags(BOARD_EXT_WAKE_UP_GPIO,
                                 1U << BOARD_EXT_WAKE_UP_GPIO_PIN);

    LED_RED_TOGGLE();
    spora_wakeup();
}

void
mpu9250_read(Mpu9250_data_st *p)
{
    p->status = mpu9250_readByte(INT_STATUS);

    p->axh = mpu9250_readByte(ACCEL_XOUT_H);
    p->axl = mpu9250_readByte(ACCEL_XOUT_L);

    p->magnet = ak8963_readByte(AK8963_ST1);
}

bool
mpu9250_init(void)
{
    uint8_t status0_value = 0;
    uint8_t aux;

    I2C_init();
    if (I2C_readAccelWhoAmI(WHO_AM_I_MPU9250, MPU9250_WHOAMI) != true)
    {
        return false;
    }

    status0_value = mpu9250_readByte(INT_STATUS);
    PRINTF("\r\nINT_STATUS: %x.\r\n",status0_value);

    aux = mpu9250_readByte(GYRO_CONFIG);
    PRINTF("\r\nGYRO_CONFIG (must be 0x18): 0x%x.\r\n",aux);

    /* MPU general settings */

    mpu9250_writeByte(GYRO_CONFIG, GYRO_FULL_SCALE_2000_DPS);

    aux = mpu9250_readByte(GYRO_CONFIG);
    PRINTF("\r\nGYRO_CONFIG (must be 0x18): 0x%x.\r\n",aux);

    /* settup accelerometers range */
    mpu9250_writeByte(ACCEL_CONFIG, ACC_FULL_SCALE_16_G);
    aux = mpu9250_readByte(ACCEL_CONFIG);
    PRINTF("\r\nACCEL_CONFIG (must be 0x18): 0x%x.\r\n",aux);

    /*
     * INT Pin/Bypass:
     *      - bit 1 I2C bypass mode enable.
     *      - bit 5 active until read.
     */
    aux = mpu9250_readByte(INT_PIN_CFG);
    aux |= 0x22;
    mpu9250_writeByte(INT_PIN_CFG, aux);
    aux = mpu9250_readByte(INT_PIN_CFG);
    PRINTF("\r\nINT_PIN_CFG(must be 0x22): %x.\r\n",aux);

    /* Test AK8963 reading Who am I */
    aux = ak8963_readByte(WHO_AM_I_AK8963);
    PRINTF("\r\nWHO_AM_I_AK8963: 0x%x", aux);

    /* Request first magnetometer single measurement */
    ak8963_writeByte(AK8963_CNTL, 0x01);
    aux = ak8963_readByte(AK8963_CNTL);
    PRINTF("\r\nAK8963_CNTL: 0x%x.\r\n",aux);

    EXT_WAKE_UP_irqEnable();

    /* Step 1: */
    /* Verify that is runnig */
    aux = mpu9250_readByte(PWR_MGMT_1);
    aux &= 0x8F; /*clear bits 4 5 y 6 */
    mpu9250_writeByte(PWR_MGMT_1,aux);

    /* Enable Axis */
    aux = mpu9250_readByte(PWR_MGMT_2);
    aux = 0x00; /*clear all bits */
    mpu9250_writeByte(PWR_MGMT_2,aux);

    /* Step 2: */
    /* Setup bandwidth */
    aux = mpu9250_readByte(ACCEL_CONFIG2);
    aux &= 0xF0;
    aux |= 0x09;
    mpu9250_writeByte(ACCEL_CONFIG2, aux);

    /* Step 3: */
    /* Enable movement interrupt */
    aux = mpu9250_readByte(INT_ENABLE);
    aux = 0x40;
    /*aux = 0xC0; */
    mpu9250_writeByte(INT_ENABLE, aux);

    /* Step 4: */
    /* Enable movement detection */
    aux = mpu9250_readByte(MOT_DETECT_CTRL);
    aux |= 0xC0;
    mpu9250_writeByte(MOT_DETECT_CTRL, aux);

    /* Step 5: */
    /* Setup movemente detection threshold */
    aux = mpu9250_readByte(WOM_THR);
    aux = 0xFF;
    mpu9250_writeByte(WOM_THR, aux);

    /* Step 6: */
    aux = mpu9250_readByte(LP_ACCEL_ODR);
    aux = 0x08;
    mpu9250_writeByte(LP_ACCEL_ODR, aux);

    /* Step 7: */
    aux = mpu9250_readByte(PWR_MGMT_1);
    aux |= 0x20; /*or bit 5 */
    mpu9250_writeByte(PWR_MGMT_1, aux);

    return true;
}

/* ------------------------------ End of file ------------------------------ */
