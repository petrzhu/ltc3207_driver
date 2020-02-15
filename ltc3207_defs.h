/*
 * ltc3207.h
 *
 *  Created on: May 16, 2019
 *      Author: Petr Zhuvasin
 */

#ifndef LTC3207_DEFS_H_
#define LTC3207_DEFS_H_
#include "stdint.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if !defined(UINT8_C) && !defined(INT8_C)
#define INT8_C(x)   S8_C(x)
#define UINT8_C(x)  U8_C(x)
#endif

#if !defined(UINT16_C) && !defined(INT16_C)
#define INT16_C(x)  S16_C(x)
#define UINT16_C(x) U16_C(x)
#endif

#if !defined(INT32_C) && !defined(UINT32_C)
#define INT32_C(x)  S32_C(x)
#define UINT32_C(x) U32_C(x)
#endif

#if !defined(INT64_C) && !defined(UINT64_C)
#define INT64_C(x)  S64_C(x)
#define UINT64_C(x) U64_C(x)
#endif

#define STRUCT2UINT8(strct) (*(uint8_t*)&strct)
#define STRUCT2UINT16(strct)(*(uint8_t*)&strct)
/**@}*/
/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *) 0)
#endif
#endif

/*************************** Sensor macros   *****************************/
/* Test for an endian machine */
#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 0
#endif

#ifndef __BYTE_ORDER__
#define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LITTLE_ENDIAN           1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BIG_ENDIAN              1
#else
#error "Code does not support Endian format of the processor"
#endif

/*
 * Register addresses defs
 */
#define LTC3207_RA_CMD UINT8_C(0x0)
#define LTC3207_RA_ULED_1 UINT8_C(0x1)
#define LTC3207_RA_ULED_2 UINT8_C(0x2)
#define LTC3207_RA_ULED_3 UINT8_C(0x3)
#define LTC3207_RA_ULED_4 UINT8_C(0x4)
#define LTC3207_RA_ULED_5 UINT8_C(0x5)
#define LTC3207_RA_ULED_6 UINT8_C(0x6)
#define LTC3207_RA_ULED_7 UINT8_C(0x7)
#define LTC3207_RA_ULED_8 UINT8_C(0x8)
#define LTC3207_RA_ULED_9 UINT8_C(0x9)
#define LTC3207_RA_ULED_10 UINT8_C(0xA)
#define LTC3207_RA_ULED_11 UINT8_C(0xB)
#define LTC3207_RA_ULED_12 UINT8_C(0xC)
#define LTC3207_RA_CAM UINT8_C(0xD)
#define LTC3207_RA_ENU_L UINT8_C(0xE)
#define LTC3207_RA_GRAD_BLINK_ENU_H UINT8_C(0xF)

/*
 * Return values for functions
 */
#define LTC3207_OK INT8_C(0)
#define LTC3207_E_NULL_PTR INT8_C(-1)
#define LTC3207_E_COM_FAIL INT8_C(-2)

/*
 * Masks for configurations, registers etc etc etc
 */

#define LTC3207_GRAD_UP_MASK UINT8_C(0x0)
#define LTC3207_QW_MASK UINT8_C(0x1)
#define LTC3207_FORCE1P5_MASK UINT8_C(0x2)
#define LTC3207_FORCE2X_MASK UINT8_C(0x3)
#define LTC3207_CAMHL_MASK UINT8_C(0x7)

#define LTC3207_ENU_H_MASK UINT8_C(0xF)
#define LTC3207_ENU_L_MASK UINT8_C(0xFF)
#define LTC3207_ENU_H_BITSHIFT (0x8)

#define LTC3207_BLINK_GRAD_MASK (0xF0)
#define LTC3207_BLINK_GRAD_BITSHIFT (0x4)

#define LTC3207_ULED_MODE_BITSHIFT (0x6)
#define LTC3207_ULED_MODE_MASK (0xC0)
#define LTC3207_ULED_CURRENT_MASK (0x3F)

typedef int8_t (*ltc3207_com_fptr_t)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
typedef void (*ltc3207_delay_fptr_t)(uint32_t period);

