/*
 * objects.h
 *
 *  Created on: Aug 7, 2024
 *      Author: kobie
 */

#ifndef INC_OBJECTS_H_
#define INC_OBJECTS_H_

#include "menu_parts.h"
#include "fatfs.h"
#include <algorithm>
#include "display_ssd1963.h"
#include <sstream>
#include <iomanip>

#define forget_when_hiden true

#define start_pos_x 200
#define start_pos_y 238
#define line_height 25
#define line_space 10
#define num_files_on_page 6
#define file_menu_font const_cast<GFXfont*>(_Open_Sans_Bold_14)

enum tool_status
{
	On, Switch, Off
};

enum movement_type
{
	circ, lin,
};

class menu_segment
{
	std::vector<std::shared_ptr<menu_part>> top_parts;
	std::vector<std::shared_ptr<menu_part>> background_parts;
	std::vector<button> buttons;

public:
	void draw();
	void reduce_vector_size();
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
	int check_pressed(int x, int y);
	void update_text(int id, std::string text);

};

class projects_explorer
{
public:
	enum sort_option
	{
		by_name, by_size, by_date,
	};
private:
	FATFS file_system;
	DIR directory;
	FILINFO fno;
	std::vector<FILINFO> sd_files;
	bool initialized;
	int first_file_to_display = 0;
	int last_file_to_display=0;




	enum sort_option option = by_date;
	bool sort_ascending = false;
	int selected_file = -1;//wartość ujemna oznacza brak wybranego pliku
	button page_up_btn = button(0,140, 158, 40, 40, 0xD6BA, 20);//nawigacja góra
	button page_down_btn = button(1,140, 425, 40, 40, 0xD6BA, 20);//nawigacja dół



	std::string format_date(WORD fdate);
	void get_files();
	void sort_files();
	void update_last_file_to_display();
	bool check_area_pressed(int x, int y, int area_x, int area_y,
				int area_width, int area_height);
	void forget_selected_hiden_file();

public:

	projects_explorer();
	void create_file(std::string name);
	void set_sort_option(enum sort_option in_option, bool in_sort_ascending);
	std::string get_choosen_file();
	void delete_file();
	void handle_pressed(int x, int y);
	void draw();
};

class project_editor
{
public:
	struct circ_point
	{
		enum tool_status tool_status;
		int8_t speed;
		float target_x;
		float target_y;
		float target_z;
		float target_a;
		float target_b;
		float target_c;
		float help_x;
		float help_y;
		float help_z;
		float help_a;
		float help_b;
		float help_c;
	};

	struct lin_point
	{
		enum tool_status tool_status;
		int8_t speed;
		float target_x;
		float target_y;
		float target_z;
		float target_a;
		float target_b;
		float target_c;
	};
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
