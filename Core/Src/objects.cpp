/*
 * objects.cpp
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#include "objects.h"
	void menu_segment::adjust_vector_size(){
		buttons.shrink_to_fit();
		figures.shrink_to_fit();
		text_fields.shrink_to_fit();
	}
	void menu_segment::draw(){
		for (button o_button : buttons){
			o_button.draw();
		}
		for (figure o_figure : figures){
			o_figure.draw();
		}
		for (text_field o_text_field : text_fields){
			o_text_field.draw();
		}
	}


