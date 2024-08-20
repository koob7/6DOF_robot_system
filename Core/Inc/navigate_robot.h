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
#include "display_ssd1963.h"
#include "menu_parts.h"

#define command_explorer_start_pos_x 200
#define command_explorer_start_pos_y 208
#define command_explorer_line_height 28
#define command_explorer_line_space 16
#define command_explorer_num_files_on_page 6
#define command_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)
#define command_explorer_first_setting_x 260
#define command_explorer_second_setting_x 370
#define command_explorer_third_setting_x 480

struct robot_position {
  double x;
  double y;
  double z;
  double a;
  double b;
  double c;

  robot_position(double x_val, double y_val, double z_val, double a_val,
      double b_val, double c_val) :
      x(x_val), y(y_val), z(z_val), a(a_val), b(b_val), c(c_val) {
  }

  bool operator==(const robot_position &other) const {
    return x == other.x && y == other.y && z == other.z && a == other.a
        && b == other.b && c == other.c;
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

class command {
public:
  virtual bool perform_task() = 0;
  virtual void draw(int print_y) = 0;
  // std::string getType(){return typeid(*this).name();}
};

class movement: public command {
public:
  enum e_movement_type {
    continous, step_by_step,
  };
  enum e_speed {
    //to są wartości procentowe
    speed_10,
    speed_50,
    speed_100,
  };
  struct robot_position target_pos;
  uint8_t speed;
  enum e_movement_type movement_type;
  movement(struct robot_position in_target_pos, uint8_t speed,
      enum e_movement_type movement_type);
  struct robot_position get_target_position() {
    return target_pos;
  }
  void draw(int print_y);
  virtual void save_to_file(struct robot_position &in_target_pos,
      enum e_speed &in_speed, enum e_movement_type &in_movement_type)=0;
};

class mov_streight: public movement {
public:
  mov_streight(struct robot_position in_target_pos, enum e_speed speed,
      enum e_movement_type movement_type);
  bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel
  void update_command(struct robot_position in_target_pos,
      enum e_speed in_speed, enum e_movement_type in_movement_type);
  void save_to_file(struct robot_position &in_target_pos,
      enum e_speed &in_speed, enum e_movement_type &in_movement_type);
};

class mov_circular: public movement {
public:
  struct robot_position help_pos;
  mov_circular(struct robot_position in_help_pos,
      struct robot_position in_target_pos, enum e_speed speed,
      enum e_movement_type movement_type);
  bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel
  void update_command(struct robot_position in_help_pos,
      struct robot_position in_target_pos, enum e_speed in_speed,
      enum e_movement_type in_movement_type);
  struct robot_position get_help_position() {
    return help_pos;
  }
  void save_to_file(struct robot_position &in_target_pos,
      enum e_speed &in_speed, enum e_movement_type &in_movement_type);
};

class control: public command {
public:
  virtual void save_to_file()=0;
};

class cmd_wait: public control {
public:
  enum e_wait_time {
    wait_1s, wait_5s, wait_30s, wait_1min, wait_5min,
  };

  enum e_wait_time wait_time;
  cmd_wait(enum e_wait_time wait_time);
  cmd_wait(std::string command_line);
  bool perform_task(); // tutaj będzie odczekiwany mały odstęp czasu,  zwraca
                       // true jeżeli osiągnięto cel
  void draw(int print_y);
  void update_command(enum e_wait_time wait_time);
  void save_to_file();
};

class cmd_set_pin: public control {
public:
  enum e_output_pin {
    robot_tool, user_led,
  };
  enum e_output_pin output_pin;
  bool set_pin_high;
  cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high);
  cmd_set_pin(std::string command_line);
  bool perform_task(); // tutaj będzie ustawiana wartość pinu w zależności od
                       // zmiennej set_pin_high, zwraca true jeżeli poprawnie
                       // ustawiono pin
  void draw(int print_y);
  void update_command(enum e_output_pin in_output_pin, bool in_set_pin_high);
  void save_to_file();
};

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
