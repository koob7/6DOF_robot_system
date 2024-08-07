/*
 * menu_parts.cpp
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */
#include "menu_parts.h"
uint16_t *save_screen_buffer = (uint16_t*) malloc(300 * 300 * sizeof(uint16_t)); //bufor zapisujący fragment ekranu

menu_part::menu_part(int x, int y, int width, int height) :
		object_dimension(x, y, width, height)
{
}

button::button(int id, int x, int y, int width, int height,
		uint16_t background_color, int radius, std::string text,
		uint16_t text_color, GFXfont *p_font) :
		id(id), menu_part(x, y, width, height), background_color(
				background_color), radius(radius), text(text), text_color(
				text_color), p_font(p_font)
{
	if (radius * 2 > (height > width ? width : height))
	{
		radius = (height > width ? width : height);

	}
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
		draw_center_text(object_dimension.x, object_dimension.y,
				object_dimension.width, object_dimension.height, p_font, 1,
				text_color, text);
	}
}

int button::check_pressed(int x, int y)
{
	if (check_area_pressed(x, y, object_dimension.x, object_dimension.y,
			object_dimension.width, object_dimension.height))
	{
		return id;
	}
	else
	{
		return -1;
	}
}
bool button::check_area_pressed(int x, int y, int area_x, int area_y,
		int area_width, int area_height)
{
	return (x >= object_dimension.x && x <= area_x + area_width && y >= area_y
			&& y <= area_y + area_height);
}

popup::popup(int x, int y, int width, uint16_t background_color,
		std::string title, std::string text, int radius, uint16_t text_color,
		GFXfont *p_font) :
		button(-1, x, y, width, 0, background_color, radius, text, text_color,
				p_font), title_text(title)
{
	title_box_height = 50;
	info_box_height_border = 30;
	button_height = 40;
}

void popup::store_screen(int x, int y, int width, int height)
{
	lcd_Read_Area(x, y, width, height, save_screen_buffer);
}
void popup::restore_screen(int x, int y, int width, int height)
{
	TFT_Restore_Area(x, y, width, height, save_screen_buffer);
}

allert::allert(int x, int y, int width, uint16_t background_color,
		std::string title, std::string text, int radius, uint16_t text_color,
		GFXfont *p_font) :
		popup(x, y, width, background_color, title, text, radius, text_color,
				p_font)
{
	title_box_height = 50;
	info_box_height_border = 30;
	button_height = 40;
	if (!text.empty())
	{
		splitText();
	}
}

void allert::draw()
{
	uint16_t height = get_total_height(); //rozmiar czerwonego pola + minimalny rozmiar informacji + dodatkowy rozmiar informacji+ rozmiar przycisku
	store_screen(object_dimension.x, object_dimension.y,
			object_dimension.width, get_total_height());
	if (radius == 0)
	{
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, height, background_color);
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, title_box_height,
				RED);
		TFT_Draw_Rectangle(object_dimension.x,
				object_dimension.y + height - button_height,
				object_dimension.width, button_height - 5, 5,
				BLACK);
	}
	else
	{
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, height, radius, background_color);
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, title_box_height, radius,
				RED);
		TFT_Draw_Round_Rect(object_dimension.x,
				object_dimension.y + height - button_height - 4, //sprawdzić to pięć
				object_dimension.width - 4, button_height, radius, 5,
				BLACK);
	}
	draw_center_text(object_dimension.x, object_dimension.y,
			object_dimension.width, title_box_height, title_font, 1, BLACK,
			title_text);
	draw_text_field(object_dimension.x, object_dimension.y + title_box_height,
			object_dimension.width, height - title_box_height - button_height);
	draw_center_text(object_dimension.x,
			object_dimension.y + height - button_height, object_dimension.width,
			button_height, title_font, 1, BLACK, "OK");

}

bool allert::check_pressed(int x, int y)
{
	if (check_area_pressed(x, y, object_dimension.x,
			object_dimension.y + get_total_height() - button_height,
			object_dimension.width, button_height))
	{
		restore_screen(object_dimension.x, object_dimension.y,
				object_dimension.width, get_total_height());
		return true;
	}
	else
	{
		return false;
	}
}

