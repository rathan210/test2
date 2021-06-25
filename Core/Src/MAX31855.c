/*
 * MAX31855.c
 *
 *  Created on: Sep 22, 2020
 *      Author: Rathan
 */



/*
 * max_31855.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rathan
 */


#include "MAX31855.h"

/************************************************************
 * Function: void PrintTempData(void)
 *
 * @brief:	 This Function is to be called in main loop for printing
 * 		   	 the temperature value
 *
 * @Note: 	 This function calls the ReadTemperature(uint16 *)
 * 			 function which reads the temperature
 *
 * @Note: 	 user_printf() function template is given below
 *************************************************************/

uint32_t TempDelay;

uint8_t errorScreenFlag,tempScreenFlag;

uint16_t pTemp;
uint16_t pTemp_k1;

uint16_t *temp_k1;


void GetempData(void)
{

	if (HAL_GetTick()-TempDelay >= 100)
	{
		TempDelay=HAL_GetTick();
		status = ReadTemperature(&Temperature_value);

/*		if(status != TEMP_OK)
		{
			if(errorScreenFlag == 0)
			{
				errorScreenFlag = 1;
				tempScreenFlag = 0;
				ILI9341_FillScreenTemp(ILI9341_WHITE);
			}

			TempError(status);

		}
		else
		{*/
			if(tempScreenFlag == 0)
			{
				tempScreenFlag = 1;
				errorScreenFlag = 0;
				//ILI9341_FillScreenTemp(ILI9341_WHITE);
			}
			//sprintf(temp_buff1,"T: %03d",Temperature_value);
//			ILI9341_WriteString(K_TYPE_TEMP_VALUE,K_TYPE_Y_AXIS,temp_buff1, Font_11x18, ILI9341_WHITE, ILI9341_WHITE);
			//ILI9341_WriteString1(K_TYPE_TEMP_VALUE,K_TYPE_Y_AXIS,temp_buff1, ILI9341_BLACK, ILI9341_WHITE);
//		}
	}
/*	else
	{
		sprintf(temp_buff,"Temp - %d",Temperature_value);
		ILI9341_WriteString(0, 3*10,temp_buff, Font_11x18, ILI9341_GREEN, ILI9341_WHITE);
	}*/
}

/************************************************************
 * Function: void TempError(Temp_status error)
 *
 * @brief:	 Function is called by PrintTempData() to print
 * 		   	 the thermocouple Fault condition
 *************************************************************/
void TempError(Temp_status error)
{
	if(error == TEMP_SCV_FAULT) /*thermocouple is short circuited to VCC*/
	{
//		ILI9341_WriteString(ERROR_OFFSET,K_TYPE_Y_AXIS,"T:SC-VCC", Font_11x18, ILI9341_WHITE, ILI9341_WHITE);
		//ILI9341_WriteString1(ERROR_OFFSET,K_TYPE_Y_AXIS,"T:SC-VCC", ILI9341_BLACK, ILI9341_WHITE);
	}
	else if(error == TEMP_SCG_FAULT) /*thermocouple is short circuited to GND*/
	{
		//ILI9341_WriteString(ERROR_OFFSET, K_TYPE_Y_AXIS,"T:SC-GND", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
	}
	else if(error == TEMP_OC_FAULT) /*thermocouple is open*/
	{
		//ILI9341_WriteString(ERROR_OFFSET,K_TYPE_Y_AXIS,"T:Open  ", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
	}
}


/**************************************************************
 * Function: Temp_status ReadTemperature(uint16_t *temp)
 *
 * @brief:	 Function is called by PrintTempData() to capture
 * 		   	 the thermocouple temperature and Fault condition
 *
 * @Note: 	 Update the HAL_GPIO_WritePin() function with
 * 			 the port value and pin value to which the SPI
 * 			 chip select  is connected
 *
 * @Note: 	 SPI pheripheral to be configured with
 * 			 Mode      - Receive Only Master
 * 			 Data Size - 8Bits
 * 			 CPOL 	   - LOW
 * 			 CPHA 	   - 1 Edge
 * 			 and pass the appropriate SPI handle structure
 *
 * @Retval:  Temp_status value is returned
 *************************************************************/
