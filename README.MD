# LTC3207 sensor API
## Introduction
This package contains the Linear Technology LTC3207 sensor driver (sensor API)

The sensor driver package includes ltc3207.h, ltc3207.c and ltc3207_defs.h files


## Integration details
* Integrate ltc3207.h, ltc3207_defs.h and ltc3207.c file in to your project.
* Include the ltc3207.h file in your code like below.
``` c
#include "ltc3207.h"
```

## File information
* ltc3207_defs.h : This header file has the constants, macros and datatype declarations.
* ltc3207.h : This header file contains the declarations of the sensor driver APIs.
* ltc3207.c : This source file contains the definitions of the sensor driver APIs.

## Supported sensor interface
* I2C

## Usage guide
### Initializing the sensor
To initialize the sensor, you will first need to create a device structure. You 
can do this by creating an instance of the structure ltc3207_dev. Then go on to 
fill in the various parameters as shown below.


#### Example code
``` c
struct ltc3207_dev sensor;

sensor.address = LTC3207_I2C_ADDR; // write your own I2C address
sensor.read = user_i2c_read;
sensor.write = user_i2c_write;
sensor.delay_ms = user_delay_ms;

ltc3207_reset(&sensor);

```

### Turning on leds
#### Example for turning on leds
``` c

int8_t res;

/* Select the needed LED by choosing the number from 1 to 12 */
enum ltc3207_uled uled = your_led_number_of_choice;

/* Initialize led register structure, set the mode and the value for current going through the led */
struct ltc3207_led_reg led_reg;

led_reg.uled_mode = LTC3207_uled_mode_normal;
led_reg.led_current = your_value_of_choice;


/* Set the sensor configuration */
res = ltc3207_set_uled(uled, &led_reg, &sensor);
```

## Notes

ENU and Gradual Blinking features were not examined and tested during the writing of this code.
