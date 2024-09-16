/*
 * navigate_robot.h
 *
 *  Created on: Jul 10, 2024
 *      Author: kobie
 */

#ifndef INC_NAVIGATE_ROBOT_H_
#define INC_NAVIGATE_ROBOT_H_

#include "display_ssd1963.h"
#include "ff.h"
#include "gpio.h"
#include "math.h"
#include "menu_block.h"
#include "stdio.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define command_explorer_start_pos_x 200
#define command_explorer_start_pos_y 138
#define command_explorer_line_height 28
#define command_explorer_line_space 16
#define command_explorer_num_files_on_page 8
#define command_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)
#define command_explorer_first_setting_x 260
#define command_explorer_second_setting_x 370
#define command_explorer_third_setting_x 540

#define single_wait_time_prescaller 200

struct robot_position {
  double x;
  double y;
  double z;
  double a;
  double b;
  double c;

  robot_position(double x_val, double y_val, double z_val, double a_val,
                 double b_val, double c_val)
      : x(x_val), y(y_val), z(z_val), a(a_val), b(b_val), c(c_val) {}
  robot_position() : x(0), y(0), z(0), a(0), b(0), c(0) {}

  bool operator==(const robot_position &other) const {
    return x == other.x && y == other.y && z == other.z && a == other.a &&
           b == other.b && c == other.c;
  }
};

extern struct robot_position robot_home_position;

// maksymalne wartości pozycji robota
extern int max_range;
extern int min_range;
extern int min_y;
extern int min_x;

// wykorzystywane wymiary konstrukcji robota
extern double d1;
extern double a2;
extern double a3;
extern double d6;

extern uint16_t max_licz_krokow_osi[6];
extern double currentPosition[6];
extern double givenPosition[6];
extern int liczba_krokow_osi[5];
extern uint8_t kalibracja_osi[5];
extern int givenSteps[6];

extern bool robot_was_moved; // jeżeli true - oznacza że robot był ruszony przez
                             // użytkownika, zmienna potrzebna przy wykonywaniu
                             // całego programu
extern volatile bool
    automatic_movement_ready; // zmienna która bedzie regulować prędkością
                              // robota w obsłudze programu- będzie setowana w
                              // przerwaniu i resetowaniu przy ruchu robotem
extern volatile bool manual_movement_ready; //...w ręcznym sterowaniu robotem

void kalibracja_robota(int givenSteps[6], int liczba_krokow_osi[5],
                       uint8_t kalibracja_osi[5]);
bool licz_kroki(
    double givenPosition[6], int givenSteps[6],
    double currentPosition[6]); // zwraca true jeżeli ruch jest możliwy, w
                                // przeciwnym wyapdku false
void simpleMoveMotor(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void moveMotorWithPosition(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                           int *stepCounter, int8_t factor);
void setDuration(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, int currentSteps,
                 int givenSteps, int8_t *factor);
void handle_move_interrupt(int *givenSteps, int *liczba_krokow_osi,
                           int8_t *factor);
void handle_limit_switch_interrupt(uint16_t GPIO_Pin, uint8_t *kalibracja_osi,
                                   int *givenSteps, int *liczba_krokow_osi);
struct robot_position get_current_position();
#endif /* INC_NAVIGATE_ROBOT_H_ */
