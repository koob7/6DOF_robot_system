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

extern uint16_t *save_screen_buffer; //bufor zapisujący fragment ekranu

static const uint8_t size = 1;

struct dimension
{
	int x;
	int width;
	int y;
	int height;

	dimension(int x, int y, int width, int height) :
			x(x), y(y), width(width), height(height)
	{
	}
};

class menu_part
{
public:
	struct dimension object_dimension;

	menu_part(int x, int y, int width, int height);
};

class button: public menu_part
{
public:

	struct line_content
	{
		std::string content;
		int width;
		line_content(std::string content, int width) :
				content(content), width(width)
		{
		}
	};
	int id;
	uint16_t background_color;
	int radius;
	std::string text;
	uint16_t text_color;

	GFXfont *p_font;
	button(int id, int x, int y, int width, int height,
			uint16_t background_color, int radius = 0, std::string text = "",
			uint16_t text_color = BLACK, GFXfont *p_font =
					const_cast<GFXfont*>(_Open_Sans_Bold_14));
	void draw();
	int check_pressed(int x, int y);
	bool check_area_pressed(int x, int y, int area_x, int area_y,
			int area_width, int area_height);

};

class popup: public button
{
public:
	popup(int x, int y, int width, uint16_t background_color, std::string title,
			std::string text, int radius = 0, uint16_t text_color = 0xFFFF,
			GFXfont *p_font = const_cast<GFXfont*>(_Open_Sans_Bold_14));
	GFXfont *title_font = const_cast<GFXfont*>(_Open_Sans_Bold_28);
	uint8_t title_box_height;
	uint8_t info_box_height_border;
	uint8_t button_height;
	std::string title_text;

};

class allert: public popup
{

public:
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

	allert(int x, int y, int width, uint16_t background_color,
			std::string title, std::string text, int radius = 0,
			uint16_t text_color = 0xFFFF, GFXfont *p_font =
					const_cast<GFXfont*>(_Open_Sans_Bold_14));
	void splitText();
	int get_total_height()
	{
		return lines.size() * p_font->yAdvance * size+ title_box_height +info_box_height_border+ button_height;
	}
	void draw_text_field(uint16_t x, uint16_t y, uint16_t width,
			uint16_t height);

	void draw();
	bool check_pressed(int x, int y);

	void store_screen();
	void restore_screen();

};

class list_dialog: public popup{
	std::vector<std::string> options;
	list_dialog(int x, int y, int width, uint16_t background_color,
			std::string title, int radius = 0,
			uint16_t text_color = 0xFFFF, GFXfont *p_font =
					const_cast<GFXfont*>(_Open_Sans_Bold_14));
	int get_total_height()
	{
		return options.size() * (p_font->yAdvance+info_box_height_border) * size + title_box_height;
	}
	int check_pressed(int x, int y);
};

class text_field: public menu_part
{
public:

	std::string text;
	uint16_t text_color;
	GFXfont *p_font;

	text_field(int x, int y, int width, int height, std::string text,
			uint16_t text_color = BLACK, GFXfont *p_font =
					const_cast<GFXfont*>(_Open_Sans_Bold_14));
	void draw();
	void update_text(std::string new_text);
};

class figure: public menu_part
{
	enum shape
	{
		rectangle, circle, triangle
	};
	enum shape figure_shape;
	uint16_t color;
	uint16_t radius=0;
	uint8_t border_size;
	uint8_t x3 = 0;
	uint8_t y3 = 0;
	figure(int x, int y, int width, int height, uint16_t color,
			uint16_t radius, uint16_t border_size);
	figure(int x, int y, uint16_t color, uint16_t radius,
			uint16_t border_size);
	figure(int x1, int y1, int x2, int y2, uint8_t x3, uint8_t y3,
			uint16_t color, uint16_t border_size);
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
