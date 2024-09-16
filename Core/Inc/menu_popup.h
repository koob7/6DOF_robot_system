#include "menu_block.h"
#ifndef INC_MENU_POPUP_H_
#define INC_MENU_POPUP_H_

class popup : public button {
protected:
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

class list_dialog : public popup {
public:
  std::vector<std::string> options;
  bool cancel_option;
  list_dialog(int x, int y, int width, uint16_t background_color,
              std::string title, std::initializer_list<std::string> option_list,
              bool cancel_option = true, int radius = 0,
              uint16_t text_color = 0x0000,
              GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));
  int check_pressed();
  void draw();

private:
  int get_option_height() {
    return p_font->yAdvance * size + info_box_height_border;
  }
  int get_total_height() {
    return options.size() * (p_font->yAdvance * size + info_box_height_border) +
           title_box_height;
  }
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

public:
  allert(int x, int y, int width, uint16_t background_color, std::string title,
         std::string text, bool cancel_option = true, int radius = 0,
         uint16_t text_color = 0x0000,
         GFXfont *p_font = const_cast<GFXfont *>(_Open_Sans_Bold_14));

  void draw();
  int check_pressed();

private:
  void splitText();
  void draw_text_field(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
  int get_total_height() {
    return lines.size() * p_font->yAdvance * size + title_box_height +
           info_box_height_border + button_height;
  }
};

#endif
