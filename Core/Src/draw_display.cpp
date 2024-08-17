#include <draw_display.h>

menu_segment main_top_menu ;
menu_segment main_left_menu ;
menu_segment main_right_menu ;
menu_segment project_explorer_menu;




void init_objects(){
	TFT_Clear_Screen(clear_screen_color);
	TFT_Draw_Fill_Rectangle(100,0,20,20, top_menu_background_color);
	TFT_Draw_Fill_Rectangle(680,0,20,20, top_menu_background_color);
	init_main_top_menu();
	init_main_left_menu();
	init_main_right_menu();
	init_project_explorer_menu();
}

void init_main_top_menu(){
	//tło
	main_top_menu.add_background_part(std::make_shared<rectangle>(120, 144, 560, 336, clear_screen_color));
	main_top_menu.add_background_part(std::make_shared<rectangle>(120, 0, 560, 144, top_menu_background_color));
	//przyciski na gorze
	main_top_menu.add_part(button(0,132, 9, 70, 41, top_menu_button_color, 20, "SELECT", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(button(1,212, 9, 70, 41, top_menu_button_color, 20,"NEW P.", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(button(2,291, 9, 70, 41, top_menu_button_color, 20,"EDIT P.", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(button(3,371, 9, 81, 41, top_menu_button_color, 20,"DELETE P.", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(button(4,462, 9, 72, 41, top_menu_button_color, 20,"SET T.P.", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(button(5,544, 9, 72, 41, top_menu_button_color, 20,"SET H.P", top_menu_text_color, top_menu_font));
	//przyciski programu
	button btn = button(6,628, 15, 40, 40, top_menu_button_color, 20);//nawigacja góra
	btn.add_part(std::make_shared<triangle>(636, 42, 636 + 23, 42, 647, 22, 0x00FD));
	main_top_menu.add_part(btn);
	btn = button(7,628, 88, 40, 40, top_menu_button_color, 20);//nawigacja dół
	btn.add_part(std::make_shared<triangle>(636, 42 + 59, 636 + 23, 42 + 59, 647, 22 + 40 + 59,0x00FD));
	main_top_menu.add_part(btn);
	main_top_menu.add_part(button(8,211, 68, 61, 21, top_menu_button_color, 10, "P11", top_menu_text_color, top_menu_font));//name
	btn = button(9,211, 109, 61, 21, top_menu_button_color, 10, "OFF", top_menu_text_color, top_menu_font, false);//tool
	btn.add_part(std::make_shared<triangle>(574 - 322, 74 + 41, 573 + 13 - 322, 74 + 41, 580 - 322,74 + 11 + 41, 0x00FD));
	main_top_menu.add_part(btn);
	btn = button(10,362, 68, 61, 21, top_menu_button_color, 10, "Circ", top_menu_text_color, top_menu_font, false);//move
	btn.add_part(std::make_shared<triangle>(574 - 170, 74, 573 + 13 - 170, 74, 580 - 170, 74 + 11,0x00FD));
	main_top_menu.add_part(btn);
	btn = button(11,362, 109, 61, 21, top_menu_button_color, 10, "100%", top_menu_text_color, top_menu_font, false);//speed
	btn.add_part(std::make_shared<triangle>(574 - 170, 74 + 41, 573 + 13 - 170, 74 + 41, 580 - 170,74 + 11 + 41, 0x00FD));
	main_top_menu.add_part(btn);
	btn = button(12,532, 68, 61, 21, top_menu_button_color, 10, "Cont", top_menu_text_color, top_menu_font, false);//type
	btn.add_part(std::make_shared<triangle>(574, 74, 573 + 13, 74, 580, 74 + 11, 0x00FD));
	main_top_menu.add_part(btn);
	main_top_menu.add_part(button(12,532, 109, 61, 21, top_menu_button_color, 10, "YES", top_menu_text_color, top_menu_font));//at target
	//etykiery przycisków programu
	main_top_menu.add_part(std::make_shared<text_field>(155, 67 ,21, "Name:", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(std::make_shared<text_field>(155, 109,21, "Tool:", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(std::make_shared<text_field>(295, 67,21, "Move:", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(std::make_shared<text_field>(295, 109,21, "Speed:", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(std::make_shared<text_field>(446, 67,21, "Type:", top_menu_text_color, top_menu_font));
	main_top_menu.add_part(std::make_shared<text_field>(446, 109,21, "at Target:", top_menu_text_color, top_menu_font));

}

void init_main_left_menu(){
	//szary prostokąt z lewej
	main_left_menu.add_background_part(std::make_shared<rectangle>(0, 0, 20, 20, left_menu_background_color));
	main_left_menu.add_background_part(std::make_shared<rectangle>(0, 460, 20, 20, left_menu_background_color));
	main_left_menu.add_background_part(std::make_shared<rectangle>(0, 0, 120, 480, left_menu_background_color,20));
	int pos_y = 33;
	std::string names[9] = {"JOB NAME","OPEN","CONT. JOB","MANUAL","ENABLE TOOL","RUN JOB","AXIS CONTROL","CONT. MOVEMENT","SETTINGS"};
	//przyciski po lewej
	for (uint8_t i = 0; i < 8; i += 1)
	{
		main_left_menu.add_part(button(i,16, pos_y, 88, 47, left_menu_button_color, 10, names[i], left_menu_text_color, left_menu_font));
		pos_y += 56;
	}

}

void init_main_right_menu(){
	//szary prostokąt z prawej
	main_right_menu.add_background_part(std::make_shared<rectangle>(780, 0, 20, 20, right_menu_background_color));
	main_right_menu.add_background_part(std::make_shared<rectangle>(780, 460, 20, 20, right_menu_background_color));
	main_right_menu.add_background_part(std::make_shared<rectangle>(680, 0, 120, 480, right_menu_background_color,20));
	int pos_y = 9;
	std::string names[6] = {"X","Y","Z","A","B","C"};
	//przyciski po prawej
	for (uint8_t i = 0; i < 6; i += 1)
			{
		main_right_menu.add_part(button(i*2,696, pos_y, 48, 47, right_menu_button_color, 10, "+", 0x4A69, right_menu_font));
		main_right_menu.add_part(button(i*2+1,738, pos_y, 46, 47, right_menu_button_color, 10, "-", 0x4A69, right_menu_font));
		main_right_menu.add_part(std::make_shared<rectangle>(740, pos_y, 2, 47, 0x0000));
		main_right_menu.add_part(std::make_shared<text_field>(696, pos_y, 88, 47,names[i],right_menu_text_color,right_menu_font));
		pos_y += 56;
	}
	//przycisk z rączką
	button btn = button(6,696, pos_y, 88, 47, right_menu_button_color, 10);
	btn.add_part(std::make_shared<rectangle>(740, pos_y, 2, 47, 0x0000));
	btn.add_part(std::make_shared<text_field>(696, pos_y, 88, 47,"+ -", 0x4A69,right_menu_font));
	btn.add_part(std::make_shared<image>(721, 353, hand_icon_x, hand_icon_y, hand_icon, false));
	main_right_menu.add_part(btn);

	btn = button(7,696, 413, 88, 47, right_menu_button_color, 10);
	btn.add_part(std::make_shared<rectangle>(740, 413, 2, 47, 0x0000));
	btn.add_part(std::make_shared<text_field>(696, 413, 88, 47,"+ -", 0x4A69,right_menu_font));
	btn.add_part(std::make_shared<triangle>(732, 417, 732, 417 + 38, 732 + 24, 417 + 19, right_menu_text_color));
	main_right_menu.add_part(btn);
}

void init_project_explorer_menu(){
	project_explorer_menu.add_background_part(std::make_shared<rectangle>(120, 144, 560, 336, clear_screen_color));
	project_explorer_menu.add_background_part(std::make_shared<rectangle>(120, 0, 560, 144, project_explorer_background_color));
	project_explorer_menu.add_part(button(0,152, 52, 100, 40, project_explorer_button_color, 10, "Open file", project_explorer_text_color, project_explorer_font ));
	project_explorer_menu.add_part(button(1,284, 52, 100, 40, project_explorer_button_color, 10, "Create File", project_explorer_text_color, project_explorer_font ));
	project_explorer_menu.add_part(button(2,416, 52, 100, 40, project_explorer_button_color, 10, "Delete File", project_explorer_text_color, project_explorer_font ));
	project_explorer_menu.add_part(button(3,548, 52, 100, 40, project_explorer_button_color, 10, "Sort Files", project_explorer_text_color, project_explorer_font ));
	project_explorer_menu.add_part(std::make_shared<text_field>(project_explorer_start_pos_x, 164, 20,"File name:", project_explorer_text_color, project_explorer_font));
	project_explorer_menu.add_part(std::make_shared<text_field>(project_explorer_start_pos_x+153, 164, 20,"Date:", project_explorer_text_color, project_explorer_font));
	project_explorer_menu.add_part(std::make_shared<text_field>(project_explorer_start_pos_x+153*2, 164, 20,"Size:", project_explorer_text_color, project_explorer_font));

}

//void draw_file_list(int start, int end, bool ascending,
//		enum sort_option option) {
//	int number_of_files = sd_files.size();
//	char buffer2[100];
//
//	if (start > 0) {
//		TFT_Draw_Fill_Round_Rect(142, 158, 40, 40, 20, 0xD6BA);
//		LCD_FillTriangle(150, 185, 150 + 23, 185, 161, 165, 0x00FD);
//	} else
//		TFT_Draw_Fill_Rectangle(142, 158, 40, 40, clear_screen_color);
//	if (end < number_of_files-1) {
//		TFT_Draw_Fill_Round_Rect(142, 425, 40, 40, 20, 0xD6BA);
//		LCD_FillTriangle(150, 432, 150 + 23, 432, 161, 452, 0x00FD);
//	} else
//		TFT_Draw_Fill_Rectangle(142, 425, 40, 40, clear_screen_color);
//
//	sort_sd_files(option, ascending);
//
//	char buffer[20];
//
//	int position = 0;
//	for (int i = 0; i < number_of_files; i++) {
//		if (i >= (start > 0 ? start : 0)
//				&& i <= (end < number_of_files ? end : number_of_files)) {
//			//snprintf(buffer, sizeof(buffer), "%d", sd_files[i].name);
//			LCD_Font_Dynamic(206, 280 + position, _Open_Sans_Bold_14, 1, BLACK,
//					"%10u, %s, %02d-%02d-%04d\n", sd_files[i].size,
//					sd_files[i].name, sd_files[i].date & 0x1F, /* Dzień */
//					(sd_files[i].date >> 5) & 0xF, /* Miesiąc */
//					(sd_files[i].date >> 9) + 1980); /* Rok */
//			//LCD_Font(206, 280+position, buffer, _Open_Sans_Bold_14, 1, BLACK);
//			position += 14;
//		}
//	}
//
//}





