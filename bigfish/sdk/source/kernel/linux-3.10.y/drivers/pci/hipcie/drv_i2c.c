/*  extdrv/interface/i2c/hi_i2c.c
 *
 * Copyright (c) 2006 Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 * History:
 *      19-April-2006 create this file
 */
#include <linux/device.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/poll.h>
#include <mach/hardware.h>
#include <linux/interrupt.h>
#include <linux/slab.h>

#include "hi_drv_i2c.h"
#include "drv_i2c.h"

#define I2C_WAIT_TIME_OUT 0x1000

#define I2C_WRITE_REG(Addr, Value) ((*(volatile unsigned int *)(Addr)) = (Value))
#define I2C_READ_REG(Addr) (*(volatile unsigned int *)(Addr))

//static UMAP_DEVICE_S   g_I2cRegisterData;
//static atomic_t g_I2cCount = ATOMIC_INIT(0);
static struct semaphore g_I2cMutex;

static int i2cState = 0;

static unsigned int g_I2cKernelAddr[HI_STD_I2C_NUM];
static unsigned int g_aI2cRate[HI_STD_I2C_NUM] = {0};

static volatile void *crg = (void*)IO_ADDRESS(0xf8a2206c);


static void I2C_DRV_SetRate(unsigned int I2cNum, unsigned int I2cRate)
{
    unsigned int Value = 0;
    unsigned int SclH = 0;
    unsigned int SclL = 0;

    //HI_CHIP_TYPE_E enChipType;
    //unsigned int u32ChipVersion;
    unsigned int SysClock = I2C_DFT_SYSCLK;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        return;
    }

    g_aI2cRate[I2cNum] = I2cRate;

    /* read i2c I2C_CTRL register*/
    Value = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_CTRL_REG));

    /* close all i2c  interrupt */
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_CTRL_REG), (Value & (~I2C_UNMASK_TOTAL)));

    //HI_DRV_SYS_GetChipVersion( &enChipType, &u32ChipVersion );
    /*if (HI_CHIP_TYPE_HI3716C == g_enChipType)
    {
        SysClock = I2C_3716C_SYSCLK;
    }*/

    SclH = (SysClock / (I2cRate * 2)) / 2 - 1;
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_SCL_H_REG), SclH);

    SclL = (SysClock / (I2cRate * 2)) / 2 - 1;
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_SCL_L_REG), SclL);

    /*enable i2c interrupt, resume original  interrupt*/
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_CTRL_REG), Value);

    return;
}

static int I2C_DRV_WaitWriteEnd(unsigned int I2cNum)
{
    unsigned int I2cSrReg;
    unsigned int i = 0;

    do
    {
        I2cSrReg = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_SR_REG));

        if (i > I2C_WAIT_TIME_OUT)
        {
            HI_ERR_I2C("wait write data timeout!\n");
            return HI_FAILURE;
        }

        i++;
    } while ((I2cSrReg & I2C_OVER_INTR) != I2C_OVER_INTR);

    if (I2cSrReg & I2C_ACK_INTR)
    {
        HI_ERR_I2C("wait write data timeout!\n");
        return HI_FAILURE;
    }

    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_ICR_REG), I2C_CLEAR_ALL);

    return 0;
}

static int I2C_DRV_WaitRead(unsigned int I2cNum)
{
    unsigned int I2cSrReg;
    unsigned int i = 0;

    do
    {
        I2cSrReg = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_SR_REG));

        if (i > I2C_WAIT_TIME_OUT)
        {
            HI_ERR_I2C("wait Read data timeout!\n");
            return HI_FAILURE;
        }

        i++;
    } while ((I2cSrReg & I2C_RECEIVE_INTR) != I2C_RECEIVE_INTR);

    return 0;
}

/*
add by Jiang Lei 2010-08-24
I2C write finished acknowledgement function
it use to e2prom device ,make sure it finished write operation.
i2c master start next write operation must waiting when it acknowledge e2prom write cycle finished.
 */
