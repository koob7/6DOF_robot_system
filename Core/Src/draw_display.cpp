#include <draw_display.h>

menu_segment main_left_menu;
menu_segment main_right_menu;
menu_segment project_explorer_menu;
menu_segment project_editor_menu;
menu_segment straight_mov_menu;
menu_segment circular_mov_menu;
menu_segment commands_menu;
menu_segment settings_menu;

void init_objects() {
  TFT_Clear_Screen(clear_screen_color);
  TFT_Draw_Fill_Rectangle(100, 0, 20, 20, top_menu_background_color);
  TFT_Draw_Fill_Rectangle(680, 0, 20, 20, top_menu_background_color);
  init_main_left_menu();
  init_main_right_menu();
  init_project_explorer_menu();
  init_project_editor_menu();
  init_straight_mov_menu();
  init_circular_mov_menu();
  init_commands_menu();
  init_settings_menu();
}

void init_main_left_menu() {
  // szary prostokąt z lewej
  main_left_menu.add_background_part(
      std::make_shared<rectangle>(0, 0, 20, 20, left_menu_background_color));
  main_left_menu.add_background_part(
      std::make_shared<rectangle>(0, 460, 20, 20, left_menu_background_color));
  main_left_menu.add_background_part(
      std::make_shared<rectangle>(0, 0, 120, 480, left_menu_background_color,
          20));
  int pos_y = 89;
  std::string names[8] = { "OPEN", "CONT. JOB", "MANUAL", "ENABLE TOOL",
      "RUN JOB", "AXIS CONTROL", "CONT. MOVEMENT", "SETTINGS" };
  // przyciski po lewej
  for (uint8_t i = 0; i < 7; i += 1) {
    main_left_menu.add_part(
        button(i, 16, pos_y, 88, 47, left_menu_button_color, 10, names[i],
        left_menu_text_color,
        left_menu_font));
    pos_y += 56;
  }
}

void init_main_right_menu() {
  // szary prostokąt z prawej
  main_right_menu.add_background_part(
      std::make_shared<rectangle>(780, 0, 20, 20, right_menu_background_color));
  main_right_menu.add_background_part(
      std::make_shared<rectangle>(780, 460, 20, 20,
      right_menu_background_color));
  main_right_menu.add_background_part(
      std::make_shared<rectangle>(680, 0, 120, 480, right_menu_background_color,
          20));
  int pos_y = 9;
  std::string names[6] = { "X", "Y", "Z", "A", "B", "C" };
  // przyciski po prawej
  for (uint8_t i = 0; i < 6; i += 1) {
    main_right_menu.add_part(button(i * 2, 696, pos_y, 48, 47,
    right_menu_button_color, 10, "+", 0x4A69,
    right_menu_font));
    main_right_menu.add_part(button(i * 2 + 1, 738, pos_y, 46, 47,
        right_menu_button_color, 10, "-", 0x4A69,
        right_menu_font));
    main_right_menu.add_part(
    std::make_shared<rectangle>(740, pos_y, 2, 47, 0x0000));
    main_right_menu.add_part(std::make_shared<text_field>(
        696, pos_y, 88, 47, names[i], right_menu_text_color, right_menu_font));
    pos_y += 56;
  }
  // przycisk z rączką
  main_right_menu.add_part(
      button(12, 696, pos_y, 48, 47, right_menu_button_color, 10, "+", 0x4A69,
      right_menu_font));
  main_right_menu.add_part(
      button(13, 738, pos_y, 48, 47, right_menu_button_color, 10, "-", 0x4A69,
      right_menu_font));
  main_right_menu.add_part(
      std::make_shared<rectangle>(740, pos_y, 2, 47, 0x0000));
  main_right_menu.add_part(
      std::make_shared<image>(721, 353, hand_icon_x, hand_icon_y, hand_icon,
          false));

  main_right_menu.add_part(
      button(14, 696, 413, 48, 47, right_menu_button_color, 10, "+", 0x4A69,
      right_menu_font));
  main_right_menu.add_part(
      button(15, 738, 413, 48, 47, right_menu_button_color, 10, "-", 0x4A69,
      right_menu_font));
  main_right_menu.add_part(
      std::make_shared<rectangle>(740, 413, 2, 47, 0x0000));
  main_right_menu.add_part(
      std::make_shared<triangle>(732, 417, 732, 417 + 38, 732 + 24, 417 + 19,
      right_menu_text_color));

}

void init_project_explorer_menu() {
  project_explorer_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  project_explorer_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  project_explorer_menu.add_part(
      button(0, 146, 16, 80, 40, top_menu_button_color, 10, "Create file",
      top_menu_text_color, top_menu_font));
  project_explorer_menu.add_part(button(1, 253, 16, 80, 40,
  top_menu_button_color, 10, "Open File",
  top_menu_text_color, top_menu_font));
  project_explorer_menu.add_part(
      button(2, 360, 16, 80, 40, top_menu_button_color, 10, "Edit File Name",
      top_menu_text_color, top_menu_font));
  project_explorer_menu.add_part(
      button(3, 467, 16, 80, 40, top_menu_button_color, 10, "Delete File",
      top_menu_text_color, top_menu_font));
  project_explorer_menu.add_part(
      button(4, 574, 16, 80, 40, top_menu_button_color, 10, "Sort Files",
  top_menu_text_color, top_menu_font));
  project_explorer_menu.add_part(std::make_shared<text_field>(
  project_explorer_start_pos_x, 92, 20, "File name:", top_menu_text_color,
  top_menu_font));
  project_explorer_menu.add_part(std::make_shared<text_field>(
  project_explorer_start_pos_x + 153, 92, 20, "Date:", top_menu_text_color,
  top_menu_font));
  project_explorer_menu.add_part(std::make_shared<text_field>(
  project_explorer_start_pos_x + 153 * 2, 92, 20, "Size:",
  top_menu_text_color, top_menu_font));
}

