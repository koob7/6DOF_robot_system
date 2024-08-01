/*
 * menu_parts.cpp
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */
#include "menu_parts.h"
uint16_t *save_screen_buffer = (uint16_t*) malloc(300 *300  * sizeof(uint16_t));//bufor zapisujący fragment ekranu

menu_part::menu_part(int x, int y, int width, int height) :
		object_dimension(x, y, width, height)
{
}

button::button(int x, int y, int width, int height, uint16_t background_color,
		int radius, std::string text, uint16_t text_color, GFXfont *p_font) :
		menu_part(x, y, width, height), background_color(background_color), radius(
				radius), text(text), text_color(text_color), p_font(p_font)
{
	if (radius * 2 > (height > width ? width : height))
	{
		radius = (height > width ? width : height);

	}
	if (!text.empty())
	{
		splitText();
	}
}
int button::get_required_height()
{
	int font_height = p_font->yAdvance * size;
	return lines.size() * font_height;
}

void button::draw()
{
	if (radius == 0)
	{
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, object_dimension.height,
				background_color);
	}
	else
	{
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, object_dimension.height, radius,
				background_color);
	}
	if (text.size() != 0)
	{
		draw_text_field(object_dimension.x, object_dimension.y,
				object_dimension.width, object_dimension.height);
	}
}

void button::draw_text_field(uint16_t x, uint16_t y, uint16_t width,
		uint16_t height)
{
	int font_height = p_font->yAdvance * size;
	int start_y = y + height / 2 - (lines.size() - 1) * font_height / 2;
	for (struct line_content _line : lines)
	{
		char *ptr = new char[_line.content.size() + 1];
		strcpy(ptr, _line.content.c_str());
		LCD_Font(x + (width - _line.width) / 2, start_y, ptr, p_font, size,
				text_color);
		start_y += font_height;
		delete[] ptr;
	}
}