static int I2C_DRV_WriteConfig(unsigned int I2cNum, unsigned char I2cDevAddr)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int I2cSrReg;

    do
    {
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), (I2cDevAddr & WRITE_OPERATION));
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), (I2C_WRITE | I2C_START));

        j = 0;
        do
        {
            I2cSrReg = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_SR_REG));

            if (j > I2C_WAIT_TIME_OUT)
            {
                HI_ERR_I2C("wait write data timeout!\n");
                return HI_FAILURE;
            }

            j++;
        } while ((I2cSrReg & I2C_OVER_INTR) != I2C_OVER_INTR);

        I2cSrReg = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_SR_REG));
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_ICR_REG), I2C_CLEAR_ALL);

        i++;

        if (i > 0x200000) //I2C_WAIT_TIME_OUT)
        {
            HI_ERR_I2C("wait write ack ok timeout!\n");
            return HI_FAILURE;
        }
    } while ((I2cSrReg & I2C_ACK_INTR));

    return 0;
}

static int I2C_DRV_Write(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char *pData,
                     unsigned int DataLen, bool bWithStop)
{
    unsigned int i;

    //    unsigned long   IntFlag;
    unsigned int RegAddr;

    //local_irq_save(IntFlag);

    /*  clear interrupt flag*/
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_ICR_REG), I2C_CLEAR_ALL);

    /* send devide address */
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), (I2cDevAddr & WRITE_OPERATION));
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), (I2C_WRITE | I2C_START));

    if (I2C_DRV_WaitWriteEnd(I2cNum))
    {
        //local_irq_restore(IntFlag);
        //HI_ERR_I2C("wait write data timeout!%s, %d\n", __func__, __LINE__);
        return HI_ERR_I2C_WRITE_TIMEOUT;
    }

    /* send register address which will need to write */
    for (i = 0; i < I2cRegAddrByteNum; i++)
    {
        RegAddr = I2cRegAddr >> ((I2cRegAddrByteNum - i - 1) * 8);
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), RegAddr);

        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_WRITE);

        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!%s, %d\n", __func__, __LINE__);
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    /* send data */
    for (i = 0; i < DataLen; i++)
    {
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), (*(pData + i)));
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_WRITE);

        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!%s, %d\n", __func__, __LINE__);
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    if (bWithStop)
    {
        /*   send stop flag bit*/
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_STOP);
        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!%s, %d\n", __func__, __LINE__);
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    //local_irq_restore(IntFlag);

    return 0;
}

static int I2C_DRV_Read(unsigned int I2cNum, unsigned char I2cDevAddr, bool bSendSlave, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum,
                 unsigned char *pData, unsigned int DataLen)
{
    unsigned int dataTmp = 0xff;
    unsigned int i;

    //    unsigned long   IntFlag;
    unsigned int RegAddr;

    //local_irq_save(IntFlag);

    if (bSendSlave)
    {
        /* clear interrupt flag*/
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_ICR_REG), I2C_CLEAR_ALL);

        /* send devide address*/
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), (I2cDevAddr & WRITE_OPERATION));
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), (I2C_WRITE | I2C_START));

        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!\n");
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    /* send register address which will need to write*/
    for (i = 0; i < I2cRegAddrByteNum; i++)
    {
        RegAddr = I2cRegAddr >> ((I2cRegAddrByteNum - i - 1) * 8);
        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), RegAddr);

        I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_WRITE);

        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!\n");
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    /* send register address which will need to read */
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_TXR_REG), (I2cDevAddr | READ_OPERATION));
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_WRITE | I2C_START);

    if (I2C_DRV_WaitWriteEnd(I2cNum))
    {
        //local_irq_restore(IntFlag);
        return HI_ERR_I2C_WRITE_TIMEOUT;
    }

    /* repetitivily read data */
    for (i = 0; i < DataLen; i++)
    {
        /*  the last byte don't need send ACK*/
        if (i == (DataLen - 1))
        {
            I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), (I2C_READ | (~I2C_SEND_ACK)));
        }
        /*  if i2c master receive data will send ACK*/
        else
        {
            I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_READ);
        }

        if (I2C_DRV_WaitRead(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait read data timeout!\n");
            return HI_ERR_I2C_READ_TIMEOUT;
        }

        dataTmp = I2C_READ_REG((g_I2cKernelAddr[I2cNum] + I2C_RXR_REG));
        *(pData + i) = dataTmp & 0xff;

        if (I2C_DRV_WaitWriteEnd(I2cNum))
        {
            //local_irq_restore(IntFlag);
            //HI_ERR_I2C("wait write data timeout!\n");
            return HI_ERR_I2C_WRITE_TIMEOUT;
        }
    }

    /* send stop flag bit*/
    I2C_WRITE_REG((g_I2cKernelAddr[I2cNum] + I2C_COM_REB), I2C_STOP);
    if (I2C_DRV_WaitWriteEnd(I2cNum))
    {
        //local_irq_restore(IntFlag);
        //HI_ERR_I2C("wait write data timeout!\n");
        return HI_ERR_I2C_WRITE_TIMEOUT;
    }

    //local_irq_restore(IntFlag);

    return 0;
}

