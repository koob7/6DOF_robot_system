/*
 * navigate_robot.c
 *
 *  Created on: Jul 10, 2024
 *      Author: kobie
 */
#include <navigate_robot.h>

  uint16_t max_licz_krokow_osi[6] =
  { 6400 * 2, 6400 * 2, 8000, 6400 * 2, 6400 * 2, 0 };
  double currentPosition[6];
  double givenPosition[6];
  int liczba_krokow_osi[5];
  uint8_t kalibracja_osi[5] = { 1, 1, 1, 1, 1 };
  int givenSteps[6] = { 0, 0, 0, 0, 0, 0 };

struct robot_position robot_home_position = robot_position(20, 0, 20, 0, 0, 0);

int max_range = 39;
int min_range = 13;
int min_y = (-10);
int min_x = (0);

double d1 = 0;
double a2 = 20;
double a3 = 20;
double d6 = 10.5;

void movement::draw(int print_y) {

  std::string move_type =
      (static_cast<mov_circular *>(this) != nullptr) ? "Circ" : "Straight";

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
    //TODO tutaj będzie kiedyś wyjątek
    break;
  }

  draw_text(
  command_explorer_first_setting_x, print_y, command_explorer_line_height,
  command_explorer_file_menu_font, 1, BLACK,
  "MOVE = " + move_type
  );

  draw_text(
  command_explorer_second_setting_x, print_y, command_explorer_line_height,
  command_explorer_file_menu_font, 1, BLACK,
  "TYPE = " + type_string
  );

  draw_text(
  command_explorer_third_setting_x, print_y, command_explorer_line_height,
  command_explorer_file_menu_font, 1, BLACK,
  "SPEED = " + speed_string
  );
}

void cmd_wait::draw(int print_y) {
  draw_text(command_explorer_first_setting_x, print_y,
  command_explorer_line_height, command_explorer_file_menu_font, 1,
  BLACK, "COMAND = Wait");
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

movement::movement(struct robot_position in_target_pos, enum e_speed speed,
    enum e_movement_type movement_type) :
    target_pos(in_target_pos), speed(speed), movement_type(movement_type) {
}
movement::movement() {
  target_pos = robot_position();
  speed = speed_10;
  movement_type = continous;
}
mov_streight::mov_streight(struct robot_position in_target_pos,
    enum e_speed speed, enum e_movement_type movement_type) :
    movement(in_target_pos, speed, movement_type) {
}
mov_streight::mov_streight(std::istringstream& iss) {
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
        //TODO tutaj powinien być wyjątek
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
        //TODO tutaj powinien być wyjątek
        break;
      }
      break;
    default:
      //TODO tutaj powinien być wyjątek
      break;
    }
  }
}

mov_circular::mov_circular(std::istringstream& iss) {
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
        //TODO tutaj powinien być wyjątek
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
        //TODO tutaj powinien być wyjątek
        break;
      }
      break;
    default:
      //TODO tutaj powinien być wyjątek
      break;
    }
  }
}

cmd_wait::cmd_wait(std::istringstream& iss) {
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
        //TODO tutaj powinien być wyjątek
        break;
      }
      break;
    default:
      //TODO tutaj powinien być wyjątek
      break;
    }
  }
}

cmd_set_pin::cmd_set_pin(std::istringstream& iss) {
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
        //TODO tutaj powinien być wyjątek
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
        //TODO tutaj powinien być wyjątek
        break;
      }
      break;
    default:
      //TODO tutaj powinien być wyjątek
      break;
    }
  }
}

mov_circular::mov_circular(struct robot_position in_help_pos,
    struct robot_position in_target_pos, enum e_speed speed,
    enum e_movement_type movement_type) :
    movement(in_target_pos, speed, movement_type), help_pos(in_help_pos) {
}

cmd_wait::cmd_wait(enum e_wait_time wait_time) :
    wait_time(wait_time) {
}
cmd_set_pin::cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high) :
    output_pin(output_pin), set_pin_high(set_pin_high) {
}

