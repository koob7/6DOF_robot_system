/*
 * objects.cpp
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#include "menu_segment.h"

FATFS file_system;



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

void menu_segment::update_text(int id, std::string text,
    enum e_menu_layer menu_layer) {

  switch (menu_layer) {
  case e_menu_layer::e_buttons: {
    for (auto &o_button : buttons) {
      if (o_button.get_id() == id) {
        o_button.update_text(text);
        o_button.draw();
        break;
      }
    }

    break;
  }
  case e_menu_layer::e_top_parts: {
    if (id >= 0 && id < static_cast<int>(top_parts.size())
        && top_parts[id] != nullptr) {
      top_parts[id]->update_text(text);
      top_parts[id]->draw();
    }
    break;
  }
  case e_menu_layer::e_background_parts: {
    if (id >= 0 && id < static_cast<int>(background_parts.size())
        && background_parts[id] != nullptr) {
      background_parts[id]->update_text(text);
      background_parts[id]->draw();
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