void init_project_editor_menu() {
  project_editor_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  project_editor_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  project_editor_menu.add_part(button(0, 146, 16, 80, 40,
  top_menu_button_color, 10, "Close file",
  top_menu_text_color, top_menu_font));
  project_editor_menu.add_part(button(1, 253, 16, 80, 40,
  top_menu_button_color, 10, "Save File",
  top_menu_text_color, top_menu_font));
  project_editor_menu.add_part(button(2, 360, 16, 80, 40,
  top_menu_button_color, 10, "New Point",
  top_menu_text_color, top_menu_font));
  project_editor_menu.add_part(button(3, 467, 16, 80, 40,
  top_menu_button_color, 10, "Edit Point",
  top_menu_text_color, top_menu_font));
  project_editor_menu.add_part(
      button(4, 574, 16, 80, 40, top_menu_button_color, 10, "Delete Point",
      top_menu_text_color, top_menu_font));
}

void init_straight_mov_menu() {
  straight_mov_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  straight_mov_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  button btn = button(0, 143, 40, 80, 26, top_menu_button_color, 10, " 100%",
  top_menu_text_color, top_menu_font, false);
  btn.add_part(
      std::make_shared<triangle>(197, 47, 197 + 16, 47, 197 + 8, 47 + 14,
          0x00FD));
  straight_mov_menu.add_part(btn);
  btn = button(1, 240, 40, 80, 26, top_menu_button_color, 10, " cont",
  top_menu_text_color, top_menu_font, false);
  btn.add_part(
      std::make_shared<triangle>(294, 47, 294 + 16, 47, 294 + 8, 47 + 14,
          0x00FD));
  straight_mov_menu.add_part(btn);
  straight_mov_menu.add_part(
      button(2, 345, 16, 100, 40, top_menu_button_color, 10,
          "Touch up target point", top_menu_text_color, top_menu_font));
  straight_mov_menu.add_part(button(3, 470, 16, 80, 40,
  top_menu_button_color, 10, "Save point",
  top_menu_text_color, top_menu_font));
  straight_mov_menu.add_part(button(4, 575, 16, 80, 40,
  top_menu_button_color, 10, "Cancel",
  top_menu_text_color, top_menu_font));
  straight_mov_menu.add_part(
      std::make_shared<text_field>(143, 10, 20, "Speed:", top_menu_text_color,
      top_menu_font));
  straight_mov_menu.add_part(
      std::make_shared<text_field>(240, 10, 20, "Type:", top_menu_text_color,
      top_menu_font));
}

void init_circular_mov_menu() {
  circular_mov_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  circular_mov_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  button btn = button(0, 136, 40, 60, 26, top_menu_button_color, 10, "100%",
  top_menu_text_color, top_menu_font, false);
  btn.add_part(
      std::make_shared<triangle>(178, 47, 178 + 16, 47, 178 + 8, 47 + 14,
          0x00FD));
  circular_mov_menu.add_part(btn);
  btn = button(1, 211, 40, 60, 26, top_menu_button_color, 10, "cont",
  top_menu_text_color, top_menu_font, false);
  btn.add_part(
      std::make_shared<triangle>(253, 47, 253 + 16, 47, 253 + 8, 47 + 14,
          0x00FD));
  circular_mov_menu.add_part(btn);
  circular_mov_menu.add_part(
      button(2, 286, 16, 100, 40, top_menu_button_color, 20,
          "Touch up help point", top_menu_text_color, top_menu_font));
  circular_mov_menu.add_part(
      button(3, 400, 16, 100, 40, top_menu_button_color, 20,
          "Touch up target point", top_menu_text_color, top_menu_font));
  circular_mov_menu.add_part(button(4, 514, 16, 70, 40,
  top_menu_button_color, 20, "Save point",
  top_menu_text_color, top_menu_font));
  circular_mov_menu.add_part(button(5, 598, 16, 70, 40,
  top_menu_button_color, 20, "Cancel",
  top_menu_text_color, top_menu_font));
  circular_mov_menu.add_part(
      std::make_shared<text_field>(136, 10, 20, "Speed:", top_menu_text_color,
      top_menu_font));
  circular_mov_menu.add_part(
      std::make_shared<text_field>(211, 10, 20, "Type:", top_menu_text_color,
      top_menu_font));

}
void init_commands_menu() {
  commands_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  commands_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  commands_menu.add_part(
      std::make_shared<text_field>(127, 16, 40, "Command:", top_menu_text_color,
      top_menu_font));
  button btn = button(0, 215, 16, 175, 40, top_menu_button_color, 20,
      " wait for: 5s",
      top_menu_text_color, top_menu_font, false);
  btn.add_part(
      std::make_shared<triangle>(355, 27, 355 + 22, 27, 355 + 11, 27 + 20,
          0x00FD));
  commands_menu.add_part(btn);
  commands_menu.add_part(button(1, 422, 16, 100, 40,
  top_menu_button_color, 20, "Save point",
  top_menu_text_color, top_menu_font));
  commands_menu.add_part(button(2, 552, 16, 100, 40,
  top_menu_button_color, 20, "Cancel",
  top_menu_text_color, top_menu_font));
}

void init_settings_menu() {
  settings_menu.add_background_part(
      std::make_shared<rectangle>(120, 72, 560, 408, clear_screen_color));
  settings_menu.add_background_part(
      std::make_shared<rectangle>(120, 0, 560, 72, top_menu_background_color));
  settings_menu.add_part(button(0, 422, 16, 100, 40,
  top_menu_button_color, 20, "BACK",
  top_menu_text_color, top_menu_font));
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
//
//
//