Temp_status ReadTemperature(uint16_t *temp)
{
	uint8_t Temp_buf[5] = {"\0"};
//	uint8_t temp_buff_1[5] = {"\0"};
	Temp_status status = TEMP_OK;
//	Temp_status status_k1 = TEMP_OK;

	/*Update this function with the port value and pin value
		to which the SPI chip select is connected*/
//	HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, RESET);
//	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
// 	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);

//	HAL_Delay(50);
	memset(temp, 0, sizeof(&temp));
//	temp = 0;
	memset(Temp_buf, 0, sizeof(Temp_buf));
	/*Check*/

//	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
//    HAL_Delay(50);
	HAL_SPI_Receive(&hspi1,Temp_buf,sizeof(Temp_buf),HAL_MAX_DELAY);

//	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
	HAL_Delay(50);
	*temp = Temp_buf[0] << 8;

	*temp |= Temp_buf[1];

//   HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);

	if(*temp & 0x1)
	{
		if(Temp_buf[3] & 0x1) /*Check to see if thermocouple is open*/
		{
			status = TEMP_OC_FAULT;
		}
		else if(Temp_buf[3] & 0x2) /*Check to see if thermocouple is short circuited to GND*/
		{
			status = TEMP_SCG_FAULT;
		}
		else if(Temp_buf[3] & 0x4)/*Check to see if thermocouple is short circuited to VCC*/
		{
			status = TEMP_SCV_FAULT;
		}
		*temp = pTemp;
		return status;
	}
	else
	{

		*temp >>= 2;
		*temp *= 0.25; /*Temperature Resolution Calculation*/

		pTemp = *temp;
		k1_flag=0;
		k2_flag=1;
		//return pTemp;
	}
//	return pTemp;
	return status; /*Return the Status of the thermocouple*/
	/*Check*/

	/*Configure with the appropriate SPI handle structure*/
//if(k1_flag == 1 && k2_flag == 0)
//{
//	//*temp=0x0;
//	//*temp >>= 16;
//	HAL_SPI_Receive(&hspi1,Temp_buf,sizeof(Temp_buf),HAL_MAX_DELAY);
//
//	*temp = Temp_buf[0] << 8;
//
//	*temp |= Temp_buf[1];
//
////   HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
//
//	if(*temp & 0x1)
//	{
//		if(Temp_buf[3] & 0x1) /*Check to see if thermocouple is open*/
//		{
//			status = TEMP_OC_FAULT;
//		}
//		else if(Temp_buf[3] & 0x2) /*Check to see if thermocouple is short circuited to GND*/
//		{
//			status = TEMP_SCG_FAULT;
//		}
//		else if(Temp_buf[3] & 0x4)/*Check to see if thermocouple is short circuited to VCC*/
//		{
//			status = TEMP_SCV_FAULT;
//		}
//		*temp = pTemp;
//		return status;
//	}
//	else
//	{
//
//		*temp >>= 2;
//		*temp *= 0.25; /*Temperature Resolution Calculation*/
//
//		pTemp = *temp;
//		k1_flag=0;
//		k2_flag=1;
//		//return pTemp;
//	}
////	return pTemp;
//	return status; /*Return the Status of the thermocouple*/
//}
//else if(k2_flag == 1 && k1_flag == 0)
//{
////	*temp=0x0;
////	*temp >>= 16;
//	HAL_SPI_Receive(&hspi1,temp_buff_1,sizeof(temp_buff_1),HAL_MAX_DELAY);
//
//	*temp_k1 = temp_buff_1[0] << 8;
//
//	*temp_k1 |= temp_buff_1[1];
//
////   HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
//
//	if(*temp_k1 & 0x1)
//	{
//		if(temp_buff_1[3] & 0x1) /*Check to see if thermocouple is open*/
//		{
//			status_k1 = TEMP_OC_FAULT;
//		}
//		else if(temp_buff_1[3] & 0x2) /*Check to see if thermocouple is short circuited to GND*/
//		{
//			status_k1 = TEMP_SCG_FAULT;
//		}
//		else if(temp_buff_1[3] & 0x4)/*Check to see if thermocouple is short circuited to VCC*/
//		{
//			status_k1 = TEMP_SCV_FAULT;
//		}
//		*temp_k1 = pTemp_k1;
//		//return status_k1;
//	}
//	else
//	{
//		*temp_k1 >>= 8;
//		*temp_k1 *= 0.25; /*Temperature Resolution Calculation*/
//
//		pTemp_k1 = *temp_k1;
//		k2_flag=0;
//		k1_flag=1;
//		//return pTemp_k1;
//	}
////	return pTemp_k1;
//	return status_k1; /*Return the Status of the thermocouple*/
//}
//return status;
//return status_k1;
}

