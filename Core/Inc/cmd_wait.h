
#ifndef INC_CMD_WAIT_H_
#define INC_CMD_WAIT_H_

#include <commands.h>

class cmd_wait : public command {
public:
  enum e_wait_time {
    wait_1s,
    wait_5s,
    wait_30s,
    wait_1min,
    wait_5min,
  };

  enum e_wait_time wait_time;

  cmd_wait() = default;
  cmd_wait(std::istringstream &iss);
  cmd_wait(enum e_wait_time wait_time);
  cmd_wait(const cmd_wait &other);

  void update_command(enum e_wait_time wait_time);
  void update_command(cmd_wait in_object);
  void update_time(enum e_wait_time in_wait_time) { wait_time = in_wait_time; }

  void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector);
  bool perform_task(); // tutaj będzie odczekiwany mały odstęp czasu,  zwraca

  void draw(int print_y);
  void save_to_file(FIL &fil);

  virtual enum e_command_type get_command_type() {
    return e_command_type::cmd_wait;
  } // true jeżeli osiągnięto cel
  std::string get_time_text();
};

#endif
