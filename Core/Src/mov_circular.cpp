#include "mov_circular.h"

mov_circular::mov_circular(struct robot_position in_help_pos,
                           struct robot_position in_target_pos,
                           enum e_speed speed,
                           enum e_movement_type movement_type)
    : movement(in_target_pos, speed, movement_type), help_pos(in_help_pos) {}

mov_circular::mov_circular(std::istringstream &iss) {
  char prefix;
  double value;
  while (iss >> prefix >> value) {
    switch (prefix) {
    case 'X':
      target_pos.x = value;
      break;
    case 'Y':
      target_pos.y = value;
      break;
    case 'Z':
      target_pos.z = value;
      break;
    case 'A':
      target_pos.a = value;
      break;
    case 'B':
      target_pos.b = value;
      break;
    case 'C':
      target_pos.c = value;
      break;
    case 'I':
      target_pos.x = value;
      break;
    case 'J':
      target_pos.y = value;
      break;
    case 'E':
      target_pos.z = value;
      break;
    case 'K':
      target_pos.a = value;
      break;
    case 'L':
      target_pos.b = value;
      break;
    case 'O':
      target_pos.c = value;
      break;
    case 'S':
      switch (static_cast<int>(value)) {
      case 10:
        speed = speed_10;
        break;
      case 50:
        speed = speed_50;
        break;
      case 100:
        speed = speed_100;
        break;
      default:
        // TODO tutaj powinien być wyjątek
        break;
      }
      break;
    case 'M':
      switch (static_cast<int>(value)) {
      case 0:
        movement_type = continous;
        break;
      case 1:
        movement_type = step_by_step;
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

mov_circular::mov_circular(const mov_circular &other)
    : movement(other), help_pos(other.help_pos) {}

void mov_circular::update_command(mov_circular in_object) {
  target_pos = in_object.target_pos;
  help_pos = in_object.help_pos;
  speed = in_object.speed;
  movement_type = in_object.movement_type;
}

void mov_circular::update_command(struct robot_position in_help_pos,
                                  struct robot_position in_target_pos,
                                  enum e_speed in_speed,
                                  enum e_movement_type in_movement_type) {
  help_pos = in_help_pos;
  target_pos = in_target_pos;
  speed = in_speed;
  movement_type = in_movement_type;
}

bool mov_circular::perform_task() {
  task_progres++;
  return true;
}

void mov_circular::prepare_task(
    std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
    int position_in_vector) {

  // tymczasowa obsługa - ustawiamy żeby zadanie wykonywało sie tak samo jak
  // ruch prosty

  // szkic docelowej obsługi  - do poprawy !!!
  //   struct robot_position previous_robot_position;
  //   for (int i = position_in_vector-1; i >-1; i--) {
  //           try {
  //             previous_robot_position = get_target_position();
  //             //tutaj obliczanie ruchu kołowego jeżeli znaleźliśmy poprzednią
  //             pozycję return;
  //           } catch (const std::exception& e) {
  //             //tutaj wpadamy jeżli poprzedni punkt jest innego typu niż
  //             movement task_progres=0; task_steps=... robot_was_moved =
  //             false;//ustawiamy że jesteśmy pierwszym punktem tylko gdy
  //             faktycznie wykonamy operację
  //           }
  //       }
  //   //tutaj zaczyna się obsługa jeżeli nie było wcześniej komendy typu
  //   movement
}

void mov_circular::save_to_file(FIL &fil) {
  char buffer[256];
  int len = 0;
  UINT bytesWritten;

  len += snprintf(buffer + len, sizeof(buffer) - len, "G2 ");

  len += snprintf(buffer + len, sizeof(buffer) - len, "X%.2f ", target_pos.x);
  len += snprintf(buffer + len, sizeof(buffer) - len, "Y%.2f ", target_pos.y);
  len += snprintf(buffer + len, sizeof(buffer) - len, "Z%.2f ", target_pos.z);
  len += snprintf(buffer + len, sizeof(buffer) - len, "A%.2f ", target_pos.a);
  len += snprintf(buffer + len, sizeof(buffer) - len, "B%.2f ", target_pos.b);
  len += snprintf(buffer + len, sizeof(buffer) - len, "C%.2f ", target_pos.c);

  len += snprintf(buffer + len, sizeof(buffer) - len, "I%.2f ", help_pos.x);
  len += snprintf(buffer + len, sizeof(buffer) - len, "J%.2f ", help_pos.y);
  len += snprintf(buffer + len, sizeof(buffer) - len, "E%.2f ", help_pos.z);
  len += snprintf(buffer + len, sizeof(buffer) - len, "K%.2f ", help_pos.a);
  len += snprintf(buffer + len, sizeof(buffer) - len, "L%.2f ", help_pos.b);
  len += snprintf(buffer + len, sizeof(buffer) - len, "O%.2f ", help_pos.c);

  len += snprintf(buffer + len, sizeof(buffer) - len,
                  ("S" + get_speed_text() + " ").c_str());

  switch (movement_type) {
  case continous:
    len += snprintf(buffer + len, sizeof(buffer) - len, "M0");
    break;
  case step_by_step:
    len += snprintf(buffer + len, sizeof(buffer) - len, "M1");
    break;
  }

  len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");

  f_write(&fil, buffer, len, &bytesWritten);
}