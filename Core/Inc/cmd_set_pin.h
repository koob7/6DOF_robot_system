#ifndef INC_CMD_SET_PIN_H_
#define INC_CMD_SET_PIN_H_

#include <commands.h>

class cmd_set_pin : public command {
public:
  cmd_set_pin() = default;
  enum e_output_pin {
    robot_tool,
    user_led,
  };
  enum e_output_pin output_pin;
  bool set_pin_high;
  cmd_set_pin(std::istringstream &iss);
  cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high);
  cmd_set_pin(const cmd_set_pin &other);

  void update_command(enum e_output_pin in_output_pin, bool in_set_pin_high);
  void update_command(cmd_set_pin in_object);
  void update_pin(enum e_output_pin in_output_pin) {
    output_pin = in_output_pin;
  }
  void update_pin_level(bool in_set_pin_high) {
    set_pin_high = in_set_pin_high;
  }

  void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector);
  bool perform_task(); // tutaj będzie ustawiana wartość pinu w zależności od
                       // zmiennej set_pin_high, zwraca true jeżeli poprawnie
                       // ustawiono pin

  void draw(int print_y);
  void save_to_file(FIL &fil);

  virtual enum e_command_type get_command_type() {
    return e_command_type::cmd_set_pin;
  }
  std::string get_pin_output_text();
  std::string get_pin_level_text();
};

#endif