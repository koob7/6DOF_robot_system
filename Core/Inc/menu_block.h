/*
 * menu_block.h
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */

#ifndef INC_MENU_BLOCK_H_
#define INC_MENU_BLOCK_H_

#include "display_ssd1963.h"
#include "tim.h"
#include "xpt2046.h"
#include <iostream>
#include <memory>

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

class menu_block {
public:
  struct dimension object_dimension;

  menu_block(int x, int y, int width, int height);
  virtual void draw() = 0;
  virtual void update_text(std::string new_text) {}
};

class button : public menu_block {
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
  GFXfont *p_font;
  bool centered_text;
  std::vector<std::shared_ptr<menu_block>> parts;

  button(int id, int x, int y, int width, int height, uint16_t background_color,
         int radius = 0, std::string text = "", uint16_t text_color = BLACK,
         GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14),
         bool centered_text = true);
  void draw();
  int check_pressed(int x, int y);
  bool check_area_pressed(int x, int y, int area_x, int area_y, int area_width,
                          int area_height);
  void add_part(std::shared_ptr<menu_block> part);
  void update_text(std::string new_text) { text = new_text; }
  int get_id() { return id; }
};

class text_field : public menu_block {
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

class circle : public menu_block {
public:
  uint16_t color;
  uint16_t radius;
  uint16_t border_size;
  circle(int x, int y, uint16_t radius, uint16_t color,
         uint16_t border_size = 0);
  void draw();
};
class triangle : public menu_block {
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
class image : public menu_block {
public:
  const uint16_t *array;
  bool background;
  image(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
        const uint16_t *array, bool background);
  void draw();
};
class rectangle : public menu_block {
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
