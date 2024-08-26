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

enum class e_operation_mode {
  MANUAL, AUTOMATIC
};

enum class e_project_mode {
  SETTINGS, BROWSE_PROJECTS, EDIT_PROJECTS
};

enum class e_step_mode {
  STEP_BY_STEP, CONTINUOUS
};

enum class e_control_mode {
  AUTOMATIC_MODE, MANUAL_MODE
};

class finish_state_machine {
public:

  finish_state_machine();

  void change_mode(e_operation_mode new_state);
  void change_mode(e_project_mode new_state);
  void change_mode(e_step_mode new_state);
  void change_mode(e_control_mode new_state);
  void handle_press_with_current_state(int x, int y);

private:

  e_operation_mode operation_mode;
  e_project_mode project_mode;
  e_step_mode step_mode;
  e_control_mode control_mode;
  project_editor main_project_editor;
  projects_explorer main_project_explorer;

};

#endif /* INC_FINISH_STATE_MACHINE_H_ */
