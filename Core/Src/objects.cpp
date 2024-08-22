/*
 * objects.cpp
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#include "objects.h"

void menu_segment::draw() {
  for (auto part : background_parts) {
    part->draw();
  }
  for (auto o_button : buttons) {
    o_button.draw();
  }
  for (auto part : top_parts) {
    part->draw();
  }
}

void menu_segment::reduce_vector_size() {
  background_parts.shrink_to_fit();
  top_parts.shrink_to_fit();
  buttons.shrink_to_fit();
}

int menu_segment::check_pressed(int x, int y) {
  for (auto o_button : buttons) {
    if (o_button.check_pressed(x, y) > -1) {
      return o_button.check_pressed(x, y);
    }
  }

  return -1;
}

void menu_segment::update_text(int id, std::string text) {
  for (auto o_button : buttons) {
    if (o_button.get_id() == id) {
      o_button.update_text(text);
      break;
    }
  }
}

projects_explorer::projects_explorer() {
  page_up_btn.add_part(
      std::make_shared<triangle>(150, 185, 150 + 23, 185, 161, 165, 0x00FD));
  page_down_btn.add_part(
      std::make_shared<triangle>(150, 432, 150 + 23, 432, 161, 452, 0x00FD));
  if (f_mount(&file_system, "/", 1) == FR_OK) {
    get_files();
    initialized = true;
  } else
    initialized = false;
}

void projects_explorer::update_last_file_to_display() {
  last_file_to_display =
      ((first_file_to_display + project_explorer_num_files_on_page)
          > sd_files.size()) ?
          sd_files.size() :
          (first_file_to_display + project_explorer_num_files_on_page);
}

void projects_explorer::get_files() {
  sd_files.clear();
  if (f_opendir(&directory, "/") == FR_OK) {
    for (;;) {
      if (f_readdir(&directory, &fno) != FR_OK || fno.fname[0] == 0)
        break;
      if (std::string(fno.fname).find(".txt") != std::string::npos) {
        sd_files.push_back(fno);
      }
    }
  }
  first_file_to_display = 0;
  selected_file = -1;
  sort_files();
}

void projects_explorer::sort_files() {
  auto compare = [this](const FILINFO &a, const FILINFO &b) {
    switch (option) {
    case by_name:
      return sort_ascending ? a.fname < b.fname : a.fname > b.fname;
    case by_size:
      return sort_ascending ? a.fsize < b.fsize : a.fsize > b.fsize;
    case by_date:
      return sort_ascending ? a.fdate < b.fdate : a.fdate > b.fdate;
    default:
      return false;
    }
  };
  std::sort(sd_files.begin(), sd_files.end(), compare);
  selected_file = -1;
  draw();
}

void projects_explorer::set_sort_option(enum sort_option in_option,
    bool in_sort_ascending) {
  option = in_option;
  sort_ascending = in_sort_ascending;
  sort_files();
}

std::string projects_explorer::get_choosen_file() {
  if (selected_file >= 0) {
    return sd_files[selected_file].fname;
  } else {
    // TODO tutaj powinien być rzucany wyjątek w przyszłości
    return "";
  }
}

void projects_explorer::draw() {
  update_last_file_to_display();
  if (first_file_to_display > 0) {
    page_up_btn.draw();
  } else {
    TFT_Draw_Fill_Rectangle(142, 158, 40, 40, clear_screen_color);
  }
  if (sd_files.size() > last_file_to_display) {
    page_down_btn.draw();
  } else {
    TFT_Draw_Fill_Rectangle(142, 425, 40, 40, clear_screen_color);
  }
  int i = first_file_to_display;
  int pos_counter = 0;
  for (; i < last_file_to_display; i++) {
    TFT_Draw_Fill_Rectangle(project_explorer_start_pos_x,
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space) -
    project_explorer_line_space / 2 - 1, 460, 2, 0xB5B6);
    if (i == selected_file) {
      TFT_Draw_Fill_Round_Rect(project_explorer_start_pos_x,
          project_explorer_start_pos_y
              + pos_counter * (project_explorer_line_height +
              project_explorer_line_space), 460, project_explorer_line_height,
          10, 0xB6DF);
    } else {
      TFT_Draw_Fill_Rectangle(project_explorer_start_pos_x,
          project_explorer_start_pos_y
              + pos_counter * (project_explorer_line_height +
              project_explorer_line_space), 460, project_explorer_line_height,
          clear_screen_color);
    }
    draw_text(project_explorer_start_pos_x,
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space),
    project_explorer_line_height, project_explorer_file_menu_font, 1,
    BLACK, sd_files[i].fname);
    draw_text(project_explorer_start_pos_x + 153,
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space),
    project_explorer_line_height, project_explorer_file_menu_font, 1,
    BLACK, format_date(sd_files[i].fdate));
    draw_text(project_explorer_start_pos_x + 153 * 2,
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space),
    project_explorer_line_height, project_explorer_file_menu_font, 1,
    BLACK, std::to_string(sd_files[i].fsize));
    pos_counter++;
  }
}

void projects_explorer::forget_selected_hiden_file() {
  if ((selected_file < first_file_to_display
      || selected_file > last_file_to_display) &&
  forget_when_hiden) {
    selected_file = -1;
  }
}

void projects_explorer::handle_pressed(int x, int y) {
  if (first_file_to_display > 0) {
    if (page_up_btn.check_pressed(x, y) == 0) {
      first_file_to_display--;
      forget_selected_hiden_file();
      draw();
    }
  }
  if (sd_files.size() > last_file_to_display) {
    if (page_down_btn.check_pressed(x, y) == 1) {
      first_file_to_display++;
      forget_selected_hiden_file();
      draw();
    }
  }
  int i = first_file_to_display;
  int pos_counter = 0;
  for (; i < last_file_to_display; i++) {
    if (check_area_pressed(x, y, project_explorer_start_pos_x,
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space), 460, project_explorer_line_height)) {
      selected_file = i;
      draw();
      break;
    }
    pos_counter++;
  }
}

void projects_explorer::create_file(std::string name) {
  FIL file;
  const char *filename = name.c_str();
  if (f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
    f_close(&file);
  } else {
    // TODO tutaj powinien być rzucany wyjątek
  }
  get_files();
}

std::string projects_explorer::format_date(WORD fdate) {
  std::stringstream dateStream;
  int day = fdate & 0x1F;
  int month = (fdate >> 5) & 0xF;
  int year = (fdate >> 9) + 1980;
  dateStream << std::setw(2) << std::setfill('0') << day << "-" << std::setw(2)
      << std::setfill('0') << month << "-" << std::setw(4) << std::setfill('0')
      << year;

  return dateStream.str();
}

bool projects_explorer::check_area_pressed(int x, int y, int area_x, int area_y,
    int area_width, int area_height) {
  return (x >= area_x && x <= area_x + area_width && y >= area_y
      && y <= area_y + area_height);
}

void projects_explorer::delete_file() {
  if (selected_file >= -1) {
    if (f_unlink(sd_files[selected_file].fname) == FR_OK) {
      get_files();
    }
  } else {
    // TODO tutaj powinien być rzucany wyjątek w przypadku nieudanego usunięcia
  }
}

void project_editor::insert_command(std::shared_ptr<command> in_cmd) {
  if (selected_command > -1) {
    commands.insert(commands.begin() + selected_command + 1, in_cmd);
  } else {
    commands.push_back(in_cmd);
  }
  draw();
}

void project_editor::remove_command() {
  if (selected_command >= -1) {
    commands.erase(commands.begin() + selected_command);
    selected_command = -1;
    draw();
  } else {
    // TODO tutaj powinien być rzucany wyjątek w przypadku nieudanego usunięcia
  }
}

void project_editor::draw() {
  update_last_command_to_display();
  if (first_command_to_display > 0) {
    page_up_btn.draw();
  } else {
    TFT_Draw_Fill_Rectangle(142, 158, 40, 40, clear_screen_color);
  }
  if (commands.size() > last_command_to_display) {
    page_down_btn.draw();
  } else {
    TFT_Draw_Fill_Rectangle(142, 425, 40, 40, clear_screen_color);
  }
  int i = first_command_to_display;
  int pos_counter = 0;
  for (; i < last_command_to_display; i++) {

    TFT_Draw_Fill_Rectangle(command_explorer_start_pos_x,
    command_explorer_start_pos_y + pos_counter * (command_explorer_line_height +
    command_explorer_line_space) -
    command_explorer_line_space / 2 - 1, 460, 2, 0xB5B6);
    if (i == selected_command) {
      TFT_Draw_Fill_Round_Rect(command_explorer_start_pos_x,
          command_explorer_start_pos_y
              + pos_counter * (command_explorer_line_height +
              command_explorer_line_space), 460, command_explorer_line_height,
          10, 0xB6DF);
    } else {
      TFT_Draw_Fill_Rectangle(command_explorer_start_pos_x,
          command_explorer_start_pos_y
              + pos_counter * (command_explorer_line_height +
              command_explorer_line_space), 460, command_explorer_line_height,
          clear_screen_color);
    }
    auto movement_ptr = std::static_pointer_cast<movement>(commands[i]);
    if (movement_ptr) {
      if (movement_ptr->get_target_position() == robot_home_position) {
        draw_text(command_explorer_start_pos_x,
            command_explorer_start_pos_y
                + pos_counter * (command_explorer_line_height +
                command_explorer_line_space),
            command_explorer_line_height, command_explorer_file_menu_font,
        1, BLACK, "HOME");
      }
    } else {
      draw_text(command_explorer_start_pos_x,
      command_explorer_start_pos_y +
      pos_counter * (command_explorer_line_height +
          command_explorer_line_space),
      command_explorer_line_height, command_explorer_file_menu_font,
      1, BLACK, "P" + std::to_string(i));
    }
    commands[i]->draw(
    project_explorer_start_pos_y + pos_counter * (project_explorer_line_height +
    project_explorer_line_space));
    pos_counter++;
  }
}

bool project_editor::check_area_pressed(int x, int y, int area_x, int area_y,
    int area_width, int area_height) {
  return (x >= area_x && x <= area_x + area_width && y >= area_y
      && y <= area_y + area_height);
}

void project_editor::forget_selected_hiden_command() {
  if ((selected_command < first_command_to_display
      || selected_command > last_command_to_display) &&
  forget_when_hiden) {
    selected_command = -1;
  }
}

void project_editor::update_last_command_to_display() {
  last_command_to_display =
      ((first_command_to_display + command_explorer_num_files_on_page)
          > commands.size()) ?
          commands.size() :
          (first_command_to_display + command_explorer_num_files_on_page);
}

void project_editor::handle_pressed(int x, int y) {
  if (first_command_to_display > 0) {
    if (page_up_btn.check_pressed(x, y) == 0) {
      first_command_to_display--;
      forget_selected_hiden_command();
      draw();
    }
  }
  if (commands.size() > last_command_to_display) {
    if (page_down_btn.check_pressed(x, y) == 1) {
      first_command_to_display++;
      forget_selected_hiden_command();
      draw();
    }
  }
  int i = first_command_to_display;
  int pos_counter = 0;
  for (; i < last_command_to_display; i++) {
    if (check_area_pressed(x, y, project_explorer_start_pos_x,
    command_explorer_start_pos_y + pos_counter * (command_explorer_line_height +
    command_explorer_line_space), 460, command_explorer_line_height)) {
      selected_command = i;
      draw();
      break;
    }
    pos_counter++;
  }
}

std::shared_ptr<command> project_editor::get_command_to_execute() {
  if (selected_command < 0) {
    if (commands.size() != 0) {
      selected_command = first_command_to_display;
      draw();
    }
  }
  return commands[selected_command];
}

void project_editor::save_changes_into_file() {
  input_file.close();
  output_file.open(file_name, std::ios::out | std::ios::trunc);
  for (auto cmd : commands) {
    cmd->save_to_file(output_file);
  }
  output_file.close();
  input_file.open(file_name);

}

bool project_editor::open_file(std::string in_file_name) {
//  input_file.close();
//  file_name = in_file_name;
//  input_file.open(in_file_name);
//
//  if (!input_file.is_open()) {
//    //TODO zwróć wyjątek że plik się nie otwiera
//    return false;
//  }
//
  const TCHAR* tchar_file_name = in_file_name.c_str();


      file_name = in_file_name;

      FRESULT result = f_open(&fil, tchar_file_name, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

      if (result != FR_OK) {
          // TODO: Rzuć wyjątek, że plik nie może zostać otwarty
          return result;
      }


  return get_commands();

}

bool project_editor::get_commands() {
  commands.clear();
  selected_command = -1;
  std::string Gcode_command;

  if (!input_file.is_open()) {
    //TODO zwróć wyjątek że plik się nie otwiera
    return false;
  }


  while (input_file >> Gcode_command) {
    if (Gcode_command == "G1") {
      add_part(std::make_shared<mov_streight>(input_file));
    } else if (Gcode_command == "G2") {
      add_part(std::make_shared<mov_circular>(input_file));
    } else if (Gcode_command == "G4") {
      add_part(std::make_shared<cmd_wait>(input_file));
    } else if (Gcode_command == "M42") {
      add_part(std::make_shared<cmd_set_pin>(input_file));
    } else {
      std::cerr << "Unknown Gcode command: " << Gcode_command << std::endl;
      //TODO zwróć wyjątek
    }
  }

  if (commands.empty()) {
    add_part(std::make_shared<mov_streight>(robot_home_position, movement::e_speed::speed_100, movement::e_movement_type::continous));
    add_part(std::make_shared<mov_streight>(robot_home_position, movement::e_speed::speed_100, movement::e_movement_type::continous));
  }

  draw();
  return true;
}
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
//
//
//
//
