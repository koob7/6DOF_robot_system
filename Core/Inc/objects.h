/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */

#ifndef INC_OBJECTS_H_
#define INC_OBJECTS_H_

#include <memory>
#include "menu_parts.h"

class menu_segment
{
	std::vector<std::shared_ptr<menu_part>> parts;

public:
	void draw()
	{
		for (const auto part : parts)
		{
			part->draw();
		}
	}
	void reduce_vector_size()
	{
		parts.shrink_to_fit();
	}
	void add_part(std::shared_ptr<menu_part> part)
	{
		parts.push_back(part);
	}

};

#endif /* INC_OBJECTS_H_ */
