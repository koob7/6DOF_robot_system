#include "menu_popup.h"

popup::popup(int x, int y, int width, uint16_t background_color,
             std::string title, std::string text, int radius,
             uint16_t text_color, GFXfont *p_font)
    : button(-1, x, y, width, 0, background_color, radius, text, text_color,
             p_font),
      title_text(title) {
  title_box_height = 50;
  info_box_height_border = 30;
  button_height = 40;
}

void popup::store_screen(int x, int y, int width, int height) {
  lcd_Read_Area(x, y, width, height, save_screen_buffer);
}
void popup::restore_screen(int x, int y, int width, int height) {
  TFT_Restore_Area(x, y, width, height, save_screen_buffer);
}

list_dialog::list_dialog(int x, int y, int width, uint16_t background_color,
                         std::string title,
                         std::initializer_list<std::string> option_list,
                         bool cancel_option, int radius, uint16_t text_color,
                         GFXfont *p_font)
    : popup(x, y, width, background_color, title, "", radius, text_color,
            p_font),
      cancel_option(cancel_option) {
  title_box_height = 50;
  info_box_height_border = 10;
  button_height = 40;
  for (const auto &option : option_list) {
    options.push_back(option);
  }
  if (cancel_option) {
    options.push_back("Cancel");
  }
  options.shrink_to_fit();
}

int list_dialog::check_pressed() {
  int option_height = get_option_height();
  int range;
  if (cancel_option) {
    range = options.size() - 1;
  } else {
    range = options.size();
  }
  NVIC_DisableIRQ(EXTI9_5_IRQn);
  XPT2046_Init();
  __HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);
  NVIC_EnableIRQ(EXTI9_5_IRQn);
  while (1) {

    if (was_touched == 1) {
      was_touched = 0;
      for (int i = 0; i < range; i++) {
        if (check_area_pressed(touch_x, touch_y, object_dimension.x,
                               object_dimension.y + title_box_height +
                                   i * option_height,
                               object_dimension.width, option_height)) {
          restore_screen(object_dimension.x, object_dimension.y,
                         object_dimension.width, get_total_height());
          return i;
        }
      }
      if (cancel_option) {
        if (check_area_pressed(touch_x, touch_y, object_dimension.x,
                               object_dimension.y + title_box_height +
                                   range * option_height,
                               object_dimension.width, option_height)) {
          restore_screen(object_dimension.x, object_dimension.y,
                         object_dimension.width, get_total_height());
          return -1;
        }
      }
    }
  }
}

void list_dialog::draw() {
  store_screen(object_dimension.x, object_dimension.y, object_dimension.width,
               get_total_height());
  uint16_t height = get_total_height();
  int option_height = get_option_height();
  int counter = 0;
  // store_screen();
  if (radius == 0) {
    TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                            object_dimension.width, height, background_color);
  } else {
    TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
                             object_dimension.width, height, radius,
                             background_color);
  }
  TFT_Draw_Fill_Rectangle(object_dimension.x,
                          object_dimension.y + title_box_height,
                          object_dimension.width, 2, 0xB5B6);
  draw_center_text(object_dimension.x, object_dimension.y,
                   object_dimension.width, title_box_height, title_font, 1,
                   BLACK, title_text);
  for (const auto &option : options) {
    draw_center_text(
        object_dimension.x,
        object_dimension.y + title_box_height + counter * option_height,
        object_dimension.width, option_height, p_font, 1, text_color, option);
    if (option != options.back()) {
      TFT_Draw_Fill_Rectangle(object_dimension.x,
                              object_dimension.y + title_box_height +
                                  (counter + 1) * option_height,
                              object_dimension.width, 2, 0xB5B6);
    }
    counter++;
  }
}

allert::allert(int x, int y, int width, uint16_t background_color,
               std::string title, std::string text, bool cancel_option,
               int radius, uint16_t text_color, GFXfont *p_font)
    : popup(x, y, width, background_color, title, text, radius, text_color,
            p_font),
      cancel_option(cancel_option) {
  title_box_height = 50;
  info_box_height_border = 30;
  button_height = 40;
  if (!text.empty()) {
    splitText();
  }
  uint16_t start_y = object_dimension.y + get_total_height() - button_height;
  if (cancel_option) {
    buttons.push_back(button(
        0, object_dimension.x, start_y, object_dimension.width / 2,
        button_height, background_color, radius, "ok", BLACK, title_font));
    buttons.push_back(button(1, object_dimension.x + object_dimension.width / 2,
                             start_y, object_dimension.width / 2, button_height,
                             background_color, radius, "exit", BLACK,
                             title_font));
  } else {
    buttons.push_back(button(
        0, object_dimension.x, start_y, object_dimension.width, button_height,
        background_color, radius, "OK", BLACK, title_font));
  }
}

