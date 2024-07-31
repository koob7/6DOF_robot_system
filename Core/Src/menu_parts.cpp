/*
 * menu_parts.cpp
 *
 *  Created on: Jul 31, 2024
 *      Author: kobie
 */
#include "menu_parts.h"

menu_part::menu_part(int x, int y, int width, int height) :
		object_dimension(x, y, width, height) {
}


button::button(int x, int y, int width, int height, uint16_t background_color, int radius,
		std::string text, uint16_t text_color) :
		menu_part(x, y, width, height), background_color(background_color), radius(radius), text(text), text_color(text_color) {

}

void button::draw(){
	if(radius==0){
		TFT_Draw_Fill_Rectangle(object_dimension.x, object_dimension.y, object_dimension.width, object_dimension.height, background_color);
	}
	else{
		TFT_Draw_Fill_Round_Rect(object_dimension.x, object_dimension.y, object_dimension.width, object_dimension.height, radius, background_color);
	}
	if (text.size()!=0){

	}
}

bool button::check_pressed(int x, int y) {
	if (x >= object_dimension.x
			&& x <= object_dimension.x + object_dimension.width
			&& y >= object_dimension.y
			&& y <= object_dimension.y + object_dimension.height) {
		return true;
	} else {
		return false;
	}
}

