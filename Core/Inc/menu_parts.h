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

struct dimension {
	int x;
	int width;
	int y;
	int height;

	dimension(int x, int y, int width, int height) :
			x(x), y(y), width(width), height(height) {
	}
};

class menu_part {
public:
	struct dimension object_dimension;

	menu_part(int x, int y, int width, int height);

	virtual void draw_object();
};

class button: public menu_part {
public:
	int radius = 0;
	uint16_t background_color;
	uint16_t text_color;
	std::string text;
	button(int x, int y, int width, int height, uint16_t background_color, int radius = 0,
			std::string text = "", uint16_t text_color= 0xFFFF);

	void draw();
	bool check_pressed(int x, int y);
};

#endif /* INC_MENU_PARTS_H_ */
