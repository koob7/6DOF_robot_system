/*
 * navigate_robot.h
 *
 *  Created on: Jul 10, 2024
 *      Author: kobie
 */

#ifndef INC_NAVIGATE_ROBOT_H_
#define INC_NAVIGATE_ROBOT_H_

#include "gpio.h"
#include "math.h"
#include "stdio.h"

struct robot_position{
double x;
double y;
double z;
double a;
double b;
double c;

robot_position(double x_val, double y_val, double z_val,
		double a_val, double b_val, double c_val)
        : x(x_val), y(y_val), z(z_val), a(a_val), b(b_val), c(c_val) {}

bool operator==(const robot_position& other) const {
        return x == other.x && y == other.y && z == other.z &&
               a == other.a && b == other.b && c == other.c;
    }
};

extern struct robot_position robot_home_position;

extern int max_range;
extern int min_range;
extern int min_y;
extern int min_x;

extern double d1;
extern double a2;
extern double a3;
extern double d6;
void kalibracja_robota(int givenSteps[6], int liczba_krokow_osi[5],
                       uint8_t kalibracja_osi[5]);
void licz_kroki(double givenPosition[6], int givenSteps[6],
                double currentPosition[6]);
void simpleMoveMotor(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void moveMotorWithPosition(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                           int *stepCounter, int8_t factor);
void setDuration(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, int currentSteps,
                 int givenSteps, int8_t *factor);
#endif /* INC_NAVIGATE_ROBOT_H_ */
