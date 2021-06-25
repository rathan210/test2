/*
 * MAX31855.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Rathan
 */

#ifndef INC_MAX31855_H_
#define INC_MAX31855_H_


#include "main.h"
//#include "MAX_31855.h"
#include "stm32f0xx_hal.h"
//#include "stdint.h"
//#include <string.h>
//#include <stdarg.h>
//#include "ili9341.h"
#include <stdlib.h>


typedef enum{
	TEMP_OK = 0,
	TEMP_SCV_FAULT, /*Thermocouple is short circuited to VCC*/
	TEMP_SCG_FAULT, /*Thermocouple is short circuited to GND*/
	TEMP_OC_FAULT, /*Thermocouple is open*/
}Temp_status;

uint16_t Temperature_value;

Temp_status status;
Temp_status status_k1;
Temp_status ReadTemperature(uint16_t *temp);

void GetempData(void);

void TempError(Temp_status error);

extern char temp_buff[200];
extern char temp_buff_1[200];
extern uint8_t k2_flag,k1_flag;
extern SPI_HandleTypeDef hspi1;





#endif /* INC_MAX31855_H_ */
