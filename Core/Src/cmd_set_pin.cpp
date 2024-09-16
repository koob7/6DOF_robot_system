#include "cmd_set_pin.h"

cmd_set_pin::cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high)
    : output_pin(output_pin), set_pin_high(set_pin_high) {}

cmd_set_pin::cmd_set_pin(std::istringstream &iss) {
  char prefix;
  double value;
  while (iss >> prefix >> value) {
    switch (prefix) {
    case 'P':
      switch (static_cast<int>(value)) {
      case 0:
        output_pin = robot_tool;
        break;
      case 1:
        output_pin = user_led;
        break;
      default:
        // TODO tutaj powinien być wyjątek
        break;
      }
      break;
    case 'S':
      switch (static_cast<int>(value)) {
      case 0:
        set_pin_high = false;
        break;
      case 1:
        set_pin_high = true;
        break;
      default:
        // TODO tutaj powinien być wyjątek
        break;
      }
      break;
    default:
      // TODO tutaj powinien być wyjątek
      break;
    }
  }
}

cmd_set_pin::cmd_set_pin(const cmd_set_pin &other)
    : command(other), output_pin(other.output_pin),
      set_pin_high(other.set_pin_high) {}

void cmd_set_pin::update_command(cmd_set_pin in_object) {
  output_pin = in_object.output_pin;
  set_pin_high = in_object.set_pin_high;
}

void cmd_set_pin::update_command(enum e_output_pin in_output_pin,
                                 bool in_set_pin_high) {
  output_pin = in_output_pin;
  set_pin_high = in_set_pin_high;
}

bool cmd_set_pin::perform_task() {
  task_progres = 1;
  switch (output_pin) {
  case e_output_pin::robot_tool:
    // HAL_GPIO_WritePin(ROBOT_TOOl_GPIO_Port, ROBOT_TOOl_Pin,
    // set_pin_high?GPIO_PIN_SET:GPIO_PIN_RESET); obecnie nie mamy żadnego
    // nażędzia więc nic się nie dzieje
    break;
  case e_output_pin::user_led:
    HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin,
                      set_pin_high ? GPIO_PIN_SET : GPIO_PIN_RESET);
    break;
  }
  return true;
}

void cmd_set_pin::prepare_task(
    std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
    int position_in_vector) {
  task_progres = 0;
  // task_steps=1;//w tej komendzie zmiana pinu zawsze będzie operacją atomową
}

void cmd_set_pin::save_to_file(FIL &fil) {

  char buffer[64];
  int len = 0;
  UINT bytesWritten;

  len += snprintf(buffer + len, sizeof(buffer) - len, "M42 ");

  switch (output_pin) {
  case robot_tool:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P0 ");
    break;
  case user_led:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P1 ");
    break;
  default:
    // TODO turtaj powinien być zwrócony wyjątek
    break;
  }

  // Append pin state
  switch (set_pin_high) {
  case true:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S1");
    break;
  case false:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S0");
    break;
  default:
    // TODO turtaj powinien być zwrócony wyjątek
    break;
  }

  len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");

  f_write(&fil, buffer, len, &bytesWritten);
}

void cmd_set_pin::draw(int print_y) {
  draw_text(command_explorer_first_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "COM. = Signal");

  std::string output_pin_text;
  switch (output_pin) {
  case robot_tool:
    output_pin_text = "Robot tool";
    break;
  case user_led:
    output_pin_text = "User led";
    break;
  }
  draw_text(command_explorer_second_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "Source = " + output_pin_text);

  std::string output_pin_level = set_pin_high ? "high" : "low";

  draw_text(command_explorer_third_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "Level = " + output_pin_level);
}

std::string cmd_set_pin::get_pin_output_text() {
  switch (output_pin) {
  case robot_tool:
    return "robot tool";
  case user_led:
    return "user led";
  }
}

std::string cmd_set_pin::get_pin_level_text() {
  if (set_pin_high) {
    return "high";
  } else {
    return "low";
  }
}