void mov_streight::update_command(struct robot_position in_target_pos,
    enum e_speed in_speed, enum e_movement_type in_movement_type) {
  target_pos = in_target_pos;
  speed = in_speed;
  movement_type = in_movement_type;
}

void mov_circular::update_command(struct robot_position in_help_pos,
    struct robot_position in_target_pos, enum e_speed in_speed,
    enum e_movement_type in_movement_type) {
  help_pos = in_help_pos;
  target_pos = in_target_pos;
  speed = in_speed;
  movement_type = in_movement_type;
}

void cmd_wait::update_command(enum e_wait_time in_wait_time) {
  wait_time = in_wait_time;
}

void cmd_set_pin::update_command(enum e_output_pin in_output_pin,
    bool in_set_pin_high) {
  output_pin = in_output_pin;
  set_pin_high = in_set_pin_high;
}

void cmd_set_pin::draw(int print_y) {
  draw_text(command_explorer_first_setting_x, print_y,
  command_explorer_line_height, command_explorer_file_menu_font, 1,
  BLACK, "COMAND = Signal");

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
  BLACK, "SOURCE = " + output_pin_text);
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

  switch (speed) {
  case speed_10:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S10 ");
    break;
  case speed_50:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S50 ");
    break;
  case speed_100:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S100 ");
    break;
  }

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

  switch (speed) {
  case speed_10:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S10 ");
    break;
  case speed_50:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S50 ");
    break;
  case speed_100:
    len += snprintf(buffer + len, sizeof(buffer) - len, "S100 ");
    break;
  }

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
    //TODO turtaj powinien być zwrócony wyjątek
    break;
  }

  len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");

  f_write(&fil, buffer, len, &bytesWritten);
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
    //TODO turtaj powinien być zwrócony wyjątek
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
    //TODO turtaj powinien być zwrócony wyjątek
    break;
  }

  len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");

  f_write(&fil, buffer, len, &bytesWritten);
}

void kalibracja_robota(int givenSteps[6], int liczba_krokow_osi[5],
    uint8_t kalibracja_osi[5]) {
  // kalibracja osi 2
  if (!HAL_GPIO_ReadPin(M2_S_GPIO_Port, M2_S_Pin))
    givenSteps[1] = 1400;
  while (givenSteps[1] != liczba_krokow_osi[1]) {
  }
  kalibracja_osi[1] = 0;
  givenSteps[1] = -90000;
  // ustawienie pozycji 90 osi 2
  while (kalibracja_osi[1] == 0) {
  }
  givenSteps[1] = 6400;
  while (givenSteps[1] != liczba_krokow_osi[1]) {
  }

  // kalibracja osi 3
  if (!HAL_GPIO_ReadPin(M3_S_GPIO_Port, M3_S_Pin))
    givenSteps[2] = 2600;
  while (givenSteps[2] != liczba_krokow_osi[2]) {
  }
  kalibracja_osi[2] = 0;
  givenSteps[2] = -90000;
  // ustawienie pozycji zero osi 3
  while (kalibracja_osi[2] == 0) {
  }
  liczba_krokow_osi[2] = 0; // 180
  while (givenSteps[2] != liczba_krokow_osi[2]) {
  }
  liczba_krokow_osi[2] = 0;
  givenSteps[2] = 0;

  // kalibracja osi 1
  if (!HAL_GPIO_ReadPin(M1_S_GPIO_Port, M1_S_Pin))
    givenSteps[0] = 1400;
  while (givenSteps[0] != liczba_krokow_osi[0]) {
  }
  kalibracja_osi[0] = 0;
  givenSteps[0] = -90000;
  // ustawienie pozycji zero osi 1
  while (kalibracja_osi[0] == 0) {
  }
  liczba_krokow_osi[0] = 220;
  while (givenSteps[0] != liczba_krokow_osi[0]) {
  }
  liczba_krokow_osi[0] = 0;
  givenSteps[0] = 6400;

  // kalibracja servo
  givenSteps[5] = 900;

  // kalibracja osi 4
  if (!HAL_GPIO_ReadPin(M4_S_GPIO_Port, M4_S_Pin))
    givenSteps[3] = 1400;
  while (givenSteps[3] != liczba_krokow_osi[3]) {
  }
  kalibracja_osi[3] = 0;
  givenSteps[3] = -90000;
  // ustawienie pozycji 0 osi 4
  while (kalibracja_osi[3] == 0) {
  }
  givenSteps[3] = 6400;

  // kalibracja osi 5
  if (!HAL_GPIO_ReadPin(M5_S_GPIO_Port, M5_S_Pin))
    givenSteps[4] = 4500;
  while (givenSteps[4] != liczba_krokow_osi[4]) {
  }
  kalibracja_osi[4] = 0;
  givenSteps[4] = -90000;

  // ustawienie pozycji 0 osi 5
  while (kalibracja_osi[4] == 0) {
  }
  givenSteps[4] = 6400;

  givenSteps[2] = 6400;
  while (givenSteps[2] != liczba_krokow_osi[2]
      || givenSteps[3] != liczba_krokow_osi[3]
      || givenSteps[4] != liczba_krokow_osi[4]) {
  }
}

