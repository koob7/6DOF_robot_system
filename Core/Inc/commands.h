
#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_
#include <navigate_robot.h>

class command {
public:
  enum e_command_type {
    mov_streight,
    mov_circular,
    mov_com_end,
    cmd_wait,
    cmd_set_pin,
    functional_com_end,
    default_command,
  };

  int task_progres = 0;
  bool was_error = false;
  int task_steps = 1; // task steps nigdy nie może być zerem - zadanie zawsze
                      // musi mieć choć jeden etap do wykonania

  virtual void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector) = 0; // funkcja prepare_task jest wywoływana tylko
                                   // jeżeli robot_was_moved==true lub gdy
                                   // pierwszy raz wywołujemy komendę
  virtual bool perform_task() = 0; // zwraca true jak wykona się cała komenda
  virtual void draw(int print_y) = 0;
  virtual void save_to_file(FIL &fil) = 0;

  virtual enum e_command_type get_command_type() = 0;

  virtual void reset_task_progres() { task_progres = 0; }
  bool is_task_completed() { return task_progres == task_steps; }
  bool check_was_error() { return was_error; }
  void clear_error() { was_error = false; }
  void notice_error_occured() { was_error = true; }

  virtual bool get_target_position(struct robot_position &tmp_position) {
    return false;
  }
};

class movement : public command {
public:
  enum e_movement_type {
    continous,
    step_by_step,
  };

  enum e_speed {
    // to są wartości procentowe
    speed_10,
    speed_50,
    speed_100,
  };

  struct robot_position target_pos;
  enum e_speed speed;
  enum e_movement_type movement_type;

  movement();
  movement(struct robot_position in_target_pos, enum e_speed speed,
           enum e_movement_type movement_type);
  movement(const movement &other);

  void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector) {}

  void draw(int print_y) {}
  void draw_movement(int print_y, bool ciruclar_movement);

  std::string get_speed_text();
  std::string get_movement_type_text();

  struct robot_position get_target_position() { return target_pos; }
  enum e_speed get_speed() { return speed; }
  enum e_movement_type get_movement_type() { return movement_type; }

  bool get_target_position(struct robot_position &tmp_position) {
    tmp_position = target_pos;
    return true;
  }

  void update_speed(enum e_speed in_speed) { speed = in_speed; }
  void update_movement_type(enum e_movement_type in_movement_type) {
    movement_type = in_movement_type;
  }
  void update_target_pos(struct robot_position in_target_pos) {
    target_pos = in_target_pos;
  }
};

#endif
