#include "mov_streight.h"

mov_streight::mov_streight(struct robot_position in_target_pos,
                           enum e_speed speed,
                           enum e_movement_type movement_type)
    : movement(in_target_pos, speed, movement_type) {}

mov_streight::mov_streight(std::istringstream &iss) {
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

mov_streight::mov_streight(const mov_streight &other) : movement(other) {}

void mov_streight::update_command(mov_streight in_object) {
  target_pos = in_object.target_pos;
  speed = in_object.speed;
  movement_type = in_object.movement_type;
}

void mov_streight::update_command(struct robot_position in_target_pos,
                                  enum e_speed in_speed,
                                  enum e_movement_type in_movement_type) {
  target_pos = in_target_pos;
  speed = in_speed;
  movement_type = in_movement_type;
}

bool mov_streight::perform_task() {
  if (task_progres < task_steps) {
    if (movement_divider > 1)
      movement_divider = 1;
    struct robot_position tmp_position = calculate_offset_on_line();
    givenPosition[0] = tmp_position.x;
    givenPosition[1] = tmp_position.y;
    givenPosition[2] = tmp_position.z;
    givenPosition[3] = tmp_position.a;
    givenPosition[4] = tmp_position.b;
    givenPosition[5] = tmp_position.c;
    if (!licz_kroki(givenPosition, givenSteps, currentPosition)) {
      return false;
    }
    movement_divider += delta_movement_divider;
    task_progres++;
  }
  return true;
}

void mov_streight::prepare_task(
    std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
    int position_in_vector) {
  bool was_previous = false;
  struct robot_position previous_robot_position;
  if (robot_was_moved) {
    // obliczamy ruch z aktualnej pozycji robota
    previous_robot_position = robot_position(
        currentPosition[0], currentPosition[1], currentPosition[2],
        currentPosition[3], currentPosition[4], currentPosition[5]);
    calculate_move_from_poin_to_target(previous_robot_position);
  } else {
    // szukamy poprzedniego punktu - jeżeli nie ma korzystamy z aktualnej
    // pozycji

    for (int i = position_in_vector - 1; i > -1; i--) {

      if ((*(first_command_iteratort + i))
              ->get_target_position(previous_robot_position)) {
        // ta obsługa wykona się jeżeli pobierzemy poprawnie pozycję:
        calculate_move_from_poin_to_target(previous_robot_position);
        was_previous = true;
        break;
      }
    }
    // tutaj jest obłsuga jeżeli robot się nie ruszył i nie ma poprzedniego
    // punktu - korzystamy z obecnej pozycji

    if (!was_previous) {
      previous_robot_position = robot_position(
          currentPosition[0], currentPosition[1], currentPosition[2],
          currentPosition[3], currentPosition[4], currentPosition[5]);
      calculate_move_from_poin_to_target(previous_robot_position);
    }
  }

  robot_was_moved = false;
  task_progres = 0;
}

void mov_streight::save_to_file(FIL &fil) {
  char buffer[256];
  int len = 0;
  UINT bytesWritten;

  len += snprintf(buffer + len, sizeof(buffer) - len, "G1 ");

  len += snprintf(buffer + len, sizeof(buffer) - len, "X%.2f ", target_pos.x);
  len += snprintf(buffer + len, sizeof(buffer) - len, "Y%.2f ", target_pos.y);
  len += snprintf(buffer + len, sizeof(buffer) - len, "Z%.2f ", target_pos.z);
  len += snprintf(buffer + len, sizeof(buffer) - len, "A%.2f ", target_pos.a);
  len += snprintf(buffer + len, sizeof(buffer) - len, "B%.2f ", target_pos.b);
  len += snprintf(buffer + len, sizeof(buffer) - len, "C%.2f ", target_pos.c);

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

void mov_streight::calculate_move_from_poin_to_target(
    struct robot_position start_position) {
  update_vector(start_position, target_pos);
  distance_AB = calculate_distance(start_position, target_pos);
  delta_movement_divider = calculate_delta(distance_AB);
  task_steps = count_segments(distance_AB);
  movement_divider = delta_movement_divider;
}

void mov_streight::update_vector(const struct robot_position &A,
                                 const struct robot_position &B) {
  vect_AB_x = (B.x - A.x);
  vect_AB_y = (B.y - A.y);
  vect_AB_z = (B.z - A.z);
  angle_AB_a = (B.a - A.a);
  angle_AB_b = (B.b - A.b);
  angle_AB_c = (B.c - A.c);
}

struct robot_position mov_streight::calculate_offset_on_line() {
  struct robot_position position;
  double t = (1 - movement_divider);
  position.x = target_pos.x - t * vect_AB_x;
  position.y = target_pos.y - t * vect_AB_y;
  position.z = target_pos.z - t * vect_AB_z;
  position.a = target_pos.a - t * angle_AB_a;
  position.b = target_pos.b - t * angle_AB_b;
  position.c = target_pos.c - t * angle_AB_c;
  return position;
}

double mov_streight::calculate_distance(const struct robot_position &A,
                                        const struct robot_position &B) {
  return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2));
}

double mov_streight::calculate_delta(double distance) {
  double speed_divider;
  switch (speed) {
  case e_speed::speed_10:
    speed_divider = 0.001;
    break;
  case e_speed::speed_50:
    speed_divider = 0.005;
    break;
  case e_speed::speed_100:
    speed_divider = 0.01;
    break;
  }
  return speed_divider / distance;
}

int mov_streight::count_segments(double tmp_distance) {
  // Liczymy liczbę odcinków o długości 1 cm, zaokrąglając w górę
  double speed_divider;
  switch (speed) {
  case e_speed::speed_10:
    speed_divider = 0.001;
    break;
  case e_speed::speed_50:
    speed_divider = 0.005;
    break;
  case e_speed::speed_100:
    speed_divider = 0.01;
    break;
  }
  return static_cast<int>(ceil(tmp_distance / speed_divider));
}