int allert::check_pressed() {
  NVIC_DisableIRQ(EXTI9_5_IRQn);
  XPT2046_Init();
  __HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);
  NVIC_EnableIRQ(EXTI9_5_IRQn);
  while (1) {
    if (was_touched == 1) {
      was_touched = 0;
      for (auto o_button : buttons) {
        if (o_button.check_pressed(touch_x, touch_y) > -1) {
          restore_screen(object_dimension.x, object_dimension.y,
                         object_dimension.width, get_total_height());
          return o_button.check_pressed(touch_x, touch_y);
        }
      }
    }
  }
}

void allert::draw() {
  uint16_t height = get_total_height(); // rozmiar czerwonego pola + minimalny
                                        // rozmiar informacji + dodatkowy
                                        // rozmiar informacji+ rozmiar przycisku
  store_screen(object_dimension.x, object_dimension.y, object_dimension.width,
               get_total_height());
  if (radius == 0) {
    TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                            object_dimension.width, height, background_color);
    TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
                            object_dimension.width, title_box_height, RED);
    TFT_Draw_Rectangle(object_dimension.x,
                       object_dimension.y + height - button_height,
                       object_dimension.width, button_height - 5, 5, BLACK);
  } else {
    TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
                             object_dimension.width, height, radius,
                             background_color);
    TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
                             object_dimension.width, title_box_height, radius,
                             RED);
    TFT_Draw_Round_Rect(
        object_dimension.x,
        object_dimension.y + height - button_height - 4, // sprawdzić to pięć
        object_dimension.width - 4, button_height, radius, 5, BLACK);
  }
  draw_center_text(object_dimension.x, object_dimension.y,
                   object_dimension.width, title_box_height, title_font, 1,
                   BLACK, title_text);
  draw_text_field(object_dimension.x, object_dimension.y + title_box_height,
                  object_dimension.width,
                  height - title_box_height - button_height);
  for (auto o_button : buttons) {
    o_button.draw();
  }
  if (cancel_option) {
    rectangle(object_dimension.x + object_dimension.width / 2 - 1,
              object_dimension.y + height - button_height, 2, button_height,
              0xB5B6)
        .draw();
  }
}

void allert::draw_text_field(uint16_t x, uint16_t y, uint16_t width,
                             uint16_t height) {
  int font_height = p_font->yAdvance * size;
  int start_y = y + height / 2 - (lines.size() - 1) * font_height / 2;
  for (struct line_content _line : lines) {
    char *ptr = new char[_line.content.size() + 1];
    strcpy(ptr, _line.content.c_str());
    LCD_Font(x + (width - _line.width) / 2, start_y, ptr, p_font, size,
             text_color);
    start_y += font_height;
    delete[] ptr;
  }
}

void allert::splitText() {

  std::istringstream stream(text);
  std::string word;
  std::string line = "";
  int word_length = 0;
  int line_length = 0;

  while (stream >> word) {
    word_length = 0;
    if (!line.empty()) { // wstawienie znaku spacji między wyrazami
      word.insert(word.begin(), ' ');
    }

    for (char c : word) { // obliczenie długości słowa
      if (c >= p_font->first && c <= p_font->last) {
        word_length += p_font->glyph[c - p_font->first].xAdvance * size;
      }
    }
    if (line_length + word_length + 1 >
        object_dimension.width) { // zapis obecnej, i stworzenie nowej lini
      lines.push_back(line_content(line, line_length));
      if (!line.empty()) {
        word_length -= p_font->glyph[' ' - p_font->first].xAdvance *
                       size; // odjęcie długości znaku spacji
        word.erase(0, 1);    // usunięcie znaku spacji z początku nowej lini
      }
      line_length = word_length; // stworznie nowej linidługości nowej lini
      line = word;
    } else {
      line_length += word_length; // aktualizacja lini
      line += word;
    }
  }
  if (!line.empty()) {
    lines.push_back(line_content(line, line_length)); // ostatnia linia tekstu
  }
  lines.shrink_to_fit();
}