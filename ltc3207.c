/*
 * ltc3207.c
 *
 *  Created on: May 23, 2019
 *      Author: Petr Zhuvasin
 */


#include "ltc3207.h"


/*
 * sets all the values in cmd configuration to 0s
 */

static void set_reset_cmd_cfg(struct ltc3207_cmd_cfg *cmd_cfg)
{
	cmd_cfg->camhl = 0;
	cmd_cfg->force1p5 = 0;
	cmd_cfg->force2x = 0;
	cmd_cfg->gradation = 0;
	cmd_cfg->qw = 0;
}

static int8_t null_ptr_check(const struct ltc3207_dev *dev)
{
	int8_t res;
	 if ((dev == NULL) || (dev->write == NULL) || (dev->delay == NULL))
	 {
		 res = LTC3207_E_NULL_PTR;
	 }
	 else
	 {
		 res = LTC3207_OK;
	 }

	 return res;
}

/*
 * This API writes data to chosen register
 */
int8_t ltc3207_set_regs(uint8_t ra, uint8_t *data, uint8_t len, struct ltc3207_dev *dev)
{
	int8_t res = LTC3207_OK;
	uint8_t count = 0;
	res = null_ptr_check(dev);
	if (res != LTC3207_E_NULL_PTR)
	{
		for (; count < len; count++)
		{
			res = dev->write(dev->address,ra,&data[count],1);
			dev->delay(1);
		}
		if (res != LTC3207_OK)
		{
			res = LTC3207_E_COM_FAIL;
		}
	}

	return res;
}

/*
 * This API turns off all the LED lights and sets
 */
int8_t ltc3207_reset(struct ltc3207_dev *dev)
{
	uint8_t res = null_ptr_check(dev);

	uint8_t data = 0;
	data = 1 << LTC3207_QW_MASK;
	if (res != LTC3207_E_NULL_PTR)
	{
		res = ltc3207_set_regs(LTC3207_RA_CMD, &data, 1, dev);
		if (res == LTC3207_OK)
		{
			data = 0;
			res = ltc3207_set_regs(LTC3207_RA_ULED_1, &data, 1, dev);
			if (res == LTC3207_OK)
			{
				data = 0;
				res = ltc3207_set_regs(LTC3207_RA_CMD, &data, 1, dev);
				if (res == LTC3207_OK)
				{
					res = ltc3207_set_regs(LTC3207_RA_ENU_L, &data, 1, dev);
					if (res == LTC3207_OK)
					{
						res = ltc3207_set_regs(LTC3207_RA_GRAD_BLINK_ENU_H, &data, 1, dev);
						if (res == LTC3207_OK)
						{
							data = 0;
							res = ltc3207_set_regs(LTC3207_RA_CMD, &data, 1, dev);
						}
					}
				}
			}
		}
	}

	return res;
}

int8_t ltc3207_set_uled(enum ltc3207_uled uled, struct ltc3207_led_reg *led_reg, struct ltc3207_dev *dev)
{
	uint8_t data = 0;
	int8_t res = null_ptr_check(dev);
	if (res != LTC3207_E_NULL_PTR)
	{
		if (led_reg != NULL)
		{
			data = (uint8_t)((led_reg->uled_mode) << LTC3207_ULED_MODE_BITSHIFT) & LTC3207_ULED_MODE_MASK;
			data = data | ((led_reg->led_current) & LTC3207_ULED_CURRENT_MASK);
			res = LTC3207_OK;
			res = ltc3207_set_regs(uled, &data, 1, dev);
		}
	}

	return res;
}

int8_t ltc3207_set_cmd(struct ltc3207_cmd_cfg *cmd_cfg, struct ltc3207_dev *dev)
{
	uint8_t data = STRUCT2UINT8(*cmd_cfg);
	uint8_t res = LTC3207_OK;

	res = ltc3207_set_regs(LTC3207_RA_CMD, &data, 1, dev);

	return res;
}

int8_t ltc3207_set_enu(struct ltc3207_enu_cfg *enu_cfg, struct ltc3207_dev *dev)
{
	uint16_t enu = STRUCT2UINT16(*enu_cfg);
	uint8_t enu_l = ((uint8_t)enu) & LTC3207_ENU_L_MASK;

	uint8_t res = LTC3207_OK;


	res = ltc3207_set_regs(LTC3207_RA_ENU_L, &enu_l, 1, dev);
	if (res == LTC3207_OK)
	{
		uint8_t enu_h = (STRUCT2UINT8(dev->blink_grad_cfg) << LTC3207_BLINK_GRAD_BITSHIFT) & LTC3207_BLINK_GRAD_MASK;
		enu_h = enu_h | (((uint8_t)enu >> LTC3207_ENU_H_BITSHIFT) & LTC3207_ENU_H_MASK);
		res = ltc3207_set_regs(LTC3207_RA_GRAD_BLINK_ENU_H, &enu_h, 1, dev);
	}

	return res;
}

int8_t ltc3207_set_blink_grad(struct ltc3207_blink_grad_cfg *blink_grad_cfg, struct ltc3207_dev *dev)
{
	uint8_t data = STRUCT2UINT8(*blink_grad_cfg);
	data = (data << LTC3207_BLINK_GRAD_BITSHIFT) & LTC3207_BLINK_GRAD_MASK;

	int8_t res = ltc3207_set_regs(LTC3207_RA_GRAD_BLINK_ENU_H, &data, 1, &dev);
	return res;
}
