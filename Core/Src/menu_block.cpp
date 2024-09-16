/*
 * menu_parts.cpp
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */


#include "menu_block.h"
volatile uint8_t was_touched = 0;
uint16_t *save_screen_buffer = (uint16_t *)malloc(
    300 * 300 * sizeof(uint16_t)); // bufor zapisujący fragment ekranu

menu_block::menu_block(int x, int y, int width, int height)
    : object_dimension(x, y, width, height) {}

button::button(int id, int x, int y, int width, int height,
               uint16_t background_color, int radius, std::string text,
               uint16_t text_color, GFXfont *p_font, bool centered_text)
    : menu_block(x, y, width, height), id(id),
      background_color(background_color), radius(radius), text(text),
      text_color(text_color), p_font(p_font), centered_text(centered_text) {
  if (radius * 2 > (height > width ? width : height)) {
    radius = (height > width ? width : height);
  }
}

void button::draw() {
  if (radius == 0) {
    TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                            object_dimension.width, object_dimension.height,
                            background_color);
  } else {
    TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
                             object_dimension.width, object_dimension.height,
                             radius, background_color);
  }
  for (const auto &part : parts) {
    part->draw();
  }
  if (text.size() != 0) {
    if (centered_text)
      draw_center_text(object_dimension.x, object_dimension.y,
                       object_dimension.width, object_dimension.height, p_font,
                       1, text_color, text);
    else
      draw_text(object_dimension.x, object_dimension.y, object_dimension.height,
                p_font, 1, text_color, text);
  }
}

int button::check_pressed(int x, int y) {
  if (check_area_pressed(x, y, object_dimension.x, object_dimension.y,
                         object_dimension.width, object_dimension.height)) {
    return id;
  } else {
    return -1;
  }
}
bool button::check_area_pressed(int x, int y, int area_x, int area_y,
                                int area_width, int area_height) {
  return (x >= area_x && x <= area_x + area_width && y >= area_y &&
          y <= area_y + area_height);
}

void button::add_part(std::shared_ptr<menu_block> part) {
  parts.push_back(part);
}

text_field::text_field(int x, int y, int height, std::string text,
                       uint16_t text_color, GFXfont *p_font)
    : menu_block(x, y, 0, height), text(text), text_color(text_color),
      p_font(p_font) {}

text_field::text_field(int x, int y, int width, int height, std::string text,
                       uint16_t text_color, GFXfont *p_font)
    : menu_block(x, y, width, height), text(text), text_color(text_color),
      p_font(p_font) {}

void text_field::update_text(std::string new_text) {
  if (object_dimension.width != 0) {
    TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                            object_dimension.width, object_dimension.height,
                            0x8C51);
  }
  text = new_text;
}

void text_field::draw() {
  if (object_dimension.width == 0)
    draw_text(object_dimension.x, object_dimension.y, object_dimension.height,
              p_font, 1, text_color, text);
  else
    draw_center_text(object_dimension.x, object_dimension.y,
                     object_dimension.width, object_dimension.height, p_font, 1,
                     text_color, text);
}

circle::circle(int x, int y, uint16_t radius, uint16_t color,
               uint16_t border_size)
    : menu_block(x, y, 0, 0), radius(radius), color(color),
      border_size(border_size) {}

void circle::draw() {
  if (border_size == 0)
    TFT_Draw_Circle(object_dimension.x, object_dimension.y, radius, 1,
                    border_size, color);
  else
    TFT_Draw_Circle(object_dimension.x, object_dimension.y, radius, 0,
                    border_size, color);
}

triangle::triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                   uint16_t color, uint16_t border_size)
    : menu_block(0, 0, 0, 0), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3),
      color(color), border_size(border_size) {}

void triangle::draw() {
  if (border_size == 0)
    LCD_FillTriangle(x1, y1, x2, y2, x3, y3, color);
  else
    TFT_Draw_Triangle(x1, y1, x2, y2, x3, y3, border_size, color);
}

image::image(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
             const uint16_t *array, bool background)
    : menu_block(x, y, width, height), array(array), background(background) {}

void image::draw() {
  if (background)
    TFT_Draw_Bitmap(object_dimension.x, object_dimension.y,
                    object_dimension.width, object_dimension.height, array);
  else
    TFT_Draw_Bitmap_Without_Background(object_dimension.x, object_dimension.y,
                                       object_dimension.width,
                                       object_dimension.height, array);
}

rectangle::rectangle(int x, int y, int width, int height, uint16_t color,
                     uint16_t radius, uint16_t border_size)
    : menu_block(x, y, width, height), color(color), radius(radius),
      border_size(border_size) {}

void rectangle::draw() {
  if (border_size == 0) {
    if (radius == 0)
      TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                              object_dimension.width, object_dimension.height,
                              color);
    else
      TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
                               object_dimension.width, object_dimension.height,
                               radius, color);
  } else {
    if (radius == 0)
      TFT_Draw_Rectangle(object_dimension.x, object_dimension.y,
                         object_dimension.width, object_dimension.height,
                         border_size, color);
    else
      TFT_Draw_Round_Rect(object_dimension.x, object_dimension.y,
                          object_dimension.width, object_dimension.height,
                          radius, border_size, color);
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
