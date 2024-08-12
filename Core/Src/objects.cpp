/*
 * objects.cpp
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#include "objects.h"

	void menu_segment::draw()
	{
		for (const auto part : background_parts)
		{
			part->draw();
		}
		for (auto o_button : buttons)
		{
			o_button.draw();
		}
		for (const auto part : top_parts)
		{
			part->draw();
		}
	}

	void menu_segment::reduce_vector_size()
	{
		background_parts.shrink_to_fit();
		top_parts.shrink_to_fit();
		buttons.shrink_to_fit();
	}

int menu_segment::check_pressed(int x, int y)
{
	for (auto o_button : buttons)
	{
		if (o_button.check_pressed(x, y) > -1)
		{
			return o_button.check_pressed(x, y);
		}
	}
	return -1;
}

void menu_segment::update_text(int id, std::string text)
{
	for (auto o_button : buttons)
	{
		if (o_button.get_id() == id)
		{
			o_button.update_text(text);
			break;
		}
	}
}

