#include "commands.h"

movement::movement() {
  target_pos = robot_position();
  speed = speed_10;
  movement_type = continous;
}

movement::movement(struct robot_position in_target_pos, enum e_speed speed,
                   enum e_movement_type movement_type)
    : target_pos(in_target_pos), speed(speed), movement_type(movement_type) {}

movement::movement(const movement &other)
    : target_pos(other.target_pos), speed(other.speed),
      movement_type(other.movement_type) {}

void movement::draw_movement(int print_y, bool ciruclar_movement) {

  std::string move_type = ciruclar_movement ? "Circ." : "Strai.";

  std::string type_string =
      (movement_type == continous) ? "Continous" : "Step_by_step";

  std::string speed_string;
  switch (speed) {
  case speed_10:
    speed_string = "10%";
    break;
  case speed_50:
    speed_string = "50%";
    break;
  case speed_100:
    speed_string = "100%";
    break;
  default:
    // TODO tutaj będzie kiedyś wyjątek
    break;
  }

  draw_text(command_explorer_first_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "MOVE = " + move_type);

  draw_text(command_explorer_second_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "TYPE = " + type_string);

  draw_text(command_explorer_third_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "SPEED = " + speed_string);
}

std::string movement::get_speed_text() {
  switch (speed) {
  case speed_10:
    return "10";
  case speed_50:
    return "50";
  case speed_100:
    return "100";
  }
}

std::string movement::get_movement_type_text() {
  switch (movement_type) {
  case continous:
    return "cont.";
  case step_by_step:
    return "step.";
  }
}