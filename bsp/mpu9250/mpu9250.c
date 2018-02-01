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
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "bsp.h"
#include "mpu9250.h"
#include "spora.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}InstantMotion;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
#if defined(RKH_USE_TRC_SENDER)
static rui8_t mpu9250;
#endif

static RKH_ROM_STATIC_EVENT(e_motion, evMotionDetect);

static InstantMotion motion;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
EXT_WAKE_UP_irqEnable(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinInterruptConfig(EXT_WAKE_UP_PORT,
                               EXT_WAKE_UP_GPIO_PIN,
//                               kPORT_InterruptRisingEdge);
							   kPORT_InterruptLogicOne);

    EnableIRQ(EXT_WAKE_UP_IRQ);

    GPIO_PinInit(EXT_WAKE_UP_GPIO,
                 EXT_WAKE_UP_GPIO_PIN,
                 &gpio_config);
}

/* ---------------------------- Global functions --------------------------- */
void
EXT_WAKE_UP_IRQ_Handler(void)
{
	uint8_t status;

    GPIO_PortClearInterruptFlags(EXT_WAKE_UP_GPIO,
                                 1U << EXT_WAKE_UP_GPIO_PIN);

    status = mpu9250_readByte(INT_STATUS);

    if((status & WOM_INT_STATUS_MASK) == 0)
    	return;

    motion.x = mpu9250_readByte(ACCEL_XOUT_H) << 8 |
            mpu9250_readByte(ACCEL_XOUT_L);
    
    motion.y = mpu9250_readByte(ACCEL_YOUT_H) << 8 |
            mpu9250_readByte(ACCEL_YOUT_L);
    
    motion.z = mpu9250_readByte(ACCEL_ZOUT_H) << 8 |
            mpu9250_readByte(ACCEL_ZOUT_L);
    
    mpu9250_readByte(INT_STATUS);

    RKH_SMA_POST_FIFO(spora, &e_motion, &mpu9250);
}

void
mpu9250_read(Mpu9250_data_st *p)
{
    p->temp = mpu9250_readByte(TEMP_OUT_H) << 8 |
              mpu9250_readByte(TEMP_OUT_L);

    p->ax = mpu9250_readByte(ACCEL_XOUT_H) << 8 |
            mpu9250_readByte(ACCEL_XOUT_L);
    
    p->ay = mpu9250_readByte(ACCEL_YOUT_H) << 8 |
            mpu9250_readByte(ACCEL_YOUT_L);
    
    p->az = mpu9250_readByte(ACCEL_ZOUT_H) << 8 |
            mpu9250_readByte(ACCEL_ZOUT_L);
    
    p->gx = mpu9250_readByte(GYRO_XOUT_H) << 8 |
            mpu9250_readByte(GYRO_XOUT_L);
    
    p->gy = mpu9250_readByte(GYRO_YOUT_H) << 8 |
            mpu9250_readByte(GYRO_YOUT_L);
    
    p->gz = mpu9250_readByte(GYRO_ZOUT_H) << 8 |
            mpu9250_readByte(GYRO_ZOUT_L);
    
    p->status = mpu9250_readByte(INT_STATUS);

    p->magnet = ak8963_readByte(AK8963_ST1);

    if(p->magnet != 0x00)
    {
        p->mx = ak8963_readByte(AK8963_XOUT_H) << 8 |
                ak8963_readByte(AK8963_XOUT_L);

        p->my = ak8963_readByte(AK8963_YOUT_H) << 8 |
                ak8963_readByte(AK8963_YOUT_L);

        p->mz = ak8963_readByte(AK8963_ZOUT_H) << 8 |
                ak8963_readByte(AK8963_ZOUT_L);

        ak8963_writeByte(AK8963_CNTL, 0x11);
    }

}

bool
mpu9250_init(void)
{
    uint8_t aux;

    I2C_init();
    if (I2C_readAccelWhoAmI(WHO_AM_I_MPU9250, MPU9250_WHOAMI) != true)
    {
        return false;
    }

    /* MPU reset */
    mpu9250_writeByte( PWR_MGMT_1, 0x80 );

    aux = mpu9250_readByte(INT_STATUS);
    /* MPU general settings */
    mpu9250_writeByte(GYRO_CONFIG, GYRO_FULL_SCALE_250_DPS);

    aux = mpu9250_readByte(GYRO_CONFIG);
    /* settup accelerometers range */
    mpu9250_writeByte(ACCEL_CONFIG, ACC_FULL_SCALE_16_G);
    aux = mpu9250_readByte(ACCEL_CONFIG);

    /*
     * INT Pin/Bypass:
     *      - bit 1 I2C bypass mode enable.
     *      - bit 5 active until read.
     */
    aux = mpu9250_readByte(INT_PIN_CFG);
    aux |= 0x22;
    mpu9250_writeByte(INT_PIN_CFG, aux);
    aux = mpu9250_readByte(INT_PIN_CFG);

    /* Test AK8963 reading Who am I */
    aux = ak8963_readByte(WHO_AM_I_AK8963);

    /* Sets magnetometer in 16bit continuos mode */
    ak8963_writeByte(AK8963_CNTL, 0x11);
    aux = ak8963_readByte(AK8963_CNTL);

    EXT_WAKE_UP_irqEnable();

    /* Step 1: */
    /* Verify that is runnig */
    aux = mpu9250_readByte(PWR_MGMT_1);
    aux &= 0x8F; /*clear bits 4 5 y 6 */
    mpu9250_writeByte(PWR_MGMT_1,aux);

    /* Disable Accel an Gyro */
    mpu9250_writeByte(PWR_MGMT_2,0x6C);

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
//    mpu9250_writeByte(MOT_DETECT_CTRL, aux);

    /* Step 5: */
    /* Setup Motion detection threshold */
    aux = mpu9250_readByte(WOM_THR);
    aux = 0xFF;
    mpu9250_writeByte(WOM_THR, aux);

    /* Step 6: */
    /* Set Frequency of Wake-up */
    aux = mpu9250_readByte(LP_ACCEL_ODR);
    aux = 0x08;
    mpu9250_writeByte(LP_ACCEL_ODR, aux);

    /* Step 7: */
    /* Enable cycle mode */
    aux = mpu9250_readByte(PWR_MGMT_1);
    aux |= 0x20;
    mpu9250_writeByte(PWR_MGMT_1, aux);

    /* Enable Accel an Gyro */
    mpu9250_writeByte(PWR_MGMT_2,0x00);

    aux = mpu9250_readByte(MOT_DETECT_CTRL);
    aux |= 0xC0;
    mpu9250_writeByte(MOT_DETECT_CTRL, aux);

    return true;
}

/* ------------------------------ End of file ------------------------------ */
