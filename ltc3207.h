/*
 * ltc3207.h
 *
 *  Created on: May 16, 2019
 *      Author: Petr Zhuvasin
 */

#ifndef LTC3207_H_
#define LTC3207_H_

#include "ltc3207_defs.h"

int8_t ltc3207_set_regs(uint8_t ra, uint8_t *data, uint8_t len, struct ltc3207_dev *dev);
int8_t ltc3207_reset(struct ltc3207_dev *dev);
int8_t ltc3207_set_uled(enum ltc3207_uled uled, struct ltc3207_led_reg *led_reg, struct ltc3207_dev *dev);
int8_t ltc3207_set_cmd(struct ltc3207_cmd_cfg *cmd_cfg, struct ltc3207_dev *dev);
int8_t ltc3207_set_enu(struct ltc3207_enu_cfg *enu_cfg, struct ltc3207_dev *dev);


#endif /* LTC3207_H_ */
