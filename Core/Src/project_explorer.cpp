#include "project_explorer.h"

projects_explorer::projects_explorer() {
  page_up_btn.add_part(
      std::make_shared<triangle>(147, 132, 147 + 24, 132, 147 + 12, 132 - 20,
          0x00FD));
  page_down_btn.add_part(
      std::make_shared<triangle>(147, 417, 147 + 24, 417, 147 + 12, 417 + 20,
          0x00FD));

  get_files();
  initialized = true;
}

void projects_explorer::update_last_file_to_display() {
  last_file_to_display =
      ((first_file_to_display + project_explorer_num_files_on_page)
          > static_cast<int>(sd_files.size())) ?
          sd_files.size() :
          (first_file_to_display + project_explorer_num_files_on_page);
}

void projects_explorer::get_files() {
  sd_files.clear();
  if (f_opendir(&directory, "/") == FR_OK) {
    for (;;) {
      if (f_readdir(&directory, &fno) != FR_OK || fno.fname[0] == 0)
        break;
      if (std::string(fno.fname).find(".gcode") != std::string::npos) {
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
    TFT_Draw_Fill_Rectangle(139, 106, 41, 40, clear_screen_color);
  }
  if (static_cast<int>(sd_files.size()) > last_file_to_display) {
    page_down_btn.draw();
  } else {
    TFT_Draw_Fill_Rectangle(139, 405, 41, 40, clear_screen_color);
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
      || selected_file > last_file_to_display)) {
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
  if (static_cast<int>(sd_files.size()) > last_file_to_display) {
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

int projects_explorer::create_file(std::string name) {
  FIL file;
  const char *filename = name.c_str();
  FILINFO fno;
  if (f_stat(filename, &fno) == FR_OK) {
    return -1;
  }
  if (f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
    f_close(&file);
    return 0;
  } else {
    return -2;
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

bool projects_explorer::delete_file() {
  if (selected_file >= -1) {
    if (f_unlink(sd_files[selected_file].fname) == FR_OK) {
      get_files();
      return true;
    }
    return false;
  } else {
    return false;
    // TODO tutaj powinien być rzucany wyjątek w przypadku nieudanego usunięcia
  }
}
