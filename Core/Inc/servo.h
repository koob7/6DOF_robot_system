/*
 * servo.h
 *
 *  Created on: Oct 12, 2023
 *      Author: kobie
 */

#ifndef INC_SRC_SERVO_H_
#define INC_SRC_SERVO_H_

#include <stdint.h>

#define TIM_NO htim1
#define TIM_CH_NO TIM_CHANNEL_1
#define ANGLE_MIN 0
#define ANGLE_MAX 1800
#define PWM_MIN 500
#define PWM_MAX 2500

#define STEP ((1000 * (PWM_MAX - PWM_MIN)) / (ANGLE_MAX - ANGLE_MIN))
void set_ang(uint16_t ang, uint8_t mode);

#endif /* SRC_SERVO_H_ */
