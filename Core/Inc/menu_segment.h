/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#ifndef INC_MENU_SEGMENT_H
#define INC_MENU_SEGMENT_H


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