void licz_kroki(double givenPosition[6], int givenSteps[6],
    double currentPosition[6]) {
  double x = givenPosition[0];
  double y = givenPosition[1];
  double z = givenPosition[2];
  double given_phi = givenPosition[3];
  double given_theta = givenPosition[4];
  double given_psi = givenPosition[5];
  double theta[6];
  double phi = given_phi * M_PI / 180;
  double theta_rotation = given_theta * M_PI / 180;
  double psi = given_psi * M_PI / 180;

  double r11 = cos(phi) * sin(theta_rotation) * cos(psi)
      + sin(phi) * sin(theta_rotation);
  double r21 = sin(phi) * sin(theta_rotation) * cos(psi) - cos(phi) * sin(psi);
  double r31 = cos(theta_rotation) * cos(psi);

  double r12 = cos(phi) * cos(theta_rotation);
  double r22 = sin(phi) * cos(theta_rotation);
  double r32 = -sin(theta_rotation);

  double r13 = cos(phi) * sin(theta_rotation) * sin(psi) - sin(phi) * cos(psi);
  double r23 = sin(phi) * sin(theta_rotation) * sin(psi)
      + cos(phi) * cos(theta_rotation);
  double r33 = cos(theta_rotation) * sin(psi);

  double Wx = x - d6 * r13;
  double Wy = y - d6 * r23;
  double Wz = z - d6 * r33;
  double r = (sqrt(Wx * Wx + Wy * Wy));
  double s = Wz - d1;

  theta[0] = atan2(Wy, Wx);
  double cos_theta2 = (r * r + s * s - a2 * a2 - a3 * a3) / (2 * a2 * a3);
  theta[2] = atan2(-sqrt(1 - cos_theta2 * cos_theta2), cos_theta2);
  double k1 = a2 + a3 * cos(theta[2]);
  double k2 = a3 * sin(theta[2]);
  theta[1] = atan2(s, r) - atan2(k2, k1);

  theta[2] += M_PI / 2;

  double ax = r13 * cosl(theta[0]) * cosl(theta[1] + theta[2])
      + r23 * cosl(theta[1] + theta[2]) * sinl(theta[0])
      + r33 * sinl(theta[1] + theta[2]);
  double ay = -r23 * cosl(theta[0]) + r13 * sinl(theta[0]);
  double az = -r33 * cosl(theta[1] + theta[2])
      + r13 * cosl(theta[0]) * sinl(theta[1] + theta[2])
      + r23 * sinl(theta[0]) * sinl(theta[1] + theta[2]);
  double sz = -r32 * cosl(theta[1] + theta[2])
      + r12 * cosl(theta[0]) * sinl(theta[1] + theta[2])
      + r22 * sinl(theta[0]) * sinl(theta[1] + theta[2]);
  double nz = -r31 * cosl(theta[1] + theta[2])
      + r11 * cosl(theta[0]) * sinl(theta[1] + theta[2])
      + r21 * sinl(theta[0]) * sinl(theta[1] + theta[2]);

  double epsilon = 0.5;

  if (ax == 0)
    ax += epsilon;
  if (ay == 0)
    ay += epsilon;

  if (1) { // Wz>20
    theta[3] = atan2(-ay, -ax);
    theta[4] = atan2(-sqrt(ax * ax + ay * ay), az);
    theta[5] = atan2(-sz, nz);

  } else {
    theta[3] = atan2(-ay, ax);
    theta[4] = atan2(sqrt(ax * ax + ay * ay), az);
    theta[5] = atan2(sz, -nz);
  }

  theta[0] += M_PI / 2;
  theta[1] = M_PI - theta[1];
  theta[2] = -(theta[2] - M_PI / 2);
  theta[3] += M_PI / 2;
  theta[4] = M_PI / 2 - theta[4];
  theta[5] = M_PI - theta[5];

  for (int i = 0; i < 5; i++)
    theta[i] = theta[i] * 180 / M_PI * 128 / 1.8;
  theta[5] = theta[5] * 180 / M_PI * 10;

  if (cos_theta2 <= 1 && // pierwiastek nie może mieć wartości ujemnych
      sqrt(s * s + r * r) > min_range && sqrt(s * s + r * r) < max_range && // warunek który musi być spełniony żeby pozycja była
                                                                             // osiągalna ze względu na zasięg ramion robota
      theta[0] >= 0 && theta[0] <= 12000 &&                  // 0-180 stopni
      theta[1] >= 0 && theta[1] <= 12000 && // 0-180 stopni
      theta[2] >= 0 && theta[2] <= 10168 && // 0-143 stopni
      theta[3] >= 0 && theta[3] <= 21333 && // 0-300 stopni
      theta[4] >= 0 && theta[4] <= 12000)   // 0-180 stopni

          {
    for (int i = 0; i < 6; i++) {
      givenSteps[i] = theta[i];
      currentPosition[i] = givenPosition[i];
    }
  } else {
    theta[5] = theta[5];
  }
}

