/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */

#ifndef INC_OBJECTS_H_
#define INC_OBJECTS_H_


#include "menu_parts.h"

class menu_segment
{
	std::vector<std::shared_ptr<menu_part>> top_parts;
	std::vector<std::shared_ptr<menu_part>> background_parts;
	std::vector<button> buttons;

public:
	void draw()
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
	void reduce_vector_size()
	{
		background_parts.shrink_to_fit();
		top_parts.shrink_to_fit();
		buttons.shrink_to_fit();
	}
	void add_background_part(std::shared_ptr<menu_part> part)
	{
		background_parts.push_back(part);
	}
	void add_part(std::shared_ptr<menu_part> part)
	{
		top_parts.push_back(part);
	}
	void add_part(button o_button)
	{
		buttons.push_back(o_button);
	}
	int check_pressed(int x, int y)
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
	void update_text(int id, std::string text)
	{
		for (auto o_button : buttons)
				{
					if (o_button.get_id() ==id)
					{
						o_button.update_text(text);
						break;
					}
				}
	}

};

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

#endif /* INC_OBJECTS_H_ */