enum ltc3207_uled
{
	LTC3207_uled_1 = 0x1,
	LTC3207_uled_2,
	LTC3207_uled_3,
	LTC3207_uled_4,
	LTC3207_uled_5,
	LTC3207_uled_6,
	LTC3207_uled_7,
	LTC3207_uled_8,
	LTC3207_uled_9,
	LTC3207_uled_10,
	LTC3207_uled_11,
	LTC3207_uled_12
};

enum ltc3207_uled_mode_bit
{
	LTC3207_uled_mode_normal = 0x0,
	LTC3207_uled_mode_blink_en = 0x01,
	LTC3207_uled_mode_grad_en = 0x02,
	LTC3207_uled_mode_GPO = 0x03
};


struct ltc3207_cmd_cfg
{
#if BYTE_ORDER == BIG_ENDIAN
	uint8_t camhl:1; //0 - external control of CAM, 1 - i2c control of CAM
	uint8_t : 3;
	uint8_t force2x:1; // 0 - enables mode logic to control mode based on dropout sig, 1 - force charge pump into 2x mode
	uint8_t force1p5:1; // 0 - ^, 1 - force charge pump to 1.5x mode; if both force2x and force1pb bits are set to 1, then charge pump is forced to 1x mode
	uint8_t qw:1; // 0 - normal write, 1 quick write allows to write the data from reg1 to all 12 uled regs
	uint8_t gradation:1; // 0 - gradation counts down, 1 - gradation counts up
#else
	uint8_t gradation:1;
	uint8_t qw:1;
	uint8_t force1p5:1;
	uint8_t force2x:1;
	uint8_t : 3;
	uint8_t camhl:1;
#endif

};


struct ltc3207_led_reg
{
	enum ltc3207_uled_mode_bit uled_mode; //uled mode, see enum definition
	uint8_t led_current:6; // full scale current is 27.5 mA,  there are 11 steps meaning there is ~2.3mA in a step, the range of values is between 0x0 and 0x1b
};

struct ltc3207_camera_cfg
{
	uint8_t low_bits:4;
	uint8_t high_bits:4;
};

struct ltc3207_enu_cfg
{
	//set led[number] to 1 to make the chosen led output to be controlled by ENU
#if BYTE_ORDER == BIG_ENDIAN
	uint8_t uled12:1;
	uint8_t uled11:1;
	uint8_t uled10:1;
	uint8_t uled9:1;
	uint8_t uled8:1;
	uint8_t uled7:1;
	uint8_t uled6:1;
	uint8_t uled5:1;
	uint8_t uled4:1;
	uint8_t uled3:1;
	uint8_t uled2:1;
	uint8_t uled1:1;
#else
	uint8_t uled1:1;
	uint8_t uled2:1;
	uint8_t uled3:1;
	uint8_t uled4:1;
	uint8_t uled5:1;
	uint8_t uled6:1;
	uint8_t uled7:1;
	uint8_t uled8:1;
	uint8_t uled9:1;
	uint8_t uled10:1;
	uint8_t uled11:1;
	uint8_t uled12:1;
#endif
};

struct ltc3207_blink_grad_cfg
{
#if BYTE_ORDER == BIG_ENDIAN
	uint8_t blink_period:1; //0 - 1.25s, 1 - 2.5s
	uint8_t blink_times:1; // 0 - 0.625s, 1 - 0.156s
	uint8_t grad_ramp_period:1;
	uint8_t grad_ramp_times:1; // 00 - disabled, 01 - ramp = 2.4s, per = 0.45s, 10 - ramp = 0.48s, per = 0.9s, ramp = 0.96s, per = 1.8s
#else

	uint8_t grad_ramp_times:1;
	uint8_t grad_ramp_period:1;
	uint8_t blink_times:1;
	uint8_t blink_period:1;
#endif
};

struct ltc3207_dev
{
	uint8_t address; // i2c address of ltc3207 device

	ltc3207_com_fptr_t write; // write function pointer
	ltc3207_delay_fptr_t delay; // delay function pointer

	struct ltc3207_blink_grad_cfg blink_grad_cfg;
	struct ltc3207_blink_grad_cfg prev_blink_grad_cfg;
	struct ltc3207_enu_cfg enu_cfg;
	struct ltc3207_enu_cfg prev_enu_cfg;

};

#endif /* LTC3207_DEFS_H_ */
