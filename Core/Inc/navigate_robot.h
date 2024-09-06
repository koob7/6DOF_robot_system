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
#include <fstream>
#include <iostream>
#include <sstream>
#include "ff.h"
#include <vector>
#include <exception>

#define command_explorer_start_pos_x 200
#define command_explorer_start_pos_y 208
#define command_explorer_line_height 28
#define command_explorer_line_space 16
#define command_explorer_num_files_on_page 6
#define command_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)
#define command_explorer_first_setting_x 260
#define command_explorer_second_setting_x 370
#define command_explorer_third_setting_x 540



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
  robot_position() :
        x(0), y(0), z(0), a(0), b(0), c(0) {
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

extern uint16_t max_licz_krokow_osi[6];
extern double currentPosition[6];
extern double givenPosition[6];
extern int liczba_krokow_osi[5];
extern uint8_t kalibracja_osi[5];
extern int givenSteps[6];

extern bool robot_was_moved;
extern volatile bool automatic_movement_ready;
extern volatile bool manual_movement_ready;

class command {

public:
  int task_progres=0;
  int task_steps=1;//task steps nigdy nie może być zerem - zadanie zawsze musi mieć choć jeden etap do wykonania
  virtual void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector) = 0;//funkcja prepare_task jest wywoływana tylko jeżeli robot_was_moved==true lub gdy pierwszy raz wywołujemy komendę
  virtual void perform_task() = 0;//zwraca true jak wykona się cała komenda
  void reset_task_progres(){task_progres=0;}
  bool is_task_completed(){return task_progres==task_steps;}
  virtual void draw(int print_y) = 0;
  virtual void save_to_file(FIL& fil)=0;
  virtual struct robot_position get_target_position() {
    throw std::exception();
  }
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
  enum e_speed speed;
  enum e_movement_type movement_type;
  movement();
  movement(struct robot_position in_target_pos, enum e_speed  speed,
      enum e_movement_type movement_type);
  movement(const movement& other);
  struct robot_position get_target_position() {
    return target_pos;
  }
  void draw(int print_y){}
  void draw_movement(int print_y, bool ciruclar_movement);
  enum e_speed get_speed() {
    return speed;
  }
  enum e_movement_type get_movement_type() {
    return movement_type;
  }
  std::string get_speed_text();
  std::string get_movement_type_text();
  void update_speed(enum e_speed in_speed){speed =in_speed;}
  void update_movement_type(enum e_movement_type in_movement_type){movement_type=in_movement_type;}
  void update_target_pos(struct robot_position in_target_pos){target_pos =in_target_pos;}
  void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector){}
  void perform_task(){}

};

class mov_streight: public movement {
public:
  void draw(int print_y){draw_movement(print_y, false);}
  mov_streight()=default;
  mov_streight(struct robot_position in_target_pos, enum e_speed speed,
      enum e_movement_type movement_type);
  mov_streight(std::istringstream& iss);
  mov_streight(const mov_streight& other);
  void perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel
  void update_command(struct robot_position in_target_pos,
      enum e_speed in_speed, enum e_movement_type in_movement_type);
  void update_command(mov_streight in_object);
  void save_to_file(FIL& fil);
  void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector);
};

class mov_circular: public movement {
public:
  struct robot_position help_pos;
  void draw(int print_y){draw_movement(print_y, true);}
  mov_circular(std::istringstream& iss);
  mov_circular(struct robot_position in_help_pos,
      struct robot_position in_target_pos, enum e_speed speed,
      enum e_movement_type movement_type);
  mov_circular() = default;
  mov_circular(const mov_circular& other);
  void perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel
  void update_command(struct robot_position in_help_pos,
      struct robot_position in_target_pos, enum e_speed in_speed,
      enum e_movement_type in_movement_type);
  void update_command(mov_circular in_object);
  void update_help_pos(struct robot_position in_help_pos){help_pos =in_help_pos;}
  struct robot_position get_help_position() {
    return help_pos;
  }
  void save_to_file(FIL& fil);
  void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector);
};

class cmd_wait: public command  {
public:
  enum e_wait_time {
    wait_1s, wait_5s, wait_30s, wait_1min, wait_5min,
  };
  cmd_wait() = default;
  enum e_wait_time wait_time;
  cmd_wait(std::istringstream& iss);
  cmd_wait(enum e_wait_time wait_time);
  cmd_wait(const cmd_wait& other);
  void perform_task(); // tutaj będzie odczekiwany mały odstęp czasu,  zwraca
                       // true jeżeli osiągnięto cel
  void draw(int print_y);
  void update_command(enum e_wait_time wait_time);
  void update_command(cmd_wait in_object);

  void update_time(enum e_wait_time in_wait_time){wait_time=in_wait_time;}
  void save_to_file(FIL& fil);
  std::string get_time_text();
  void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector);
};

class cmd_set_pin: public command  {
public:
  cmd_set_pin()=default;
  enum e_output_pin {
    robot_tool, user_led,
  };
  enum e_output_pin output_pin;
  bool set_pin_high;
  cmd_set_pin(std::istringstream& iss);
  cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high);
  cmd_set_pin(const cmd_set_pin& other);
  void perform_task(); // tutaj będzie ustawiana wartość pinu w zależności od
                       // zmiennej set_pin_high, zwraca true jeżeli poprawnie
                       // ustawiono pin
  void draw(int print_y);
  void update_pin(enum e_output_pin in_output_pin){output_pin=in_output_pin;}
  void update_pin_level(bool in_set_pin_high){set_pin_high=in_set_pin_high;}
  void update_command(enum e_output_pin in_output_pin, bool in_set_pin_high);
  void update_command(cmd_set_pin in_object);
  void save_to_file(FIL& fil);
  std::string get_pin_output_text();
  std::string get_pin_level_text();
  void prepare_task(std::vector<std::shared_ptr<command>>::iterator first_command_iteratort, int position_in_vector);
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
void handle_move_interrupt(int *givenSteps, int *liczba_krokow_osi, int8_t *factor);
void handle_limit_switch_interrupt(uint16_t GPIO_Pin, uint8_t *kalibracja_osi, int *givenSteps, int *liczba_krokow_osi);
struct robot_position get_current_position();
#endif /* INC_NAVIGATE_ROBOT_H_ */
