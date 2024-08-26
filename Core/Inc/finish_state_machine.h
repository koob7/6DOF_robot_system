/*
 * finish_state_machine.h
 *
 *  Created on: Aug 26, 2024
 *      Author: kobie
 */

#ifndef INC_FINISH_STATE_MACHINE_H_
#define INC_FINISH_STATE_MACHINE_H_

#include <iostream>

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
};

#endif /* INC_FINISH_STATE_MACHINE_H_ */
