/*
 * finish_state_machine.h
 *
 *  Created on: Aug 26, 2024
 *      Author: kobie
 */

#ifndef INC_FINISH_STATE_MACHINE_H_
#define INC_FINISH_STATE_MACHINE_H_

#include <iostream>
#include <display_ssd1963.h>
#include <draw_display.h>
#include <navigate_robot.h>
#include "xpt2046.h"
#include <iostream>
#include "menu_parts.h"
#include <objects.h>
#include <memory>

enum class e_operation_mode {
  MANUAL, AUTOMATIC
};

enum class e_project_mode {
  SETTINGS,
  BROWSE_PROJECTS,
  EDIT_PROJECTS,
  STREIGHT_MOVE,
  CIRCULAR_MOVE,
  WAIT_COMAND,
  SET_PIN_COMAND,

};

enum class e_step_mode {
  STEP_BY_STEP, CONTINUOUS
};

enum class e_control_mode {
  AUTOMATIC_MODE, MANUAL_MODE
};

class finish_state_machine {
  enum e_movement_speed {
    //to są wartości procentowe
    speed_10,
    speed_50,
    speed_100,
    num_of_speed_levels
  };
  enum e_movement_speed manual_movement_speed = e_movement_speed::speed_100;
  enum e_movement_speed automatic_movement_speed = e_movement_speed::speed_100;
  volatile double manual_speed_movement_factor=0.01;
  volatile double automatic_speed_movement_factor=0.01;
  bool edit_command = false; //mówi o tym czy tworzymy nowy punkt czy tylko go edytujemy
  mov_streight o_mov_streight;
  mov_circular o_mov_circular;
  cmd_wait o_cmd_wait;
  cmd_set_pin o_cmd_set_pin;
  robot_position target_position;
  bool target_point_initialized = false;
  robot_position help_position;
  bool help_point_initialized = false;
  e_operation_mode operation_mode;
  e_project_mode project_mode;
  e_step_mode step_mode;
  e_control_mode control_mode;
  e_project_mode previous_project_mode;
  project_editor main_project_editor;
  projects_explorer main_project_explorer;
  void change_mode(e_operation_mode new_state);
  void change_mode(e_project_mode new_state);
  void change_mode(e_step_mode new_state);
  void change_mode(e_control_mode new_state);
  void cancel_creating_command();
  void choose_file_sorting_option();
  void create_new_file();
  void delete_choosen_file();
  void go_to_choosen_file();
  void save_changed_file();
  void save_changed_file_and_close();
  void choose_and_prepare_to_create_command();
  void prepare_to_edit_choosen_command();
  void delete_choosen_command();
  template<typename t_command, typename t_update_value,
      typename t_update_value_fun, typename t_get_text_fun>
  void update_command_value_helper(t_command &command,
      t_update_value update_value,menu_segment &menu, int menu_button,
      void (t_update_value_fun::*update_value_fun)( t_update_value),
      std::string (t_get_text_fun::*get_text_fun)(), std::string aditional_text="");
  template<typename CommandType>
  void update_movement_type(CommandType &command, menu_segment &menu);
  template<typename CommandType>
  void update_movement_speed(CommandType &command, menu_segment &menu);
  template<typename CommandType>
  void save_changed_command(CommandType &command);
  template<typename CommandType, typename comandType2>
  void update_position(CommandType &command, bool &initialized,
      void (comandType2::*update_function)(struct robot_position));
  void update_wait_speed();
  void update_output_pin();
  void update_pin_level();
  bool handle_movement_menu(int x, int y);
  std::string get_movement_speed_text(const e_movement_speed movement_speed);
  void update_movement_speed_factor(e_movement_speed &movement_speed,volatile double &speed_movement_factor, int button_index);
  void adjust_movement_speed(e_movement_speed &movement_speed, volatile double &speed_movement_factor, int button_index, bool increase);
public:

  finish_state_machine();


  int handle_press_with_current_state(int x, int y);

private:
  allert a_cancel_create_command;
  list_dialog l_choose_sort_file_order;
  allert a_already_existing_file;
  allert a_conf_deleting_file;
  allert a_no_choosen_file_to_delete;
  allert a_confirm_save_changed_file;
  list_dialog l_choose_command_type;
  allert a_conf_deleting_command;
  allert a_no_choosen_comand_to_delete;
  list_dialog l_choose_movement_type;
  allert a_conf_update_target_pos;
  allert a_conf_help_target_pos;
  allert a_no_set_target_pos;
  allert a_no_set_help_pos;
  allert a_conf_save_command;
  list_dialog l_choose_movement_speed;
  allert a_no_choosen_file_to_open;
  allert a_function_avilable_in_future;
  list_dialog l_choose_wait_time;
  list_dialog l_choose_output_pin;
  list_dialog l_choose_pin_level;

};

#endif /* INC_FINISH_STATE_MACHINE_H_ */
