#ifndef INC_MOV_STREIGHT_H_
#define INC_MOV_STREIGHT_H_

#include <commands.h>

class mov_streight : public movement {
  double vect_AB_x = 0;
  double vect_AB_y = 0;
  double vect_AB_z = 0;
  double angle_AB_a = 0;
  double angle_AB_b = 0;
  double angle_AB_c = 0;
  double distance_AB = 0;
  double movement_divider = 0;
  double delta_movement_divider = 0;

public:
  mov_streight() = default;
  mov_streight(struct robot_position in_target_pos, enum e_speed speed,
               enum e_movement_type movement_type);
  mov_streight(std::istringstream &iss);
  mov_streight(const mov_streight &other);

  void update_command(struct robot_position in_target_pos,
                      enum e_speed in_speed,
                      enum e_movement_type in_movement_type);
  void update_command(mov_streight in_object);

  void prepare_task(
      std::vector<std::shared_ptr<command>>::iterator first_command_iteratort,
      int position_in_vector);
  bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                       // robota, zwraca true jeżeli osiągnięto cel

  void draw(int print_y) { draw_movement(print_y, false); }
  void save_to_file(FIL &fil);

  virtual enum e_command_type get_command_type() {
    return e_command_type::mov_streight;
  }
  void reset_task_progres() {
    task_progres = 0;
    movement_divider = delta_movement_divider;
  }

private:
  double calculate_delta(double distance);
  struct robot_position calculate_offset_on_line();
  void update_vector(const struct robot_position &A,
                     const struct robot_position &B);
  double calculate_distance(const struct robot_position &A,
                            const struct robot_position &B);
  int count_segments(double tmp_distance);
  void calculate_move_from_poin_to_target(struct robot_position start_position);
};

#endif