/*
 * objects.cpp
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */
#include "objects.h"

void menu_segment::draw()
{
	for (auto part : background_parts)
	{
		part->draw();
	}
	for (auto o_button : buttons)
	{
		o_button.draw();
	}
	for (auto part : top_parts)
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

projects_explorer::projects_explorer()
{
	page_up_btn.add_part(
			std::make_shared<triangle>(150, 185, 150 + 23, 185, 161, 165,
					0x00FD));
	page_down_btn.add_part(
			std::make_shared<triangle>(150, 432, 150 + 23, 432, 161, 452,
					0x00FD));
	if (f_mount(&file_system, "/", 1) == FR_OK)
	{
		get_files();
		initialized = true;
	}
	else
		initialized = false;
}

void projects_explorer::update_last_file_to_display()
{
	last_file_to_display =
			((first_file_to_display + project_explorer_num_files_on_page)
					> sd_files.size()) ?
					sd_files.size() :
					(first_file_to_display + project_explorer_num_files_on_page);
}

void projects_explorer::get_files()
{
	sd_files.clear();
	if (f_opendir(&directory, "/") == FR_OK)
	{
		for (;;)
		{
			if (f_readdir(&directory, &fno) != FR_OK || fno.fname[0] == 0)
				break;
			if (std::string(fno.fname).find(".txt") != std::string::npos)
			{
				sd_files.push_back(fno);
			}
		}
	}
	first_file_to_display = 0;
	update_last_file_to_display();
	selected_file = -1;
	sort_files();
}

void projects_explorer::sort_files()
{
	auto compare = [this](const FILINFO &a, const FILINFO &b)
	{
		switch (option)
		{
			case by_name:
			return sort_ascending ? a.fname < b.fname : a.fname > b.fname;
			case by_size:
			return sort_ascending ? a.fsize < b.fsize : a.fsize > b.fsize;
			case by_date:
			return sort_ascending ? a.fdate < b.fdate : a.fdate > b.fdate;
			default:
			return false;
		}
	};
	std::sort(sd_files.begin(), sd_files.end(), compare);
	selected_file = -1;
	draw();
}

void projects_explorer::set_sort_option(enum sort_option in_option,
		bool in_sort_ascending)
{
	option = in_option;
	sort_ascending = in_sort_ascending;
	sort_files();
}

std::string projects_explorer::get_choosen_file()
{
	if (selected_file >= 0)
	{
		return sd_files[selected_file].fname;
	}
	else
	{
		// TODO tutaj powinien być rzucany wyjątek w przyszłości
		return "";
	}
}

void projects_explorer::draw()
{
	if (first_file_to_display > 0)
	{
		page_up_btn.draw();
	}
	else
	{
		TFT_Draw_Fill_Rectangle(142, 158, 40, 40, clear_screen_color);
	}
	if (sd_files.size() > last_file_to_display)
	{
		page_down_btn.draw();
	}
	else
	{
		TFT_Draw_Fill_Rectangle(142, 425, 40, 40, clear_screen_color);
	}
	int i = first_file_to_display;
	int pos_counter = 0;
	for (; i < last_file_to_display; i++)
	{
		TFT_Draw_Fill_Rectangle(project_explorer_start_pos_x,
				project_explorer_start_pos_y
						+ pos_counter * (project_explorer_line_height +
						project_explorer_line_space) -
				project_explorer_line_space / 2 - 1, 460, 2, 0xB5B6);
		if (i == selected_file)
		{
			TFT_Draw_Fill_Round_Rect(project_explorer_start_pos_x,
					project_explorer_start_pos_y
							+ pos_counter * (project_explorer_line_height +
							project_explorer_line_space), 460,
					project_explorer_line_height, 10, 0xB6DF);
		}
		else
		{
			TFT_Draw_Fill_Rectangle(project_explorer_start_pos_x,
					project_explorer_start_pos_y
							+ pos_counter * (project_explorer_line_height +
							project_explorer_line_space), 460,
					project_explorer_line_height,
					clear_screen_color);
		}
		draw_text(project_explorer_start_pos_x,
				project_explorer_start_pos_y
						+ pos_counter
								* (project_explorer_line_height
										+ project_explorer_line_space),
				project_explorer_line_height, project_explorer_file_menu_font, 1,
		BLACK, sd_files[i].fname);
		draw_text(project_explorer_start_pos_x + 153,
				project_explorer_start_pos_y
						+ pos_counter
								* (project_explorer_line_height
										+ project_explorer_line_space),
				project_explorer_line_height, project_explorer_file_menu_font, 1,
		BLACK, format_date(sd_files[i].fdate));
		draw_text(project_explorer_start_pos_x + 153 * 2,
				project_explorer_start_pos_y
						+ pos_counter
								* (project_explorer_line_height
										+ project_explorer_line_space),
				project_explorer_line_height, project_explorer_file_menu_font, 1,
		BLACK, std::to_string(sd_files[i].fsize));
		pos_counter++;
	}
}

void projects_explorer::forget_selected_hiden_file()
{
	if ((selected_file < first_file_to_display
			|| selected_file > last_file_to_display) &&
	forget_when_hiden)
	{
		selected_file = -1;
	}
}

void projects_explorer::handle_pressed(int x, int y)
{
	if (first_file_to_display > 0)
	{
		if (page_up_btn.check_pressed(x, y) == 0)
		{
			first_file_to_display--;
			update_last_file_to_display();
			forget_selected_hiden_file();
			draw();
		}
	}
	if (sd_files.size() > last_file_to_display)
	{
		if (page_down_btn.check_pressed(x, y) == 1)
		{
			first_file_to_display++;
			update_last_file_to_display();
			forget_selected_hiden_file();
			draw();
		}
	}
	int i = first_file_to_display;
	int pos_counter = 0;
	for (; i < last_file_to_display; i++)
	{
		if (check_area_pressed(x, y, project_explorer_start_pos_x,
				project_explorer_start_pos_y
						+ pos_counter * (project_explorer_line_height +
						project_explorer_line_space), 460,
				project_explorer_line_height))
		{
			selected_file = i;
			draw();
			break;
		}
		pos_counter++;
	}
}

void projects_explorer::create_file(std::string name)
{
	FIL file;
	const char *filename = name.c_str();
	if (f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK)
	{
		f_close(&file);
	}
	else
	{
		// TODO tutaj powinien być rzucany wyjątek
	}
	get_files();
}

std::string projects_explorer::format_date(WORD fdate)
{
	std::stringstream dateStream;
	int day = fdate & 0x1F;
	int month = (fdate >> 5) & 0xF;
	int year = (fdate >> 9) + 1980;
	dateStream << std::setw(2) << std::setfill('0') << day << "-"
			<< std::setw(2) << std::setfill('0') << month << "-" << std::setw(4)
			<< std::setfill('0') << year;

	return dateStream.str();
}

bool projects_explorer::check_area_pressed(int x, int y, int area_x, int area_y,
		int area_width, int area_height)
{
	return (x >= area_x && x <= area_x + area_width && y >= area_y
			&& y <= area_y + area_height);
}

void projects_explorer::delete_file()
{
	if (selected_file >= -1)
	{
		if (f_unlink(sd_files[selected_file].fname) == FR_OK)
		{
			get_files();
		}
	}
	else
	{
		// TODO tutaj powinien być rzucany wyjątek w przypadku nieudanego usunięcia
	}
}

project_editor::movement::movement(float target_x, float target_y,
		float target_z, float target_a, float target_b, float target_c,
		uint8_t speed, enum e_movement_type movement_type) :
		target_x(target_x), target_y(target_y), target_z(target_z), target_a(
				target_a), target_b(target_b), target_c(target_c), speed(speed), movement_type(
				movement_type)
{

}

project_editor::mov_streight::mov_streight(float target_x, float target_y,
		float target_z, float target_a, float target_b, float target_c,
		uint8_t speed, enum e_movement_type movement_type) :
		movement(target_x, target_y, target_z, target_a, target_b, target_c,
				speed, movement_type)
{

}

project_editor::mov_circular::mov_circular(float target_x, float target_y,
		float target_z, float target_a, float target_b, float target_c,
		float help_x, float help_y, float help_z, float help_a, float help_b,
		float help_c, uint8_t speed, enum e_movement_type movement_type) :
		movement(target_x, target_y, target_z, target_a, target_b, target_c,
				speed, movement_type), help_x(help_x), help_y(help_y), help_z(
				help_z), help_a(help_a), help_b(help_b), help_c(help_c)
{

}

project_editor::cmd_wait::cmd_wait(uint16_t time_milisecond) :
		time_milisecond(time_milisecond)
{

}
project_editor::cmd_set_pin::cmd_set_pin(enum e_output_pin output_pin,
		bool set_pin_high) :
		output_pin(output_pin), set_pin_high(set_pin_high)
{

}

void project_editor::mov_streight::update_command(float in_target_x, float in_target_y, float in_target_z, float in_target_a,
        float in_target_b, float in_target_c, uint8_t in_speed,
        enum e_movement_type in_movement_type){
	target_x = in_target_x;
	target_y = in_target_y;
	target_z = in_target_z;
	target_a = in_target_a;
	target_b = in_target_b;
	target_c = in_target_c;
	speed = in_speed;
	movement_type = in_movement_type;
}

void project_editor::mov_circular::update_command(float in_target_x, float in_target_y, float in_target_z, float in_target_a,
        float in_target_b, float in_target_c, float in_help_x, float in_help_y,
        float in_help_z, float in_help_a, float in_help_b, float in_help_c,
        uint8_t in_speed, enum e_movement_type in_movement_type){
	target_x = in_target_x;
	target_y = in_target_y;
	target_z = in_target_z;
	target_a = in_target_a;
	target_b = in_target_b;
	target_c = in_target_c;
	help_x = in_help_x;
	help_y = in_help_y;
	help_z = in_help_z;
	help_a = in_help_a;
	help_b = in_help_b;
	help_c = in_help_c;
	speed = in_speed;
	movement_type = in_movement_type;
}

void project_editor::cmd_wait::update_command(uint16_t in_time_milisecond)
{
	time_milisecond = in_time_milisecond;
}

void project_editor::cmd_set_pin::update_command(
		enum e_output_pin in_output_pin, bool in_set_pin_high)
{
	output_pin = in_output_pin;
	set_pin_high = in_set_pin_high;
}

void project_editor::insert_command(std::shared_ptr<command> in_cmd){
	if (selected_command >= -1)
	{
		commands.insert(commands.begin() + selected_command, in_cmd);
		draw();
	}
	else
	{
		commands.push_back(in_cmd);
	}
}

void project_editor::remove_command(){
	if (selected_command >= -1)
	{
		commands.erase(commands.begin() + selected_command);
		selected_command = -1;
		draw();
	}
	else
	{
		// TODO tutaj powinien być rzucany wyjątek w przypadku nieudanego usunięcia
	}
}
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
