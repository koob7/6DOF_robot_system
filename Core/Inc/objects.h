/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */

#ifndef INC_OBJECTS_H_
#define INC_OBJECTS_H_

#include "display_ssd1963.h"
#include "fatfs.h"
#include "menu_parts.h"
#include "navigate_robot.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>

#define forget_when_hiden true

#define project_explorer_start_pos_x 200
#define project_explorer_start_pos_y 208
#define project_explorer_line_height 28
#define project_explorer_line_space 16
#define project_explorer_num_files_on_page 6
#define project_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)

#define command_explorer_start_pos_x 200
#define command_explorer_start_pos_y 208
#define command_explorer_line_height 28
#define command_explorer_line_space 16
#define command_explorer_num_files_on_page 6
#define command_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)
#define command_explorer_first_setting_x 260
#define command_explorer_second_setting_x 370
#define command_explorer_third_setting_x 480

class menu_segment {
  std::vector<std::shared_ptr<menu_part>> top_parts;
  std::vector<std::shared_ptr<menu_part>> background_parts;
  std::vector<button> buttons;

public:
  void draw();
  void reduce_vector_size();
  void add_background_part(std::shared_ptr<menu_part> part) {
    background_parts.push_back(part);
  }
  void add_part(std::shared_ptr<menu_part> part) {
    top_parts.push_back(part);
  }
  void add_part(button o_button) {
    buttons.push_back(o_button);
  }
  int check_pressed(int x, int y);
  void update_text(int id, std::string text);
};

class projects_explorer {
public:
  enum sort_option {
    by_name, by_size, by_date,
  };

private:
  FATFS file_system;
  DIR directory;
  FILINFO fno;
  std::vector<FILINFO> sd_files;
  bool initialized;
  int first_file_to_display = 0;
  int last_file_to_display = 0;

  enum sort_option option = by_date;
  bool sort_ascending = false;
  int selected_file = -1; // wartość ujemna oznacza brak wybranego pliku
  button page_up_btn = button(0, 140, 158, 40, 40, 0xD6BA, 20); // nawigacja
                                                                // góra
  button page_down_btn = button(1, 140, 425, 40, 40, 0xD6BA, 20); // nawigacja dół

  std::string format_date(WORD fdate);
  void get_files();
  void sort_files();
  void forget_selected_hiden_file();
  void update_last_file_to_display();
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
      int area_height);


public:
  projects_explorer();
  void create_file(std::string name);
  void set_sort_option(enum sort_option in_option, bool in_sort_ascending);
  std::string get_choosen_file();
  void delete_file();
  void handle_pressed(int x, int y);
  void draw();
};

class project_editor {

  void forget_selected_hiden_command();
  void update_last_command_to_display();
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
      int area_height);

public:
  int first_command_to_display = 0;
  int last_command_to_display = 0;
  int selected_command = -1; // wartość ujemna oznacza brak wybranego pliku
  button page_up_btn = button(0, 140, 158, 40, 40, 0xD6BA, 20); // nawigacja góra
  button page_down_btn = button(1, 140, 425, 40, 40, 0xD6BA, 20); // nawigacja dół
  std::vector<std::shared_ptr<command>> commands;
  project_editor();
  void draw();
  void read_commands();
  void handle_pressed(int x, int y);
  void add_part(std::shared_ptr<command> in_cmd) {
    commands.push_back(in_cmd);
  }
  bool perform_task();
  void insert_command(std::shared_ptr<command> in_cmd);
  void remove_command();
  bool open_file(std::string file_name);
  void save_changes_file();
};

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

#endif /* INC_OBJECTS_H_ */
