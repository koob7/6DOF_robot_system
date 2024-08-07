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
	std::vector<button> buttons;
	std::vector<figure> figures;
	std::vector<text_field> text_fields;

public:
	void draw();
	void adjust_vector_size();
	void add_part(button o_button)
	{
		buttons.push_back(o_button);
	}
	void add_part(figure o_figure)
	{
		figures.push_back(o_figure);
	}
	void add_part(text_field o_text_field)
	{
		text_fields.push_back(o_text_field);
	}
};

#endif /* INC_OBJECTS_H_ */
