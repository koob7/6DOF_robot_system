#ifndef INC_PROJECT_EDITOR_H_
#define INC_PROJECT_EDITOR_H_

#include "cmd_set_pin.h"
#include "cmd_wait.h"
#include "commands.h"
#include "fatfs.h"
#include "menu_block.h"
#include "mov_circular.h"
#include "mov_streight.h"
#include "navigate_robot.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

class project_editor {

  bool get_commands();
  void forget_selected_hiden_command();
  void update_last_command_to_display();
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
                          int area_height);
  FIL fil;
  bool get_next_command_to_execute();
  void draw_menu_for_next_command_to_execute();

public:
  enum e_project_run_progres {
    pending,
    end_project,
    end_step,
    fault,
  };
  int first_command_to_display = 0;
  int last_command_to_display = 0;
  int selected_command = -1; // wartość ujemna oznacza brak wybranego pliku
  button page_up_btn =
      button(0, 139, 106, 41, 40, 0xD6BA, 20); // nawigacja góra
  button page_down_btn =
      button(1, 139, 405, 41, 40, 0xD6BA, 20); // nawigacja dół
  std::vector<std::shared_ptr<command>> commands;
  std::string file_name;
  project_editor();
  void draw();
  void draw(int command_to_display);
  void handle_pressed(int x, int y);
  void add_part(std::shared_ptr<command> in_cmd) { commands.push_back(in_cmd); }

  std::shared_ptr<command> get_command_to_execute();
  std::shared_ptr<command> get_choosen_command();
  void insert_command(std::shared_ptr<command> in_cmd);
  void remove_command();
  bool open_file(std::string in_file_name);
  void close_file();
  void save_changes_into_file();
  bool check_if_is_choosen() { return selected_command > -1; }
  enum e_project_run_progres execute_project();
  void reset_project_progres();
  void prepare_commands();
};

#endif
