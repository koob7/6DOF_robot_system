/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */

#ifndef INC_OBJECTS_H_
#define INC_OBJECTS_H_


#include "fatfs.h"
#include "menu_block.h"
#include "menu_popup.h"
#include "navigate_robot.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "commands.h"
#include "mov_streight.h"
#include "mov_circular.h"
#include "cmd_set_pin.h"
#include "cmd_wait.h"

#define forget_when_hiden true

#define project_explorer_start_pos_x 200
#define project_explorer_start_pos_y 138
#define project_explorer_line_height 28
#define project_explorer_line_space 16
#define project_explorer_num_files_on_page 8
#define project_explorer_file_menu_font                                        \
  const_cast<GFXfont *>(_Open_Sans_Bold_14)

extern  FATFS file_system;

class menu_segment {



  std::vector<std::shared_ptr<menu_block>> top_parts;
  std::vector<std::shared_ptr<menu_block>> background_parts;
  std::vector<button> buttons;

public:
  enum e_menu_layer{
    e_top_parts,
    e_background_parts,
    e_buttons,
  };
  void draw();
  void reduce_vector_size();
  void add_background_part(std::shared_ptr<menu_block> part) {
    background_parts.push_back(part);
  }
  void add_part(std::shared_ptr<menu_block> part) {
    top_parts.push_back(part);
  }
  void add_part(button o_button) {
    buttons.push_back(o_button);
  }
  int check_pressed(int x, int y);
  bool check_pressed_button(int x, int y, int id){
    return buttons[id].check_pressed(x, y)>-1;
  }
  void update_text(int id, std::string text, enum e_menu_layer menu_layer = e_menu_layer::e_buttons);
};

class projects_explorer {
public:
  enum sort_option {
    by_name, by_size, by_date,
  };
  std::vector<FILINFO> sd_files;
private:

  DIR directory;
  FILINFO fno;

  bool initialized;
  int first_file_to_display = 0;
  int last_file_to_display = 0;

  enum sort_option option = by_date;
  bool sort_ascending = false;
  int selected_file = -1; // wartość ujemna oznacza brak wybranego pliku
  button page_up_btn = button(0, 139, 106, 41, 40, 0xD6BA, 20); // nawigacja góra
  button page_down_btn = button(1, 139, 405, 41, 40, 0xD6BA, 20); // nawigacja dół

  std::string format_date(WORD fdate);

  void sort_files();
  void forget_selected_hiden_file();
  void update_last_file_to_display();
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
      int area_height);


public:
  void get_files();
  projects_explorer();
  int create_file(std::string name);
  void set_sort_option(enum sort_option in_option, bool in_sort_ascending);
  std::string get_choosen_file();
  bool delete_file();
  void handle_pressed(int x, int y);
  void draw();
  bool check_if_is_choosen(){return selected_file>-1;}
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
