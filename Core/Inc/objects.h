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
	std::vector<text_fields> text_fields;

public:
	void draw();
};


#endif /* INC_OBJECTS_H_ */