void simpleMoveMotor(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

void moveMotorWithPosition(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
    int *stepCounter, int8_t factor) {
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
  (*stepCounter) += factor;
}

void setDuration(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, int currentSteps,
    int givenSteps, int8_t *factor) {
  if (givenSteps > currentSteps) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET); // jeżeli kierunek ustawiony jest na set
                                                        // to ramię odjeżdża od krańcówki
    (*factor) = 1;
  } else {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET); // jeżeli kierunek ustawiony jest na reset
                                                      // to ramię jedzie w stronę krańcówki
    (*factor) = -1;
  }
}

void handle_move_interrupt(int *givenSteps, int *liczba_krokow_osi, int8_t *factor) {
        // Obsługuje ruch silników M1, M2, M3, M4, M5, M6

        // Sprawdza i aktualizuje M1
        if (givenSteps[0] != liczba_krokow_osi[0]) {
            setDuration(M1_DIR_GPIO_Port, M1_DIR_Pin, liczba_krokow_osi[0], givenSteps[0], &factor[0]);
            moveMotorWithPosition(M1_STEP_GPIO_Port, M1_STEP_Pin, &liczba_krokow_osi[0], factor[0]);
        }

        // Sprawdza i aktualizuje M2
        if (givenSteps[1] != liczba_krokow_osi[1]) {
            setDuration(M2_DIR_GPIO_Port, M2_DIR_Pin, liczba_krokow_osi[1], givenSteps[1], &factor[1]);
            moveMotorWithPosition(M2_STEP_GPIO_Port, M2_STEP_Pin, &liczba_krokow_osi[1], factor[1]);
        }

        // Sprawdza i aktualizuje M3 i M5
        if (givenSteps[2] != liczba_krokow_osi[2]) {
            setDuration(M3_DIR_GPIO_Port, M3_DIR_Pin, liczba_krokow_osi[2], givenSteps[2], &factor[2]);
            setDuration(M5_DIR_GPIO_Port, M5_DIR_Pin, liczba_krokow_osi[2], givenSteps[2], &factor[2]);
            moveMotorWithPosition(M3_STEP_GPIO_Port, M3_STEP_Pin, &liczba_krokow_osi[2], factor[2]);
            // Opcjonalny delay
            simpleMoveMotor(M5_STEP_GPIO_Port, M5_STEP_Pin);
            simpleMoveMotor(M3_STEP_GPIO_Port, M3_STEP_Pin);
        }

        // Sprawdza i aktualizuje M4
        if (givenSteps[3] != liczba_krokow_osi[3]) {
            setDuration(M4_DIR_GPIO_Port, M4_DIR_Pin, liczba_krokow_osi[3], givenSteps[3], &factor[3]);
            moveMotorWithPosition(M4_STEP_GPIO_Port, M4_STEP_Pin, &liczba_krokow_osi[3], factor[3]);
        }

        // Sprawdza i aktualizuje M5
        if (givenSteps[4] != liczba_krokow_osi[4]) {
            setDuration(M5_DIR_GPIO_Port, M5_DIR_Pin, liczba_krokow_osi[4], givenSteps[4], &factor[4]);
            moveMotorWithPosition(M5_STEP_GPIO_Port, M5_STEP_Pin, &liczba_krokow_osi[4], factor[4]);
            // Opcjonalny delay
            simpleMoveMotor(M5_STEP_GPIO_Port, M5_STEP_Pin);
        }

        // Ustawienia dla M6
        set_ang(givenSteps[5], 0);
        HAL_GPIO_WritePin(M6_STEP_GPIO_Port, M6_STEP_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(M6_STEP_GPIO_Port, M6_STEP_Pin, GPIO_PIN_RESET);
}

void handle_limit_switch_interrupt(uint16_t GPIO_Pin, uint8_t *kalibracja_osi, int *givenSteps, int *liczba_krokow_osi) {
    // Sprawdzamy, który pin GPIO został aktywowany i czy odpowiednia oś nie jest jeszcze skalibrowana
    if (GPIO_Pin == M1_S_Pin && kalibracja_osi[0] == 0) {
        liczba_krokow_osi[0] = 0;
        givenSteps[0] = 0;
        kalibracja_osi[0] = 1;
    }
    if (GPIO_Pin == M2_S_Pin && kalibracja_osi[1] == 0) {
        liczba_krokow_osi[1] = 10; // Możesz zmienić na 20, jeśli potrzebujesz
        givenSteps[1] = 10;        // Możesz zmienić na 20, jeśli potrzebujesz
        kalibracja_osi[1] = 1;
    }
    if (GPIO_Pin == M3_S_Pin && kalibracja_osi[2] == 0) {
        liczba_krokow_osi[2] = 0;
        givenSteps[2] = 0;
        kalibracja_osi[2] = 1;
    }
    if (GPIO_Pin == M4_S_Pin && kalibracja_osi[3] == 0) {
        liczba_krokow_osi[3] = 300;
        givenSteps[3] = 300;
        kalibracja_osi[3] = 1;
    }
    if (GPIO_Pin == M5_S_Pin && kalibracja_osi[4] == 0) {
        liczba_krokow_osi[4] = 1600; // Możesz zmienić na 1790, jeśli potrzebujesz
        givenSteps[4] = 1600;        // Możesz zmienić na 1790, jeśli potrzebujesz
        kalibracja_osi[4] = 1;
    }
}