/*****************************************************************************/
static void HI_DRV_I2C_Open(void)
{
    int Ret;
    unsigned int i;

    if (1 == i2cState)
    {
        return;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return;
    }

    for (i = 0; i < HI_STD_I2C_NUM; i++)
    {
        /*disable all i2c interrupt*/
        I2C_WRITE_REG((g_I2cKernelAddr[i] + I2C_CTRL_REG), 0x0);

        /*  config scl clk rate*/
        I2C_DRV_SetRate(i, I2C_DFT_RATE);

        /*clear all i2c interrupt*/
        I2C_WRITE_REG((g_I2cKernelAddr[i] + I2C_ICR_REG), I2C_CLEAR_ALL);

        /*enable relative interrupt*/
        I2C_WRITE_REG((g_I2cKernelAddr[i] + I2C_CTRL_REG), (I2C_ENABLE | I2C_UNMASK_TOTAL | I2C_UNMASK_ALL));
    }

    i2cState = 1;

    up(&g_I2cMutex);
    return;
}

static int HI_DRV_I2C_Init(void)
{
    //HI_CHIP_TYPE_E enChipType;
    //unsigned int u32ChipVersion = 0;
    unsigned int u32RegVal = 0;
    sema_init(&g_I2cMutex, 1);


    g_I2cKernelAddr[0] = IO_ADDRESS(I2C0_PHY_ADDR);
    g_I2cKernelAddr[1] = IO_ADDRESS(I2C1_PHY_ADDR);
    g_I2cKernelAddr[2] = IO_ADDRESS(I2C2_PHY_ADDR);
    u32RegVal  = *(unsigned int *)crg;
    u32RegVal &= ~0x222222;
    u32RegVal |= 0x111111;
    *(unsigned int *)crg = u32RegVal;

    HI_DRV_I2C_Open();

    return 0;
}

static void HI_DRV_I2C_DeInit(void)
{
    unsigned int u32RegVal;

    u32RegVal  = *(unsigned int *)crg;
    u32RegVal |= 0x222222;
    *(unsigned int *)crg = u32RegVal;

    i2cState = 0;

    return;
}

static int HI_DRV_I2C_WriteConfig(unsigned int I2cNum, unsigned char I2cDevAddr)
{
    int Ret;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        HI_ERR_I2C("I2cNum(%d) is wrong, STD_I2C_NUM is %d\n", I2cNum, HI_STD_I2C_NUM);
        return HI_FAILURE;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return HI_FAILURE;
    }

    Ret = I2C_DRV_WriteConfig(I2cNum, I2cDevAddr);

    up(&g_I2cMutex);

    return Ret;
}