void allert::draw_text_field(uint16_t x, uint16_t y, uint16_t width,
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

void allert::splitText()
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
text_field::text_field(int x, int y, int width, int height, std::string text,
		uint16_t text_color, GFXfont *p_font) :
		menu_part(x, y, width, height), text(text), text_color(text_color), p_font(
				p_font)
{

}

void text_field::draw()
{
	draw_center_text(object_dimension.x, object_dimension.y,
			object_dimension.width, object_dimension.height, p_font, 1,
			text_color, text);
}

void text_field::update_text(std::string new_text)
{
	text = new_text;
}

figure::figure(int x, int y, int width, int height, uint16_t color,
		uint16_t radius, uint16_t border_size) :
		menu_part(x, y, width, height), color(color), radius(radius), border_size(
				border_size)
{
	figure_shape = rectangle;
}
figure::figure(int x, int y, uint16_t color, uint16_t radius,
		uint16_t border_size) :
		menu_part(x, y, 0, 0), color(color), radius(radius), border_size(
				border_size)
{
	figure_shape = circle;
}
figure::figure(int x1, int y1, int x2, int y2, uint8_t x3, uint8_t y3,
		uint16_t color, uint16_t border_size) :
		menu_part(x1, y1, x2, y2), color(color), radius(radius), border_size(
				border_size), x3(x3), y3(y3)
{
	figure_shape = triangle;
}

void figure::draw()
{
	if (border_size == 0)
	{
		switch (figure_shape)
		{
		case rectangle:
			if (radius == 0)
				TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
						object_dimension.width, object_dimension.height, color);
			else
				TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
						object_dimension.width, object_dimension.height, radius,
						color);
			break;
		case circle:
			TFT_Draw_Circle(object_dimension.x, object_dimension.y, radius, 1,
					border_size, color);
			break;
		case triangle:
			LCD_FillTriangle(object_dimension.x, object_dimension.y,
					object_dimension.width, object_dimension.height, x3, y3,
					color);
			break;
		}
	}
	else
	{
		switch (figure_shape)
		{
		case rectangle:
			if (radius == 0)
				TFT_Draw_Rectangle(object_dimension.x, object_dimension.y,
						object_dimension.width, object_dimension.height,
						border_size, color);
			else
				TFT_Draw_Round_Rect(object_dimension.x, object_dimension.y,
						object_dimension.width, object_dimension.height, radius,
						border_size, color);
			break;
		case circle:
			TFT_Draw_Circle(object_dimension.x, object_dimension.y, radius, 0,
					border_size, color);
			break;
		case triangle:
			TFT_Draw_Triangle(object_dimension.x, object_dimension.y,
					object_dimension.width, object_dimension.height, x3, y3,
					border_size, color);
			break;
		}
	}
}

list_dialog::list_dialog(int x, int y, int width, uint16_t background_color,
		std::string title, std::initializer_list<std::string> option_list,
		int radius, uint16_t text_color, GFXfont *p_font) :
		popup(x, y, width, background_color, title, "", radius, text_color,
				p_font)
{
	title_box_height = 50;
	info_box_height_border = 10;
	button_height = 40;
	for (const auto &option : option_list)
	{
		options.push_back(option);
	}
}

int list_dialog::check_pressed(int x, int y)
{
	int counter = 0;
	int option_height = get_option_height();
	for (const auto &option : options)
	{
		if (check_area_pressed(x, y, object_dimension.x,
				object_dimension.y + title_box_height + counter * option_height,
				object_dimension.width, option_height))
		{
			restore_screen(object_dimension.x, object_dimension.y, object_dimension.width, get_total_height());
			return counter;
		}
		counter++;
	}
	return -1;
}

void list_dialog::draw()
{
	store_screen(object_dimension.x, object_dimension.y, object_dimension.width, get_total_height());
	uint16_t height = get_total_height(); //rozmiar czerwonego pola + minimalny rozmiar informacji + dodatkowy rozmiar informacji+ rozmiar przycisku
	int option_height = get_option_height();
	int counter = 0;
	//store_screen();
	if (radius == 0)
	{
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, height, background_color);
		TFT_Draw_Rectangle(object_dimension.x, object_dimension.y,
				object_dimension.width, title_box_height - 5, 5,
				BLACK);
	}
	else
	{
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width, height, radius, background_color);
		TFT_Draw_Round_Rect(object_dimension.x, object_dimension.y,
				object_dimension.width - 4, title_box_height, radius, 5,
				BLACK);
	}
	draw_center_text(object_dimension.x, object_dimension.y,
			object_dimension.width, title_box_height, title_font, 1, BLACK,
			title_text);
	for (const auto &option : options)
	{
		draw_center_text(object_dimension.x,
				object_dimension.y + title_box_height + counter * option_height,
				object_dimension.width,
				option_height, p_font, 1,
				text_color, option);
		if (option != options.back())
		{
			TFT_Draw_Fill_Rectangle(object_dimension.x,
					object_dimension.y + title_box_height + (counter + 1) * option_height,
					object_dimension.width, 2, BLACK);
		}
		counter++;
	}
//		draw_text_field(object_dimension.x, object_dimension.y + title_box_height,
//				object_dimension.width, height - title_box_height - button_height);
//		draw_center_text(object_dimension.x,
//				object_dimension.y + height - button_height, object_dimension.width,
//				button_height, title_font, 1, BLACK, "OK");

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

