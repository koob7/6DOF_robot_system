/*
 * servo.c
 *
 *  Created on: Oct 12, 2023
 *      Author: kobie
 */
#include "tim.h"
#include "servo.h"

void set_ang(uint16_t ang,  uint8_t mode)
{
	uint16_t val;
	if(ang>ANGLE_MAX)
	{ang=ANGLE_MAX;}
		else if (ang<ANGLE_MIN)
			{ang=ANGLE_MIN;}
			if(mode)
				{val=PWM_MIN+((ang-ANGLE_MIN)*STEP)/1000;}
			else
				{val=PWM_MAX-((ang-ANGLE_MIN)*STEP)/1000;}
	__HAL_TIM_SET_COMPARE(&TIM_NO, TIM_CH_NO, val);

}