int HI_DRV_I2C_Write(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char *pData,
                        unsigned int DataLen)
{
    int Ret;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        HI_ERR_I2C("I2cNum(%d) is wrong, STD_I2C_NUM is %d\n", I2cNum, HI_STD_I2C_NUM);
        return HI_FAILURE;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return HI_FAILURE;
    }

    Ret = I2C_DRV_Write(I2cNum, I2cDevAddr, I2cRegAddr, I2cRegAddrByteNum, pData, DataLen, true);
    HI_INFO_I2C("Ret=0x%x, I2cNum=%d, DevAddr=0x%x, RegAddr=0x%x, Num=%d, Len=%d, data0=0x%x\n", Ret, I2cNum,
                I2cDevAddr, I2cRegAddr, I2cRegAddrByteNum, DataLen, pData[0]);

    up(&g_I2cMutex);

    return Ret;
}

static int HI_DRV_I2C_Write_NoSTOP(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum,
                               unsigned char *pData, unsigned int DataLen)
{
    int Ret;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        HI_ERR_I2C("I2cNum(%d) is wrong, STD_I2C_NUM is %d\n", I2cNum, HI_STD_I2C_NUM);
        return HI_FAILURE;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return HI_FAILURE;
    }

    Ret = I2C_DRV_Write(I2cNum, I2cDevAddr, I2cRegAddr, I2cRegAddrByteNum, pData, DataLen, false);
    HI_INFO_I2C("Ret=0x%x, I2cNum=%d, DevAddr=0x%x, RegAddr=0x%x, Num=%d, Len=%d, data0=0x%x\n", Ret, I2cNum,
                I2cDevAddr, I2cRegAddr, I2cRegAddrByteNum, DataLen, pData[0]);

    up(&g_I2cMutex);

    return Ret;
}

int HI_DRV_I2C_Read(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum, unsigned char *pData,
                       unsigned int DataLen)
{
    int Ret;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        HI_ERR_I2C("I2cNum(%d) is wrong, STD_I2C_NUM is %d\n", I2cNum, HI_STD_I2C_NUM);
        return HI_FAILURE;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return HI_FAILURE;
    }

    Ret = I2C_DRV_Read(I2cNum, I2cDevAddr, true, I2cRegAddr, I2cRegAddrByteNum, pData, DataLen);
    HI_INFO_I2C("Ret=0x%x, I2cNum=%d, DevAddr=0x%x, RegAddr=0x%x, Num=%d, Len=%d\n", Ret, I2cNum, I2cDevAddr,
                I2cRegAddr, I2cRegAddrByteNum, DataLen);

    up(&g_I2cMutex);

    return Ret;
}

/* Added begin: l00185424 20120131, for avl6211 demod */
/* Some I2C needn't send slave address before read */
static int HI_DRV_I2C_ReadDirectly(unsigned int I2cNum, unsigned char I2cDevAddr, unsigned int I2cRegAddr, unsigned int I2cRegAddrByteNum,
                               unsigned char *pData, unsigned int DataLen)
{
    int Ret;

    if (I2cNum >= HI_STD_I2C_NUM)
    {
        HI_ERR_I2C("I2cNum(%d) is wrong, STD_I2C_NUM is %d\n", I2cNum, HI_STD_I2C_NUM);
        return HI_FAILURE;
    }

    Ret = down_interruptible(&g_I2cMutex);
    if (Ret)
    {
        HI_INFO_I2C("lock g_I2cMutex error.\n");
        return HI_FAILURE;
    }

    Ret = I2C_DRV_Read(I2cNum, I2cDevAddr, false, I2cRegAddr, I2cRegAddrByteNum, pData, DataLen);
    HI_INFO_I2C("Ret=0x%x, I2cNum=%d, DevAddr=0x%x, RegAddr=0x%x, Num=%d, Len=%d\n", Ret, I2cNum, I2cDevAddr,
                I2cRegAddr, I2cRegAddrByteNum, DataLen);

    up(&g_I2cMutex);

    return Ret;
}