bool button::check_pressed(int x, int y)
{
	return check_area_pressed(x, y, object_dimension.x, object_dimension.y,
			object_dimension.width, object_dimension.height);
}
bool button::check_area_pressed(int x, int y, int area_x, int area_y,
		int area_width, int area_height)
{
	if (x >= object_dimension.x && x <= area_x + area_width && y >= area_y
			&& y <= area_y + area_height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void menu_part::draw_center_text(uint16_t x, uint16_t y, uint16_t width,
		uint16_t height, const GFXfont *p_font, uint8_t size, uint16_t color,
		const std::string &text)
{
	struct line_content
	{
		std::string content;
		int width;
		line_content(std::string content, int width) :
				content(content), width(width)
		{
		}
	};
	std::vector<struct line_content> lines;
	std::istringstream stream(text);
	std::string word;
	std::string line = "";
	int word_length = 0;
	int line_length = 0;
	int font_height = p_font->yAdvance * size;

	uint16_t licznik = 0;
	while (stream >> word)
	{
		word_length = 0;
		if (!line.empty())
		{ // wstawienie znaku spacji między wyrazami
			word.insert(word.begin(), ' ');
		}

		for (char c : word)
		{ // obliczenie długości słowa
			if (c >= p_font->first && c <= p_font->last)
			{
				word_length += p_font->glyph[c - p_font->first].xAdvance * size;
			}
		}
		if (line_length + word_length + 1 > width)
		{ // zapis obecnej, i stworzenie nowej lini
			lines.push_back(line_content(line, line_length));
			if (!line.empty())
			{
				word_length -= p_font->glyph[' ' - p_font->first].xAdvance
						* size; // odjęcie długości znaku spacji
				word.erase(0, 1); // usunięcie znaku spacji z początku nowej lini
			}
			line_length = word_length; // stworznie nowej linidługości nowej lini
			line = word;
		}
		else
		{
			line_length += word_length; // aktualizacja lini
			line += word;
		}
	}
	if (!line.empty())
	{
		lines.push_back(line_content(line, line_length)); // ostatnia linia tekstu
	}
	int start_y = y + height / 2 - ((lines.size() - 1) * font_height) / 2;
	for (struct line_content _line : lines)
	{
		char *ptr = new char[_line.content.size() + 1];
		strcpy(ptr, _line.content.c_str());
		LCD_Font(x + (width - _line.width) / 2, start_y, ptr, p_font, size,
				color);
		start_y += font_height;
		delete[] ptr;
	}
}

void button::splitText()
{

	std::istringstream stream(text);
	std::string word;
	std::string line = "";
	int word_length = 0;
	int line_length = 0;

	while (stream >> word)
	{
		word_length = 0;
		if (!line.empty())
		{ // wstawienie znaku spacji między wyrazami
			word.insert(word.begin(), ' ');

		}

		for (char c : word)
		{ // obliczenie długości słowa
			if (c >= p_font->first && c <= p_font->last)
			{
				word_length += p_font->glyph[c - p_font->first].xAdvance * size;
			}
		}
		if (line_length + word_length + 1 > object_dimension.width)
		{ // zapis obecnej, i stworzenie nowej lini
			lines.push_back(line_content(line, line_length));
			if (!line.empty())
			{
				word_length -= p_font->glyph[' ' - p_font->first].xAdvance
						* size; // odjęcie długości znaku spacji
				word.erase(0, 1); // usunięcie znaku spacji z początku nowej lini
			}
			line_length = word_length; // stworznie nowej linidługości nowej lini
			line = word;
		}
		else
		{
			line_length += word_length; // aktualizacja lini
			line += word;
		}
	}
	if (!line.empty())
	{
		lines.push_back(line_content(line, line_length)); // ostatnia linia tekstu
	}
}

allert::allert(int x, int y, int width, uint16_t background_color,
		std::string title, std::string text, int radius, uint16_t text_color,
		GFXfont *p_font) :
		button(x, y, width, 0, background_color, radius, text, text_color,
				p_font), title_text(title)
{
}

void allert::draw()
{
	uint16_t height = red_box_height + get_required_height() + info_box_height_border + button_height; //rozmiar czerwonego pola + minimalny rozmiar informacji + dodatkowy rozmiar informacji+ rozmiar przycisku
	store_screen();
	if (radius == 0)
	{
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, height, background_color);
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, red_box_height,
				RED);
		TFT_Draw_Rectangle(object_dimension.x, object_dimension.y + height - button_height,
				object_dimension.width, button_height, 5,
				BLACK);
	}
	else
	{
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, height, radius, background_color);
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, red_box_height, radius,
				RED);
		TFT_Draw_Round_Rect(object_dimension.x,
				object_dimension.y + height - button_height - 4, //sprawdzić to pięć
				object_dimension.width - 4, button_height, radius, 5,
				BLACK);
	}
	draw_center_text(object_dimension.x, object_dimension.y,
			object_dimension.width, red_box_height, title_font, 1, BLACK, title_text);
	draw_text_field(object_dimension.x, object_dimension.y + red_box_height,
			object_dimension.width, height - red_box_height - button_height);
	draw_center_text(object_dimension.x, object_dimension.y + height - button_height,
			object_dimension.width, button_height, title_font, 1, BLACK, "OK");

}

bool allert::check_pressed(int x, int y)
{
	if( check_area_pressed(x, y, object_dimension.x,
			object_dimension.y + red_box_height + get_required_height()+info_box_height_border,
			object_dimension.width, button_height))
	{
		restore_screen();
		return true;
	}
	else{
		return false;
	}
}

void allert::store_screen(){
	lcd_Read_Area(object_dimension.x, object_dimension.y,object_dimension.width,red_box_height + get_required_height() + info_box_height_border + button_height,
			  save_screen_buffer);
}
void allert::restore_screen(){
	TFT_Restore_Area(object_dimension.x, object_dimension.y,
			object_dimension.width, red_box_height + get_required_height() + info_box_height_border + button_height, save_screen_buffer);
}










