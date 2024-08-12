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
	void draw();
	void reduce_vector_size();
	void add_background_part(std::shared_ptr<menu_part> part){background_parts.push_back(part);}
	void add_part(std::shared_ptr<menu_part> part){top_parts.push_back(part);}
	void add_part(button o_button){buttons.push_back(o_button);}
	int check_pressed(int x, int y);
	void update_text(int id, std::string text);

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
