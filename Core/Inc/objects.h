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
#include <algorithm>
#include <iomanip>
#include <sstream>

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
  void add_part(std::shared_ptr<menu_part> part) { top_parts.push_back(part); }
  void add_part(button o_button) { buttons.push_back(o_button); }
  int check_pressed(int x, int y);
  void update_text(int id, std::string text);
};

class projects_explorer {
public:
  enum sort_option {
    by_name,
    by_size,
    by_date,
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
  button page_down_btn =
      button(1, 140, 425, 40, 40, 0xD6BA, 20); // nawigacja dół

  std::string format_date(WORD fdate);
  void get_files();
  void sort_files();
  void update_last_file_to_display();
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
                          int area_height);
  void forget_selected_hiden_file();

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
public:
  class command {
  public:
    virtual bool perform_task() = 0;
    virtual void draw(int print_y, bool selected_point) = 0;
    //std::string getType(){return typeid(*this).name();}
  };

  class movement : public command {
  public:
    enum e_movement_type {
      continous,
      step_by_step,
    };
    float target_x;
    float target_y;
    float target_z;
    float target_a;
    float target_b;
    float target_c;
    uint8_t speed;
    enum e_movement_type movement_type;
    movement(float target_x, float target_y, float target_z, float target_a,
             float target_b, float target_c, uint8_t speed,
             enum e_movement_type movement_type);
  };

  class mov_streight : public movement {
  public:
	mov_streight(float target_x, float target_y, float target_z, float target_a,
                 float target_b, float target_c, uint8_t speed,
                 enum e_movement_type movement_type);
    bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                         // robota, zwraca true jeżeli osiągnięto cel
    void draw(int print_y, bool selected_point);
    void update_command(float in_target_x, float in_target_y, float in_target_z, float in_target_a,
            float in_target_b, float in_target_c, uint8_t in_speed,
            enum e_movement_type in_movement_type);
  };

  class mov_circular : public movement {
  public:
    float help_x;
    float help_y;
    float help_z;
    float help_a;
    float help_b;
    float help_c;
    mov_circular(float target_x, float target_y, float target_z, float target_a,
                 float target_b, float target_c, float help_x, float help_y,
                 float help_z, float help_a, float help_b, float help_c,
                 uint8_t speed, enum e_movement_type movement_type);
    bool perform_task(); // tutaj funkcja będzie ustawiała kolejne pozycje
                         // robota, zwraca true jeżeli osiągnięto cel
    void draw(int print_y, bool selected_point);
    void update_command(float in_target_x, float in_target_y, float in_target_z, float in_target_a,
            float in_target_b, float in_target_c, float in_help_x, float in_help_y,
            float in_help_z, float in_help_a, float in_help_b, float in_help_c,
            uint8_t in_speed, enum e_movement_type in_movement_type);
  };

  class cmd_wait : public command {
  public:
    uint16_t time_milisecond;
    cmd_wait(uint16_t time_milisecond);
    cmd_wait(std::string command_line);
    bool perform_task(); // tutaj będzie odczekiwany mały odstęp czasu,  zwraca
                         // true jeżeli osiągnięto cel
    void draw(int print_y, bool selected_point);
    void update_command(uint16_t in_time_milisecond);
  };

  class cmd_set_pin : public command {
  public:
    enum e_output_pin {
      robot_tool,
      user_led,
    };
    enum e_output_pin output_pin;
    bool set_pin_high;
    cmd_set_pin(enum e_output_pin output_pin, bool set_pin_high);
    cmd_set_pin(std::string command_line);
    bool perform_task(); // tutaj będzie ustawiana wartość pinu w zależności od
                         // zmiennej set_pin_high, zwraca true jeżeli poprawnie
                         // ustawiono pin
    void draw(int print_y, bool selected_point);
    void update_command(enum e_output_pin in_output_pin, bool in_set_pin_high);
  };

  int first_command_to_display = 0;
  int last_command_to_display = 0;
  int selected_command = -1; // wartość ujemna oznacza brak wybranego pliku
  button page_up_btn = button(0, 140, 158, 40, 40, 0xD6BA, 20); // nawigacja góra
  button page_down_btn =
  button(1, 140, 425, 40, 40, 0xD6BA, 20); // nawigacja dół
  std::vector<std::shared_ptr<command>> commands;
  project_editor();
  void draw();
  void read_commands();
  void handle_pressed(int x, int y);
  void add_part(std::shared_ptr<command> in_cmd) { commands.push_back(in_cmd);}
  void insert_command(std::shared_ptr<command> in_cmd);
  void remove_command();

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
