/*
 * finish_state_machine.cpp
 *
 *  Created on: Aug 26, 2024
 *      Author: kobie
 */

#include "finish_state_machine.h"

finish_state_machine::finish_state_machine() :
    //operation_mode(e_operation_mode::MANUAL)
    project_mode(e_project_mode::BROWSE_PROJECTS), step_mode(
        e_step_mode::CONTINUOUS), control_mode(e_control_mode::MANUAL_MODE), axis_control_mode(
        e_axis_control_mode::INVERSE_CINEMATIC), movement_length(
        e_movement_length::MOVEMENT_INFINITE), a_cancel_create_command(300, 200,
        200, 0xD6BA, "UWAGA",
        "Czy na pewno chcesz anulowac operacje tworzenia punkut?", true), l_choose_sort_file_order(
        300, 100, 200, 0xD6BA, "Sortuj:", { "M, nazwa", "R, nazwa", "M, data",
            "R, data", "M, rozmiar", "R, rozmiar" }, true), a_already_existing_file(
        300, 200, 200, 0xD6BA, "Blad", "Plik o podanej nazwie juz istnieje",
        false), a_conf_deleting_file(300, 200, 200, 0xD6BA, "UWAGA",
        "Czy na pewno chcesz usunąć plik?", true), a_no_choosen_file_to_delete(
        300, 200, 200, 0xD6BA, "Blad", "Brak wybranego pliku do skasowania",
        false), a_confirm_save_changed_file(300, 200, 200, 0xD6BA, "UWAGA",
        "Czy chcesz zapisać zmiany w pliku?", true), l_choose_command_type(250,
        100, 300, 0xD6BA, "Typ polecenia:", { "Ruch prosty", "Ruch kolowy",
            "Pol czekaj", "Pol zmien pin" }, true), a_conf_deleting_command(300,
        200, 200, 0xD6BA, "Uwaga", "Czy na pewno chcesz usunac komende?", true), a_no_choosen_comand_to_delete(
        300, 200, 200, 0xD6BA, "Blad", "Brak wybranego komendy do skasowania",
        false), l_choose_movement_type(250, 100, 300, 0xD6BA, "Typ ruchu:", {
        "ciagly", "krok po kroku" }, true), a_conf_update_target_pos(300, 200,
        200, 0xD6BA, "UWAGA",
        "Czy na pewno chcesz zaktualizowac pozycje doceleowa?", true), a_conf_help_target_pos(
        300, 200, 200, 0xD6BA, "UWAGA",
        "Czy na pewno chcesz zaktualizowac pozycje pomocnicza?", true), a_no_set_target_pos(
        300, 200, 200, 0xD6BA, "UWAGA",
        "Brak przypisanej lokalizacji punktu docelowego"), a_no_set_help_pos(
        300, 200, 200, 0xD6BA, "UWAGA",
        "Brak przypisanej lokalizacji punktu pomocniczego"), a_conf_save_command(
        300, 200, 200, 0xD6BA, "UWAGA",
        "Czy na pewno chcesz zapisac polecenie?", true), l_choose_movement_speed(
        250, 100, 300, 0xD6BA, "Prędkosc:", { "10%", "50%", "100%" }, true), a_no_choosen_file_to_open(
        300, 200, 200, 0xD6BA, "UWAGA", "Brak wybranego pliku do otwarcia"), a_function_avilable_in_future(
        300, 180, 240, 0xD6BA, "Przepraszamy",
        "Funkcja bedzie dostępna w przyszlosci, za utrudnienia przepraszamy", false), l_choose_wait_time(
        250, 100, 300, 0xD6BA, "Czekaj:", { "1 sekunde", "5 sekund",
            "30 sekund", "1 minute", "5 minut" }, true), l_choose_output_pin(
        250, 100, 300, 0xD6BA, "Pin wyjsciowy:", { "narzedzie robota",
            "dioda urzytkownika" }, true), l_choose_pin_level(250, 100, 300,
        0xD6BA, "Stan pinu:", { "niski", "wysoki" }, true), a_finish_running_program(300, 200, 200, 0xD6BA, "sukces",
            "program zakonczony pomyslnie", false),a_error_running_program(300, 200, 200, 0xD6BA, "blad",
                "nie mozna wykonac polecenia", false)

{
  target_position = robot_position(0, 0, 0, 0, 0, 0);
  target_point_initialized = false;
  help_position = robot_position(0, 0, 0, 0, 0, 0);
  help_point_initialized = false;
  o_mov_streight = mov_streight(target_position, movement::e_speed::speed_100,
      movement::e_movement_type::continous);
  o_mov_circular = mov_circular(help_position, target_position,
      movement::e_speed::speed_100, movement::e_movement_type::continous);
  o_cmd_wait = cmd_wait(cmd_wait::e_wait_time::wait_5s);
  o_cmd_set_pin = cmd_set_pin(cmd_set_pin::e_output_pin::robot_tool, true);
  project_explorer_menu.draw();
  main_project_explorer.draw();

}

int finish_state_machine::handle_press_with_current_state(int x, int y) {

  if (handle_run_project_menu(x, y)) {
    was_touched = 2;
  }

  if (handle_movement_menu(x, y)) {
    was_touched = 2;
  }

  switch (control_mode) {
  case e_control_mode::AUTOMATIC_MODE:
    // TODO Handle automatic control mode specific logic (wywoływanie metody perform_action
    break;
  case e_control_mode::MANUAL_MODE:
    // Handle manual control mode specific logic
    break;
  }

//  switch (operation_mode) {
//  case e_operation_mode::MANUAL:
//    // Handle manual mode specific logic
//    break;
//  case e_operation_mode::AUTOMATIC:
//    // Handle automatic mode specific logic
//    break;
//  }

  switch (step_mode) {
  case e_step_mode::STEP_BY_STEP:
    // Handle step by step mode specific logic
    break;
  case e_step_mode::CONTINUOUS:
    // Handle continuous mode specific logic
    break;
  }

  switch (project_mode) {
  case e_project_mode::SETTINGS:
    // Handle settings mode specific logic
    switch (settings_menu.check_pressed(x, y)) {
    case 0:
      change_mode(previous_project_mode);
      break;
    }

    break;
  case e_project_mode::BROWSE_PROJECTS:
    // Handle browse projects mode specific logic
    main_project_explorer.handle_pressed(x, y);
    switch (project_explorer_menu.check_pressed(x, y)) {
    case 0: {
      create_new_file();
      break;
    }
    case 1:
      go_to_choosen_file();
      break;

    case 2:
      a_function_avilable_in_future.draw();
      a_function_avilable_in_future.check_pressed();
      //TODO edycjia nazwy pliku
      break;

    case 3:
      delete_choosen_file();
      break;

    case 4:
      choose_file_sorting_option();
      break;

    }
    break;
  case e_project_mode::EDIT_PROJECTS:
    // Handle edit projects mode specific logic
    main_project_editor.handle_pressed(x, y);
    switch (project_editor_menu.check_pressed(x, y)) {
    case 0:
      save_changed_file_and_close();
      break;
    case 1:
      save_changed_file();
      break;
    case 2:
      choose_and_prepare_to_create_command();
      break;
    case 3:
      prepare_to_edit_choosen_command();
      break;
    case 4:
      delete_choosen_command();
      break;
    }
    break;
  case e_project_mode::STREIGHT_MOVE: {
    switch (straight_mov_menu.check_pressed(x, y)) {
    case 0:
      update_movement_speed(o_mov_streight, straight_mov_menu);
      break;
    case 1:
      update_movement_type(o_mov_streight, straight_mov_menu);
      break;
    case 2:
      update_position(o_mov_streight, target_point_initialized,
          &movement::update_target_pos);
      break;
    case 3: {
      if (!target_point_initialized) {
        a_no_set_target_pos.draw();
        a_no_set_target_pos.check_pressed();
      } else {
        save_changed_command(o_mov_streight);
      }

      break;
    }
    case 4:
      cancel_creating_command();
      break;
    }
    break;
  }
  case e_project_mode::CIRCULAR_MOVE: {
    switch (circular_mov_menu.check_pressed(x, y)) {
    case 0:
      update_movement_speed(o_mov_circular, circular_mov_menu);
      break;
    case 1:
      update_movement_type(o_mov_circular, circular_mov_menu);
      break;
    case 2:
      update_position(o_mov_circular, target_point_initialized,
          &movement::update_target_pos);
      break;
    case 3:
      update_position(o_mov_circular, help_point_initialized,
          &mov_circular::update_help_pos);
      break;
    case 4: {
      if (!target_point_initialized) {
        a_no_set_target_pos.draw();
        a_no_set_target_pos.check_pressed();
      } else if (!help_point_initialized) {
        a_no_set_help_pos.draw();
        a_no_set_help_pos.check_pressed();
      } else {
        save_changed_command(o_mov_circular);
      }
      break;
    }
    case 5:
      cancel_creating_command();
      break;
    }

    break;
  }
  case e_project_mode::WAIT_COMAND: {
    switch (wait_command_menu.check_pressed(x, y)) {
    case 0:
      update_wait_speed();
      break;
    case 1:
      save_changed_command(o_cmd_wait);
      break;
    case 2:
      cancel_creating_command();
      break;
    }
    break;
  }
  case e_project_mode::SET_PIN_COMAND: {
    switch (set_pin_command_menu.check_pressed(x, y)) {
    case 0:
      update_output_pin();
      break;
    case 1:
      update_pin_level();
      break;
    case 2:
      save_changed_command(o_cmd_set_pin);
      break;
    case 3:
      cancel_creating_command();
      break;
    }

    break;
  }
  }
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

//TODO usunąć te komentarze

//void finish_state_machine::change_mode(e_operation_mode new_state) {
//  if (operation_mode != new_state) {
//    switch (new_state) {
//    case e_operation_mode::MANUAL:
//      operation_mode = e_operation_mode::MANUAL;
//      break;
//    case e_operation_mode::AUTOMATIC:
//      operation_mode = e_operation_mode::AUTOMATIC;
//      break;
//    }
//
//  }
//}

void finish_state_machine::change_mode(e_project_mode new_state) {
  if (project_mode != new_state) {
    previous_project_mode = project_mode;
    project_mode = new_state;
    switch (new_state) {
    case e_project_mode::SETTINGS:
      settings_menu.draw();
      break;
    case e_project_mode::BROWSE_PROJECTS:
      project_explorer_menu.draw();
      main_project_explorer.draw();
      break;
    case e_project_mode::EDIT_PROJECTS:
      project_editor_menu.draw();
      main_project_editor.draw();
      break;
    case e_project_mode::STREIGHT_MOVE:
      straight_mov_menu.update_text(0, o_mov_streight.get_speed_text() + "%");
      straight_mov_menu.update_text(1, o_mov_streight.get_movement_type_text());
      straight_mov_menu.draw();
      break;
    case e_project_mode::CIRCULAR_MOVE:
      circular_mov_menu.update_text(0, o_mov_circular.get_speed_text() + "%");
      circular_mov_menu.update_text(1, o_mov_circular.get_movement_type_text());
      circular_mov_menu.draw();
      break;
    case e_project_mode::WAIT_COMAND:
      wait_command_menu.update_text(0, o_cmd_wait.get_time_text());
      wait_command_menu.draw();
      break;
    case e_project_mode::SET_PIN_COMAND:
      set_pin_command_menu.update_text(0, o_cmd_set_pin.get_pin_output_text());
      set_pin_command_menu.update_text(1, o_cmd_set_pin.get_pin_level_text());
      set_pin_command_menu.draw();
      break;
    }

  }
}

void finish_state_machine::change_mode(e_step_mode new_state) {
  if (step_mode != new_state) {
    step_mode = new_state;
    switch (new_state) {
    case e_step_mode::STEP_BY_STEP:
      break;
    case e_step_mode::CONTINUOUS:
      break;
    }
  }
}

void finish_state_machine::change_mode(e_control_mode new_state) {
  if (control_mode != new_state) {
    control_mode = new_state;
    switch (new_state) {
    case e_control_mode::AUTOMATIC_MODE:
      break;
    case e_control_mode::MANUAL_MODE:
      break;
    }
  }
}

void finish_state_machine::change_mode(
    e_axis_control_mode new_axis_control_mode) {
  if (axis_control_mode != new_axis_control_mode) {
    axis_control_mode = new_axis_control_mode;
    switch (new_axis_control_mode) {
    case e_axis_control_mode::AXIS_CONTROL:
      break;
    case e_axis_control_mode::INVERSE_CINEMATIC:
      break;
    }
  }
}

void finish_state_machine::change_mode(e_movement_length new_movement_length) {
  if (movement_length != new_movement_length) {
    movement_length = new_movement_length;
    switch (new_movement_length) {
    case e_movement_length::MOVEMENT_INFINITE:
      break;
    case e_movement_length::MOVEMENT_1MM:
      break;
    case e_movement_length::MOVEMENT_1CM:
      break;
    case e_movement_length::MOVEMENT_5CM:
      break;
    }
  }
}

void finish_state_machine::cancel_creating_command() {

  a_cancel_create_command.draw();
  if (a_cancel_create_command.check_pressed() == 0) {
    change_mode(e_project_mode::EDIT_PROJECTS);
  }
}

void finish_state_machine::choose_file_sorting_option() {
  l_choose_sort_file_order.draw();
  switch (l_choose_sort_file_order.check_pressed()) {
  case 0:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_name, true);
    break;
  case 1:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_name, false);
    break;
  case 2:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_date, true);
    break;
  case 3:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_date, false);
    break;
  case 4:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_size, true);
    break;
  case 5:
    main_project_explorer.set_sort_option(
        projects_explorer::sort_option::by_size, false);
    break;
  case -1:
    //TODO nie wybrano sortowania
    break;
  }
}
void finish_state_machine::create_new_file() {
  if (main_project_explorer.create_file(
      std::to_string(main_project_explorer.sd_files.size()) + ".txt") == -1) {

    a_already_existing_file.draw();
    a_already_existing_file.check_pressed();
  } else {
    main_project_explorer.get_files();
  }
}

void finish_state_machine::delete_choosen_file() {
  if (main_project_explorer.check_if_is_choosen()) {

    a_conf_deleting_file.draw();
    if (a_conf_deleting_file.check_pressed() == 0) {
      main_project_explorer.delete_file();
      cleer_working_screen.draw();
      main_project_explorer.draw();
    }
  } else {

    a_no_choosen_file_to_delete.draw();
    a_no_choosen_file_to_delete.check_pressed();
  }
}

void finish_state_machine::go_to_choosen_file() {

  if (main_project_explorer.get_choosen_file() == "") {
    a_no_choosen_file_to_open.draw();
    a_no_choosen_file_to_open.check_pressed();
  } else {
    main_project_editor.open_file(main_project_explorer.get_choosen_file());
    main_project_editor.prepare_commands();
    change_mode(e_project_mode::EDIT_PROJECTS);
  }
}

void finish_state_machine::save_changed_file() {
  a_confirm_save_changed_file.draw();
  if (a_confirm_save_changed_file.check_pressed() == 0) {
    main_project_editor.save_changes_into_file();
  }

}

void finish_state_machine::save_changed_file_and_close() {
  save_changed_file();
  main_project_editor.close_file();
  change_mode(e_project_mode::BROWSE_PROJECTS);
  main_project_explorer.get_files();
}

void finish_state_machine::choose_and_prepare_to_create_command() {
  l_choose_command_type.draw();
  switch (l_choose_command_type.check_pressed()) {
  case 0: {
    target_point_initialized = false;
    target_position = robot_position(0, 0, 0, 0, 0, 0);
    o_mov_streight = mov_streight(target_position, movement::e_speed::speed_100,
        movement::e_movement_type::continous);
    edit_command = false;
    change_mode(e_project_mode::STREIGHT_MOVE);
    break;
  }
  case 1: {
    target_point_initialized = false;
    target_position = robot_position(0, 0, 0, 0, 0, 0);
    help_point_initialized = false;
    help_position = robot_position(0, 0, 0, 0, 0, 0);
    o_mov_circular = mov_circular(help_position, target_position,
        movement::e_speed::speed_100, movement::e_movement_type::continous);
    edit_command = false;
    change_mode(e_project_mode::CIRCULAR_MOVE);
    break;
  }
  case 2: {
    o_cmd_wait = cmd_wait(cmd_wait::e_wait_time::wait_5s);
    edit_command = false;
    change_mode(e_project_mode::WAIT_COMAND);
    break;
  }
  case 3: {
    o_cmd_set_pin = cmd_set_pin(cmd_set_pin::e_output_pin::robot_tool, true);
    edit_command = false;
    change_mode(e_project_mode::SET_PIN_COMAND);
    break;
  }
  }
}

void finish_state_machine::prepare_to_edit_choosen_command() {
  std::shared_ptr<command> chosen_command =
      main_project_editor.get_choosen_command();

  if (auto p_mov_streight = std::static_pointer_cast<mov_streight>(
      chosen_command)) {
    o_mov_streight = *p_mov_streight;
    target_point_initialized = true;
    edit_command = true;
    change_mode(e_project_mode::STREIGHT_MOVE);
  } else if (auto p_mov_circular = std::static_pointer_cast<mov_circular>(
      chosen_command)) {
    o_mov_circular = *p_mov_circular;
    target_point_initialized = true;
    help_point_initialized = true;
    edit_command = true;
    change_mode(e_project_mode::CIRCULAR_MOVE);
  } else if (auto p_cmd_wait = std::static_pointer_cast<cmd_wait>(
      chosen_command)) {
    o_cmd_wait = *p_cmd_wait;
    edit_command = true;
    change_mode(e_project_mode::WAIT_COMAND);
  } else if (auto p_cmd_set_pin = std::static_pointer_cast<cmd_set_pin>(
      chosen_command)) {
    o_cmd_set_pin = *p_cmd_set_pin;
    edit_command = true;
    change_mode(e_project_mode::SET_PIN_COMAND);
  }
}

void finish_state_machine::delete_choosen_command() {
  if (main_project_editor.check_if_is_choosen()) {

    a_conf_deleting_command.draw();
    if (a_conf_deleting_command.check_pressed() == 0) {
      main_project_editor.remove_command();
    }
  } else {

    a_no_choosen_comand_to_delete.draw();
    a_no_choosen_comand_to_delete.check_pressed();
  }
}

template<typename t_command, typename t_update_value,
    typename t_update_value_fun, typename t_get_text_fun>
void finish_state_machine::update_command_value_helper(t_command &command,
    t_update_value update_value, menu_segment &menu, int menu_button,
    void (t_update_value_fun::*update_value_fun)(t_update_value),
    std::string (t_get_text_fun::*get_text_fun)(), std::string aditional_text) {
  (command.*update_value_fun)(update_value);
  menu.update_text(menu_button, (command.*get_text_fun)() + aditional_text);
  menu.draw();
}

template<typename CommandType>
void finish_state_machine::update_movement_type(CommandType &command,
    menu_segment &menu) {
  movement::e_movement_type tmp;
  l_choose_movement_type.draw();
  switch (l_choose_movement_type.check_pressed()) {
  case 0:
    tmp = movement::e_movement_type::continous;
    break;
  case 1:
    tmp = movement::e_movement_type::step_by_step;
    break;
  case -1:
    return;
  }
  update_command_value_helper(command, tmp, menu, 1,
      &movement::update_movement_type, &movement::get_movement_type_text);
}

template<typename CommandType>
void finish_state_machine::update_movement_speed(CommandType &command,
    menu_segment &menu) {
  movement::e_speed tmp_speed;
  l_choose_movement_speed.draw();
  switch (l_choose_movement_speed.check_pressed()) {
  case 0:
    tmp_speed = movement::e_speed::speed_10;
    break;
  case 1:
    tmp_speed = movement::e_speed::speed_50;
    break;
  case 2:
    tmp_speed = movement::e_speed::speed_100;
    break;
  case -1:
    return;
  }
  update_command_value_helper(command, tmp_speed, menu, 0,
      &movement::update_speed, &movement::get_speed_text, "%");
}

template<typename CommandType>
void finish_state_machine::save_changed_command(CommandType &command) {
  a_conf_save_command.draw();
  if (a_conf_save_command.check_pressed() == 0) {
    if (edit_command) {
      std::static_pointer_cast<CommandType>(
          main_project_editor.get_choosen_command())->update_command(command);
      main_project_editor.prepare_commands();
      change_mode(e_project_mode::EDIT_PROJECTS);
    } else {
      main_project_editor.insert_command(
          std::make_shared<CommandType>(command));
      //tutaj przygotowanie komend jest wywoływane w środku komendy insrt
      change_mode(e_project_mode::EDIT_PROJECTS);
    }

  }
}

template<typename CommandType, typename comandType2>
void finish_state_machine::update_position(CommandType &command,
    bool &initialized,
    void (comandType2::*update_function)(struct robot_position)) {
  a_conf_update_target_pos.draw();
  if (a_conf_update_target_pos.check_pressed() == 0) {
    (command.*update_function)(get_current_position());
    initialized = true;
  }
}

void finish_state_machine::update_wait_speed() {
  cmd_wait::e_wait_time tmp_time;
  l_choose_wait_time.draw();
  switch (l_choose_wait_time.check_pressed()) {
  case 0:
    tmp_time = cmd_wait::e_wait_time::wait_1s;
    break;
  case 1:
    tmp_time = cmd_wait::e_wait_time::wait_5s;
    break;
  case 2:
    tmp_time = cmd_wait::e_wait_time::wait_30s;
    break;
  case 3:
    tmp_time = cmd_wait::e_wait_time::wait_1min;
    break;
  case 4:
    tmp_time = cmd_wait::e_wait_time::wait_5min;
    break;
  case -1:
    return;
  }
  update_command_value_helper(o_cmd_wait, tmp_time, wait_command_menu, 0,
      &cmd_wait::update_time, &cmd_wait::get_time_text);

}

void finish_state_machine::update_output_pin() {
  cmd_set_pin::e_output_pin tmp_pin;
  l_choose_output_pin.draw();
  switch (l_choose_output_pin.check_pressed()) {
  case 0:
    tmp_pin = cmd_set_pin::e_output_pin::robot_tool;
    break;
  case 1:
    tmp_pin = cmd_set_pin::e_output_pin::user_led;
    break;
  case -1:
    return;
  }
  update_command_value_helper(o_cmd_set_pin, tmp_pin, set_pin_command_menu, 0,
      &cmd_set_pin::update_pin, &cmd_set_pin::get_pin_output_text);
}

void finish_state_machine::update_pin_level() {
  bool tmp_level;
  l_choose_pin_level.draw();
  switch (l_choose_pin_level.check_pressed()) {
  case 0:
    tmp_level = false;
    break;
  case 1:
    tmp_level = true;
    break;
  case -1:
    return;
  }
  update_command_value_helper(o_cmd_set_pin, tmp_level, set_pin_command_menu, 1,
      &cmd_set_pin::update_pin_level, &cmd_set_pin::get_pin_level_text);
}

bool finish_state_machine::handle_movement_menu(int x, int y) {
  if (control_mode == e_control_mode::MANUAL_MODE) {
    int pressed_button = main_right_menu.check_pressed(x, y);
    if (pressed_button < 0) {
      return false;
    }
    if (pressed_button > -1 && pressed_button < 12) {
      robot_was_moved = true;
      while (!manual_movement_ready) {
        //TODO czekamy aż będziemy mogli wyslać kolejną komendę
      }
    }

    if (axis_control_mode == e_axis_control_mode::INVERSE_CINEMATIC) {
      switch (pressed_button) {
      case 0:
        givenPosition[0] += manual_speed_movement_factor;
        break;
      case 1:
        givenPosition[0] -= manual_speed_movement_factor;
        break;
      case 2:
        givenPosition[1] += manual_speed_movement_factor;
        break;
      case 3:
        givenPosition[1] -= manual_speed_movement_factor;
        break;
      case 4:
        givenPosition[2] += manual_speed_movement_factor;
        break;
      case 5:
        givenPosition[2] -= manual_speed_movement_factor;
        break;
      case 6:
        givenPosition[3] += manual_speed_movement_factor;
        break;
      case 7:
        givenPosition[3] -= manual_speed_movement_factor;
        break;
      case 8:
        givenPosition[4] += manual_speed_movement_factor;
        break;
      case 9:
        givenPosition[4] -= manual_speed_movement_factor;
        break;
      case 10:
        givenPosition[5] += manual_speed_movement_factor;
        break;
      case 11:
        givenPosition[5] -= manual_speed_movement_factor;
        break;
      }
    } else {
      if (pressed_button > -1 && pressed_button < 12) {
        a_function_avilable_in_future.draw();
        a_function_avilable_in_future.check_pressed();
      }
    }
    switch (pressed_button) {
    case 12:
      adjust_movement_speed(manual_movement_speed, manual_speed_movement_factor,
          12, true);
      break;
    case 13:
      adjust_movement_speed(manual_movement_speed, manual_speed_movement_factor,
          12, false);
      break;
    case 14:
      adjust_movement_speed(automatic_movement_speed,
          automatic_speed_movement_factor, 15, true);
      break;
    case 15:
      adjust_movement_speed(automatic_movement_speed,
          automatic_speed_movement_factor, 15, false);
      break;
    }
    licz_kroki(givenPosition, givenSteps, currentPosition);
    return true;

  }
  return false;
}

std::string finish_state_machine::get_movement_speed_text(
    const e_movement_speed movement_speed) {
  switch (movement_speed) {
  case speed_10:
    return "10%";
  case speed_50:
    return "50%";
  case speed_100:
    return "100%";
  }
}

void finish_state_machine::update_movement_speed_factor(
    e_movement_speed &movement_speed, volatile double &speed_movement_factor,
    int button_index) {
  switch (movement_speed) {
  //tutaj będziemy zmieniali prescaller żeby regulować częstotliowść wywoływania komend
  case speed_10:
    speed_movement_factor = 0.001;
    break;
  case speed_50:
    speed_movement_factor = 0.005;
    break;
  case speed_100:
    speed_movement_factor = 0.01;
    break;
  }
  main_right_menu.update_text(button_index,
      get_movement_speed_text(movement_speed),
      menu_segment::e_menu_layer::e_top_parts);
}

void finish_state_machine::adjust_movement_speed(
    e_movement_speed &movement_speed, volatile double &speed_movement_factor,
    int button_index, bool increase) {
  if (increase && movement_speed < num_of_speed_levels - 1) {
    movement_speed = static_cast<e_movement_speed>(movement_speed + 1);
  } else if (!increase && movement_speed > 0) {
    movement_speed = static_cast<e_movement_speed>(movement_speed - 1);
  }
  update_movement_speed_factor(movement_speed, speed_movement_factor,
      button_index);
}

bool finish_state_machine::handle_run_project_menu(int x, int y) {
  int pressed_button = main_left_menu.check_pressed(x, y);
  if (pressed_button < 0) {
    return false;
  }
  switch (pressed_button) {
  case 0:
    toggle_step_mode();
    break;
  case 1:
    toggle_control_mode();
    break;
  case 2:
    toggle_enable_tool();
    break;
  case 3:
    return handle_run_project();
    break;
  case 4:
    toggle_axis_control_mode();
    break;
  case 5:
    toggle_movement_length();
    break;
  case 6:
    //zakomentowałem bo dotyk często tutaj odczytuje pozycje i jest to problematyczne
    //a_function_avilable_in_future.draw();
    //a_function_avilable_in_future.check_pressed();
    break;

  }

  return false;
}

void finish_state_machine::toggle_enable_tool() {
  enable_tool = !enable_tool;
  main_left_menu.update_text(2, get_enable_tool_text());
}

std::string finish_state_machine::get_control_mode_text() {
  switch (control_mode) {
  case e_control_mode::MANUAL_MODE:
    return "MANUAL";
  case e_control_mode::AUTOMATIC_MODE:
    return "AUTO";
  }
}

void finish_state_machine::toggle_control_mode() {
  switch (control_mode) {
  case e_control_mode::MANUAL_MODE:
    control_mode = e_control_mode::AUTOMATIC_MODE;
    break;
  case e_control_mode::AUTOMATIC_MODE:
    control_mode = e_control_mode::MANUAL_MODE;
    break;
  }
  main_left_menu.update_text(1, get_control_mode_text());
}

std::string finish_state_machine::get_step_mode_text() {
  switch (step_mode) {
  case e_step_mode::STEP_BY_STEP:
    return "STEP MOVEMENT";
  case e_step_mode::CONTINUOUS:
    return "CONT. MOVEMENT";
  }
}

void finish_state_machine::toggle_step_mode() {
  switch (step_mode) {
  case e_step_mode::STEP_BY_STEP:
    step_mode = e_step_mode::CONTINUOUS;
    break;
  case e_step_mode::CONTINUOUS:
    step_mode = e_step_mode::STEP_BY_STEP;
    break;
  }
  main_left_menu.update_text(0, get_step_mode_text());
}

std::string finish_state_machine::get_axis_control_mode_text() {
  switch (axis_control_mode) {
  case e_axis_control_mode::AXIS_CONTROL:
    return "AXIS CONTORL";
  case e_axis_control_mode::INVERSE_CINEMATIC:
    return "INVERS CINEMATIC";
  }
}

void finish_state_machine::toggle_axis_control_mode() {
  switch (axis_control_mode) {
  case e_axis_control_mode::AXIS_CONTROL:
    axis_control_mode = e_axis_control_mode::INVERSE_CINEMATIC;
    break;
  case e_axis_control_mode::INVERSE_CINEMATIC:
    axis_control_mode = e_axis_control_mode::AXIS_CONTROL;
    break;
  }
  main_left_menu.update_text(4, get_axis_control_mode_text());
}

std::string finish_state_machine::get_movement_length_text() {
  switch (movement_length) {
  case e_movement_length::MOVEMENT_INFINITE:
    return "INF MOVEMENT";
  case e_movement_length::MOVEMENT_1MM:
    return "1MM MOVEMENT";
  case e_movement_length::MOVEMENT_1CM:
    return "1CM MOVEMENT";
  case e_movement_length::MOVEMENT_5CM:
    return "5CM MOVEMENT";
  }
}

void finish_state_machine::toggle_movement_length() {
  switch (movement_length) {
  case e_movement_length::MOVEMENT_INFINITE:
    movement_length = e_movement_length::MOVEMENT_1MM;
    break;
  case e_movement_length::MOVEMENT_1MM:
    movement_length = e_movement_length::MOVEMENT_1CM;
    break;
  case e_movement_length::MOVEMENT_1CM:
    movement_length = e_movement_length::MOVEMENT_5CM;
    break;
  case e_movement_length::MOVEMENT_5CM:
    movement_length = e_movement_length::MOVEMENT_INFINITE;
    break;
  }
  main_left_menu.update_text(5, get_movement_length_text());
}

bool finish_state_machine::handle_run_project() {
  if (control_mode == e_control_mode::MANUAL_MODE) {
    a_function_avilable_in_future.draw();
    a_function_avilable_in_future.check_pressed();
    //TODO tutaj będzie zwracane true tak dlugo jak będzie kolejna komenda do obluzenia
    return true;
  } else {

    enum project_editor::e_project_run_progres status = main_project_editor.execute_project();
      while (1) {
        if(status ==project_editor::e_project_run_progres::pending){
          status = main_project_editor.execute_project();
        }
        else if(status == project_editor::e_project_run_progres::end){
          a_finish_running_program.draw();
          a_finish_running_program.check_pressed();
                break;
        }
        else if(status == project_editor::e_project_run_progres::fault){
                a_error_running_program.draw();
                a_error_running_program.check_pressed();
                break;
          }

      }


    //TODO tutaj będzie zwrócone false po całkowitym wykonaniu programu
    return false;
  }
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

