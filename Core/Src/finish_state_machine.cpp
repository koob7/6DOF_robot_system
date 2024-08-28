/*
 * finish_state_machine.cpp
 *
 *  Created on: Aug 26, 2024
 *      Author: kobie
 */

#include "finish_state_machine.h"

finish_state_machine::finish_state_machine() :
    operation_mode(e_operation_mode::AUTOMATIC), project_mode(
        e_project_mode::BROWSE_PROJECTS), step_mode(e_step_mode::CONTINUOUS), control_mode(
        e_control_mode::MANUAL_MODE) {
  project_explorer_menu.draw();
  main_project_explorer.draw();
}

void finish_state_machine::change_mode(e_operation_mode new_state) {
  if (operation_mode != new_state) {
    switch (new_state) {
    case e_operation_mode::MANUAL:
      operation_mode = e_operation_mode::MANUAL;
      break;
    case e_operation_mode::AUTOMATIC:
      operation_mode = e_operation_mode::AUTOMATIC;
      break;
    }

  }
}

void finish_state_machine::change_mode(e_project_mode new_state) {
  if (project_mode != new_state) {
    previous_project_mode = project_mode;
    switch (new_state) {
    case e_project_mode::SETTINGS:
      project_mode = e_project_mode::SETTINGS;
      settings_menu.draw();
      break;
    case e_project_mode::BROWSE_PROJECTS:
      project_mode = e_project_mode::BROWSE_PROJECTS;
      project_explorer_menu.draw();
      main_project_explorer.draw();
      break;
    case e_project_mode::EDIT_PROJECTS:
      project_mode = e_project_mode::EDIT_PROJECTS;
      project_editor_menu.draw();
      main_project_editor.draw();
      break;
    }
  }
}

void finish_state_machine::change_mode(e_step_mode new_state) {
  if (step_mode != new_state) {
    switch (new_state) {
    case e_step_mode::STEP_BY_STEP:
      step_mode = e_step_mode::STEP_BY_STEP;
      break;
    case e_step_mode::CONTINUOUS:
      step_mode = e_step_mode::CONTINUOUS;
      break;
    }
  }
}

void finish_state_machine::change_mode(e_control_mode new_state) {
  if (control_mode != new_state) {
    switch (new_state) {
    case e_control_mode::AUTOMATIC_MODE:
      control_mode = e_control_mode::AUTOMATIC_MODE;
      break;
    case e_control_mode::MANUAL_MODE:
      control_mode = e_control_mode::MANUAL_MODE;
      break;
    }
  }
}

int finish_state_machine::handle_press_with_current_state(int x, int y) {

//  int pressed_button = main_right_menu.check_pressed(x, y);
//
//  switch (pressed_button){
//  case 0:
//    givenPosition[0]+=0.01;
//    break;
//  case 1:
//    givenPosition[0]-=0.01;
//    break;
//  case 2:
//    givenPosition[1]+=0.01;
//    break;
//  case 3:
//    givenPosition[1]-=0.01;
//    break;
//  case 4:
//    break;
//  case 5:
//    break;
//  }
//  licz_kroki(givenPosition, givenSteps, currentPosition);
//  if (pressed_button>=0){ return 1;}
//  else{return 0;}

  switch (control_mode) {
  case e_control_mode::AUTOMATIC_MODE:
    // TODO Handle automatic control mode specific logic (wywoływanie metody perform_action
    break;
  case e_control_mode::MANUAL_MODE:
    // Handle manual control mode specific logic
    break;
  }

  switch (operation_mode) {
  case e_operation_mode::MANUAL:
    // Handle manual mode specific logic
    break;
  case e_operation_mode::AUTOMATIC:
    // Handle automatic mode specific logic
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
      if(main_project_explorer.create_file(
          std::to_string(main_project_explorer.sd_files.size()) + ".txt")==-1){
        allert failure_allert(300, 200, 200, 0xD6BA, "Blad",
                      "Plik o podanej nazwie juz istnieje", false);
                  failure_allert.draw();
                  failure_allert.check_pressed();
      }
      else{
        main_project_explorer.get_files();
      }
      break;
    }
    case 1: {
      change_mode(e_project_mode::EDIT_PROJECTS);
      main_project_editor.open_file(main_project_explorer.get_choosen_file());
      break;
    }
    case 2: {
      //TODO edycjia nazwy pliku
      break;
    }
    case 3: {
      allert o_allert(300, 200, 200, 0xD6BA, "UWAGA",
          "Czy na pewno chcesz usunąć plik?", true);
      o_allert.draw();
      int check_result = o_allert.check_pressed();
      if (check_result == 0) {
        if (!main_project_explorer.delete_file()) {
          allert failure_allert(300, 200, 200, 0xD6BA, "Blad",
              "Brak wybranego pliku do skasowania", false);
          failure_allert.draw();
          failure_allert.check_pressed();
        }
      } else if (check_result == 1) {

      }
      break;
    }
    case 4: {
      list_dialog sort_dialog(300, 100, 200, 0xD6BA, "Sortuj:", { "M, nazwa",
          "R, nazwa", "M, data", "R, data", "M, rozmiar", "R, rozmiar" }, true);
      sort_dialog.draw();
      switch (sort_dialog.check_pressed()) {
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
      break;
    }
    }
    break;
  case e_project_mode::EDIT_PROJECTS:
    // Handle edit projects mode specific logic
    main_project_editor.handle_pressed(x, y);
    switch (project_editor_menu.check_pressed(x, y)) {
    case 0:{
      allert o_allert(300, 200, 200, 0xD6BA, "UWAGA",
                "Czy chcesz zapisać zmiany?", true);
            o_allert.draw();
            if(o_allert.check_pressed()==0){
              main_project_editor.save_changes_into_file();
            }
      main_project_editor.close_file();
      change_mode(e_project_mode::BROWSE_PROJECTS);
      main_project_explorer.get_files();
      break;}
    case 1:{
      main_project_editor.save_changes_into_file();
          break;}
    case 2:{
          break;}
    case 3:{
          break;}
    case 4:{
      if(!main_project_editor.remove_command()){
        allert failure_allert(300, 200, 200, 0xD6BA, "Blad",
            "Brak wybranego krokou do skasowania", false);
        failure_allert.draw();
        failure_allert.check_pressed();
      }
          break;}
    }
    break;
  }

  switch (step_mode) {
  case e_step_mode::STEP_BY_STEP:
    // Handle step by step mode specific logic
    break;
  case e_step_mode::CONTINUOUS:
    // Handle continuous mode specific logic
    break;
  }

  return 0;
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

