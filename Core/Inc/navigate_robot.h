/*
 * navigate_robot.h
 *
 *  Created on: Jul 10, 2024
 *      Author: kobie
 */

#ifndef INC_NAVIGATE_ROBOT_H_
#define INC_NAVIGATE_ROBOT_H_

#include "stdio.h"
#include "math.h"
#include "gpio.h"

extern int max_range;
extern int min_range;
extern int min_y;
extern int min_x;


extern double d1;
extern double a2;
extern double a3;
extern double d6;
void kalibracja_robota(int givenSteps[6], int liczba_krokow_osi[5], uint8_t kalibracja_osi [5]);
void licz_kroki(double givenPosition[6], int givenSteps[6], double currentPosition[6]);
void simpleMoveMotor( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void moveMotorWithPosition( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,  int* stepCounter, int8_t factor);
void setDuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int currentSteps, int givenSteps, int8_t* factor);
#endif /* INC_NAVIGATE_ROBOT_H_ */
