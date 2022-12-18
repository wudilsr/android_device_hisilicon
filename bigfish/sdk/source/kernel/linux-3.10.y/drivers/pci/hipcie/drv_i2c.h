#ifndef __DRV_I2C_H_
#define __DRV_I2C_H_

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


#define I2C_3716C_SYSCLK  (125000000)
#define I2C_DFT_SYSCLK    (100000000)  // 3716H 3716M 3716L

//#define I2C_DFT_RATE      (100000)
#define I2C_DFT_RATE      (400000)

#define I2C0_PHY_ADDR     (0xF8B10000)
#define I2C1_PHY_ADDR     (0xF8B11000)
#define I2C2_PHY_ADDR     (0xF8B12000)
#define I2C3_PHY_ADDR     (0xF8B13000)
#define I2C4_PHY_ADDR     (0xF8B16000)//I2C ADC
#define I2CQAM_PHY_ADDR   (0xF8B17000)//I2C QAM,not used



#define I2C_CTRL_REG      (0x000)
#define I2C_COM_REB       (0x004)
#define I2C_ICR_REG       (0x008)
#define I2C_SR_REG        (0x00C)
#define I2C_SCL_H_REG     (0x010)
#define I2C_SCL_L_REG     (0x014)
#define I2C_TXR_REG       (0x018)
#define I2C_RXR_REG       (0x01C)


#define READ_OPERATION     (1)
#define WRITE_OPERATION    0xfe



/* I2C_CTRL_REG */
#define I2C_ENABLE             (1 << 8)
#define I2C_UNMASK_TOTAL       (1 << 7)
#define I2C_UNMASK_START       (1 << 6)
#define I2C_UNMASK_END         (1 << 5)
#define I2C_UNMASK_SEND        (1 << 4)
#define I2C_UNMASK_RECEIVE     (1 << 3)
#define I2C_UNMASK_ACK         (1 << 2)
#define I2C_UNMASK_ARBITRATE   (1<< 1)
#define I2C_UNMASK_OVER        (1 << 0)
#define I2C_UNMASK_ALL         (I2C_UNMASK_START | I2C_UNMASK_END | \
                                I2C_UNMASK_SEND | I2C_UNMASK_RECEIVE | \
                                I2C_UNMASK_ACK | I2C_UNMASK_ARBITRATE | \
                                I2C_UNMASK_OVER)


/* I2C_COM_REB */
#define I2C_SEND_ACK (~(1 << 4))
#define I2C_START (1 << 3)
#define I2C_READ (1 << 2)
#define I2C_WRITE (1 << 1)
#define I2C_STOP (1 << 0)

/* I2C_ICR_REG */
#define I2C_CLEAR_START (1 << 6)
#define I2C_CLEAR_END (1 << 5)
#define I2C_CLEAR_SEND (1 << 4)
#define I2C_CLEAR_RECEIVE (1 << 3)
#define I2C_CLEAR_ACK (1 << 2)
#define I2C_CLEAR_ARBITRATE (1 << 1)
#define I2C_CLEAR_OVER (1 << 0)
#define I2C_CLEAR_ALL (I2C_CLEAR_START | I2C_CLEAR_END | \
                       I2C_CLEAR_SEND | I2C_CLEAR_RECEIVE | \
                       I2C_CLEAR_ACK | I2C_CLEAR_ARBITRATE | \
                       I2C_CLEAR_OVER)

/* I2C_SR_REG */
#define I2C_BUSY (1 << 7)
#define I2C_START_INTR (1 << 6)
#define I2C_END_INTR (1 << 5)
#define I2C_SEND_INTR (1 << 4)
#define I2C_RECEIVE_INTR (1 << 3)
#define I2C_ACK_INTR (1 << 2)
#define I2C_ARBITRATE_INTR (1 << 1)
#define I2C_OVER_INTR (1 << 0)

static void I2C_DRV_SetRate(unsigned int I2cNum, unsigned int I2cRate);
//#define I2C_START_END (I2C_START_INTR | I2C_OVER_INTR)
//#define I2C_STOP_END (I2C_END_INTR | I2C_OVER_INTR)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif


