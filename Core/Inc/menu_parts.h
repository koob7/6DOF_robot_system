/*
 * menu_parts.h
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */

#ifndef INC_MENU_PARTS_H_
#define INC_MENU_PARTS_H_

#include "display_ssd1963.h"
#include <iostream>
#include <memory>
#include "tim.h"
#include "xpt2046.h"

#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"
#include "bitmap_arrays.h"
#include "math.h"
#include "servo.h"

#define _Open_Sans_Bold_8 &Open_Sans_Bold_8
#define _Open_Sans_Bold_9 &Open_Sans_Bold_9
#define _Open_Sans_Bold_10 &Open_Sans_Bold_10
#define _Open_Sans_Bold_11 &Open_Sans_Bold_11
#define _Open_Sans_Bold_12 &Open_Sans_Bold_12
#define _Open_Sans_Bold_14 &Open_Sans_Bold_14
#define _Open_Sans_Bold_16 &Open_Sans_Bold_16
#define _Open_Sans_Bold_18 &Open_Sans_Bold_18
#define _Open_Sans_Bold_20 &Open_Sans_Bold_20
#define _Open_Sans_Bold_22 &Open_Sans_Bold_22
#define _Open_Sans_Bold_24 &Open_Sans_Bold_24
#define _Open_Sans_Bold_26 &Open_Sans_Bold_26
#define _Open_Sans_Bold_28 &Open_Sans_Bold_28
#define _Open_Sans_Bold_36 &Open_Sans_Bold_36
#define _Open_Sans_Bold_48 &Open_Sans_Bold_48
#define _Open_Sans_Bold_72 &Open_Sans_Bold_72
#define _Open_Sans_Bold_96 &Open_Sans_Bold_96
#define _Open_Sans_Bold_112 &Open_Sans_Bold_112
#define _Open_Sans_Bold_128 &Open_Sans_Bold_128


extern volatile uint8_t was_touched;

extern uint16_t *save_screen_buffer; // bufor zapisujący fragment ekranu

static const uint8_t size = 1;

struct dimension {
  int x;
  int y;
  int width;
  int height;

  dimension(int x, int y, int width, int height)
      : x(x), y(y), width(width), height(height) {}
};

class menu_part {
public:
  struct dimension object_dimension;

  menu_part(int x, int y, int width, int height);
  virtual void draw() = 0;
  virtual void update_text(std::string new_text) {}
};

class button : public menu_part {
public:
  struct line_content {
    std::string content;
    int width;
    line_content(std::string content, int width)
        : content(content), width(width) {}
  };
  int id;
  uint16_t background_color;
  int radius;
  std::string text;
  uint16_t text_color;
  bool centered_text;
  std::vector<std::shared_ptr<menu_part>> parts;
  GFXfont *p_font;
  button(int id, int x, int y, int width, int height, uint16_t background_color,
         int radius = 0, std::string text = "", uint16_t text_color = BLACK,
         GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14),
         bool centered_text = true);
  void draw();
  int check_pressed(int x, int y);
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
                          int area_height);
  void add_part(std::shared_ptr<menu_part> part);
  void update_text(std::string new_text) {
    text = new_text;
  }
  int get_id() { return id; }
};

class popup : public button {
public:
  popup(int x, int y, int width, uint16_t background_color, std::string title,
        std::string text, int radius = 0, uint16_t text_color = 0xFFFF,
        GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));
  GFXfont *title_font = const_cast<GFXfont *>(_Open_Sans_Bold_28);
  uint8_t title_box_height;
  uint8_t info_box_height_border;
  uint8_t button_height;
  std::string title_text;

  void store_screen(int x, int y, int width, int height);
  void restore_screen(int x, int y, int width, int height);
};

class allert : public popup {


  struct line_content {
    std::string content;
    int width;
    line_content(std::string content, int width)
        : content(content), width(width) {}
  };
  std::vector<struct line_content> lines;
  bool cancel_option;
  std::vector<button> buttons;
  int get_total_height() {
    return lines.size() * p_font->yAdvance * size + title_box_height +
           info_box_height_border + button_height;
  }
  void splitText();
  void draw_text_field(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
public:
  allert(int x, int y, int width, uint16_t background_color,  std::string title,
         std::string text, bool cancel_option = true,int radius = 0, uint16_t text_color = 0x0000,
         GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));




  void draw();
  int check_pressed();
  //bool check_pressed(int x, int y){}
};

class list_dialog : public popup {
public:
  std::vector<std::string> options;
  bool cancel_option;
  list_dialog(int x, int y, int width, uint16_t background_color,
              std::string title, std::initializer_list<std::string> option_list,bool cancel_option = true,
              int radius = 0, uint16_t text_color = 0x0000,
              GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));
  int get_total_height() {
    return options.size() * (p_font->yAdvance * size + info_box_height_border) +
           title_box_height;
  }
  int get_option_height() {
    return p_font->yAdvance * size + info_box_height_border;
  }

  // return -1 if no button is pressed
  int check_pressed();
  void draw();
};

class text_field : public menu_part {
public:
  std::string text;
  uint16_t text_color;
  GFXfont *p_font;
  text_field(int x, int y, int height, std::string text,
             uint16_t text_color = BLACK,
             GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));
  text_field(int x, int y, int width, int height, std::string text,
             uint16_t text_color = BLACK,
             GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));
  void draw();
  void update_text(std::string new_text);
};

class circle : public menu_part {
public:
  uint16_t color;
  uint16_t radius;
  uint16_t border_size;
  circle(int x, int y, uint16_t radius, uint16_t color,
         uint16_t border_size = 0);
  void draw();
};
class triangle : public menu_part {
public:
  int x1, y1;
  int x2, y2;
  int x3, y3;
  uint16_t color;
  uint16_t border_size;
  triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color,
           uint16_t border_size = 0);
  void draw();
};
class image : public menu_part {
public:
  const uint16_t *array;
  bool background;
  image(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
        const uint16_t *array, bool background);
  void draw();
};
class rectangle : public menu_part {
public:
  uint16_t color;
  uint16_t radius;
  uint16_t border_size;

  rectangle(int x, int y, int width, int height, uint16_t color,
            uint16_t radius = 0, uint16_t border_size = 0);
  void draw();
};

#endif /* INC_MENU_PARTS_H_ */

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
//
