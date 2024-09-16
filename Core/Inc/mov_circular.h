#ifndef INC_MOV_CIRCULAR_H_
#define INC_MOV_CIRCULAR_H_

#include <commands.h>

class mov_circular : public movement {
public:
  struct robot_position help_pos;

  mov_circular(std::istringstream &iss);
  mov_circular(struct robot_position in_help_pos,
               struct robot_position in_target_pos, enum e_speed speed,
               enum e_movement_type movement_type);
  mov_circular() = default;
  mov_circular(const mov_circular &other);

  void update_command(struct robot_position in_help_pos,
                      struct robot_position in_target_pos,
                      enum e_speed in_speed,
                      enum e_movement_type in_movement_type);
  void update_command(mov_circular in_object);
  void update_help_pos(struct robot_position in_help_pos) {
    help_pos = in_help_pos;
  }

  bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel
  void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector);

  void draw(int print_y) { draw_movement(print_y, true); }
  void save_to_file(FIL &fil);

  virtual enum e_command_type get_command_type() {
    return e_command_type::mov_circular;
  }
  struct robot_position get_help_position() { return help_pos; }
};

#endif