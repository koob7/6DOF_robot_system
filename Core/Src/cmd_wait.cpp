#include "cmd_wait.h"

cmd_wait::cmd_wait(enum e_wait_time wait_time) : wait_time(wait_time) {}

cmd_wait::cmd_wait(std::istringstream &iss) {
  char prefix;
  double value;
  while (iss >> prefix >> value) {
    switch (prefix) {
    case 'P':
      switch (static_cast<int>(value)) {
      case 1:
        wait_time = wait_1s;
        break;
      case 5:
        wait_time = wait_5s;
        break;
      case 30:
        wait_time = wait_30s;
        break;
      case 60:
        wait_time = wait_1min;
        break;
      case 300:
        wait_time = wait_5min;
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

cmd_wait::cmd_wait(const cmd_wait &other)
    : command(other), wait_time(other.wait_time) {}

void cmd_wait::update_command(cmd_wait in_object) {
  wait_time = in_object.wait_time;
}

void cmd_wait::update_command(enum e_wait_time in_wait_time) {
  wait_time = in_wait_time;
}

bool cmd_wait::perform_task() {
  task_progres++;
  HAL_Delay(single_wait_time_prescaller);
  return true;
}

void cmd_wait::prepare_task(
    std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
    int position_in_vector) {
  // oczekiwanie będzie wykonywało sie w odstępach zdefiniowanych w #define
  int dividend;
  switch (wait_time) {
  case e_wait_time::wait_1s:
    dividend = 1000;
    break;
  case e_wait_time::wait_5s:
    dividend = 1000 * 5;
    break;
  case e_wait_time::wait_30s:
    dividend = 1000 * 30;
    break;
  case e_wait_time::wait_1min:
    dividend = 1000 * 60;
    break;
  case e_wait_time::wait_5min:
    dividend = 1000 * 60 * 5;
    break;
  }
  task_progres = 0;
  task_steps = dividend / single_wait_time_prescaller;
}

void cmd_wait::save_to_file(FIL &fil) {
  char buffer[64];
  int len = 0;
  UINT bytesWritten;

  len += snprintf(buffer + len, sizeof(buffer) - len, "G4 ");

  switch (wait_time) {
  case wait_1s:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P1");
    break;
  case wait_5s:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P5");
    break;
  case wait_30s:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P30");
    break;
  case wait_1min:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P60");
    break;
  case wait_5min:
    len += snprintf(buffer + len, sizeof(buffer) - len, "P300");
    break;
  default:
    // TODO turtaj powinien być zwrócony wyjątek
    break;
  }

  len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");

  f_write(&fil, buffer, len, &bytesWritten);
}

void cmd_wait::draw(int print_y) {
  draw_text(command_explorer_first_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "COM = Wait");
  std::string wait_time_text;
  switch (wait_time) {
  case wait_1s:
    wait_time_text = "1s";
    break;
  case wait_5s:
    wait_time_text = "5s";
    break;
  case wait_30s:
    wait_time_text = "30s";
    break;
  case wait_1min:
    wait_time_text = "1min";
    break;
  case wait_5min:
    wait_time_text = "5min";
    break;
  }
  draw_text(command_explorer_second_setting_x, print_y,
            command_explorer_line_height, command_explorer_file_menu_font, 1,
            BLACK, "TIME = " + wait_time_text);
}

std::string cmd_wait::get_time_text() {
  switch (wait_time) {
  case wait_1s:
    return "1 second";
  case wait_5s:
    return "5 seconds";
  case wait_30s:
    return "30 seconds";
  case wait_1min:
    return "1 minut";
  case wait_5min:
    return "5 minuts";
  }
  return "fault";
}
