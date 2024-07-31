#include <draw_display.h>

#define LCD_Font_Dynamic(x, y, font, size, color, format, ...) do { \
	int needed = snprintf(NULL, 0, format, __VA_ARGS__) + 1; \
    char buffer[needed]; \
    snprintf(buffer, sizeof(buffer), format, __VA_ARGS__); \
    LCD_Font(x, y, buffer, font, size, color); \
} while(0)

void draw_file_list(int start, int end, bool ascending,
		enum sort_option option) {
	int number_of_files = sd_files.size();
	char buffer2[100];

	if (start > 0) {
		TFT_Draw_Fill_Round_Rect(142, 158, 40, 40, 20, 0xD6BA);
		LCD_FillTriangle(150, 185, 150 + 23, 185, 161, 165, 0x00FD);
	} else
		TFT_Draw_Fill_Rectangle(142, 158, 40, 40, defined_background_color);
	if (end < number_of_files-1) {
		TFT_Draw_Fill_Round_Rect(142, 425, 40, 40, 20, 0xD6BA);
		LCD_FillTriangle(150, 432, 150 + 23, 432, 161, 452, 0x00FD);
	} else
		TFT_Draw_Fill_Rectangle(142, 425, 40, 40, defined_background_color);

	sort_sd_files(option, ascending);

	char buffer[20];

	int position = 0;
	for (int i = 0; i < number_of_files; i++) {
		if (i >= (start > 0 ? start : 0)
				&& i <= (end < number_of_files ? end : number_of_files)) {
			//snprintf(buffer, sizeof(buffer), "%d", sd_files[i].name);
			LCD_Font_Dynamic(206, 280 + position, _Open_Sans_Bold_14, 1, BLACK,
					"%10u, %s, %02d-%02d-%04d\n", sd_files[i].size,
					sd_files[i].name, sd_files[i].date & 0x1F, /* Dzień */
					(sd_files[i].date >> 5) & 0xF, /* Miesiąc */
					(sd_files[i].date >> 9) + 1980); /* Rok */
			//LCD_Font(206, 280+position, buffer, _Open_Sans_Bold_14, 1, BLACK);
			position += 14;
		}
	}

}


void draw_file_menu() {
	TFT_Draw_Fill_Rectangle(120, 144, 560, 336, defined_background_color);
	TFT_Draw_Fill_Round_Rect(206, 156, 119, 41, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(349, 156, 119, 41, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(492, 156, 119, 41, 10, 0xD6BA);
	LCD_centered_Font(206, 156 + 21, 119, "Open file", _Open_Sans_Bold_14, 1,
			BLACK);
	LCD_centered_Font(349, 156 + 21, 119, "Create File", _Open_Sans_Bold_14, 1,
			BLACK);
	LCD_centered_Font(492, 156 + 21, 119, "Delete File", _Open_Sans_Bold_14, 1,
			BLACK);
	LCD_Font(206, 206 + 21, "File name:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(472, 206 + 21, "Date:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(590, 206 + 21, "Size:", _Open_Sans_Bold_14, 1, BLACK);

}

void draw_main_menu() {
	TFT_Clear_Screen(defined_background_color);
	draw_top_panel();
	draw_right_panel();
	draw_left_panel();
}
void draw_right_panel() {
	int pos_y;
	TFT_Draw_Fill_Rectangle(780, 0, 20, 20, 0x8C51); //szary prostokąt z prawej
	TFT_Draw_Fill_Rectangle(780, 460, 20, 20, 0x8C51);
	TFT_Draw_Fill_Round_Rect(680, 0, 120, 480, 20, 0x8C51);
	pos_y = 9;
	for (uint8_t i = 0; i < 7; i += 1) //przyciski po prawej
			{
		TFT_Draw_Fill_Round_Rect(696, pos_y, 88, 47, 10, 0xD6BA);
		TFT_Draw_Fill_Rectangle(740, pos_y, 2, 47, 0x0000);
		LCD_centered_Font(696, pos_y + 24, 88, "+   -", _Open_Sans_Bold_48, 1,
				0x4A69);
		pos_y += 56;
	}
	TFT_Draw_Fill_Round_Rect(696, 413, 88, 47, 10, 0xD6BA);
	TFT_Draw_Fill_Rectangle(740, 413, 2, 47, 0x0000);
	LCD_centered_Font(696, 413 + 24, 88, "+   -", _Open_Sans_Bold_48, 1,
			0x4A69);
	LCD_centered_Font(696, 9 + 25, 88, "X", _Open_Sans_Bold_48, 1, 0x7D3D); //literki po prawej
	LCD_centered_Font(696, 65 + 25, 88, "Y", _Open_Sans_Bold_48, 1, 0x7D3D);
	LCD_centered_Font(696, 121 + 25, 88, "Z", _Open_Sans_Bold_48, 1, 0x7D3D);
	LCD_centered_Font(696, 177 + 25, 88, "A", _Open_Sans_Bold_48, 1, 0x7D3D);
	LCD_centered_Font(696, 233 + 25, 88, "B", _Open_Sans_Bold_48, 1, 0x7D3D);
	LCD_centered_Font(696, 289 + 25, 88, "C", _Open_Sans_Bold_48, 1, 0x7D3D);
	LCD_FillTriangle(732, 417, 732, 417 + 38, 732 + 24, 417 + 19, 0x7D3D);
	TFT_Draw_Bitmap_Without_Background(721, 353, hand_icon_x, hand_icon_y,
			hand_icon);
}

void draw_left_panel() {
	int pos_y;
	TFT_Draw_Fill_Rectangle(0, 0, 20, 20, 0x8C51); //szary prostokąt z lewej
	TFT_Draw_Fill_Rectangle(0, 460, 20, 20, 0x8C51);
	TFT_Draw_Fill_Round_Rect(0, 0, 120, 480, 20, 0x8C51);
	pos_y = 33;
	for (uint8_t i = 0; i < 8; i += 1) //przyciski po lewej
			{
		TFT_Draw_Fill_Round_Rect(16, pos_y, 88, 47, 10, 0xD6BA);
		pos_y += 56;
	}
	LCD_centered_Font(0, 0 + 16, 120, "JOB NAME", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(16, 33 + 24, 88, "OPEN", _Open_Sans_Bold_14, 1, 0x7D3D); //literki po lewej
	LCD_centered_Font(16, 89 + 24, 88, "CONT. JOB", _Open_Sans_Bold_14, 1,
			0x7D3D);
	LCD_centered_Font(16, 145 + 24, 88, "MANUAL", _Open_Sans_Bold_14, 1,
			0x7D3D);
	LCD_centered_Font(16, 201 + 14, 88, "ENABLE\nTOOL", _Open_Sans_Bold_14, 1,
			0x7D3D);
	LCD_centered_Font(16, 257 + 24, 88, "RUN JOB", _Open_Sans_Bold_14, 1,
			0x7D3D);
	LCD_centered_Font(16, 313 + 14, 88, "AXIS\nCONTROL", _Open_Sans_Bold_14, 1,
			0x7D3D);
	LCD_centered_Font(16, 369 + 14, 88, "CONT.\nMOVEMENT", _Open_Sans_Bold_14,
			1, 0x7D3D);
	LCD_centered_Font(16, 425 + 24, 88, "SETTINGS", _Open_Sans_Bold_14, 1,
			0x7D3D);
}

void draw_top_panel() {
	TFT_Draw_Fill_Rectangle(100, 0, 600, 144, 0xD61F); //niebieska ramka
	TFT_Draw_Fill_Round_Rect(132, 9, 70, 41, 20, 0xD6BA); //przyciski na gorze
	TFT_Draw_Fill_Round_Rect(212, 9, 70, 41, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(291, 9, 70, 41, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(371, 9, 81, 41, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(462, 9, 72, 41, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(544, 9, 72, 41, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(628, 15, 40, 40, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(628, 88, 40, 40, 20, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(211, 68, 61, 21, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(211, 109, 61, 21, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(362, 68, 61, 21, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(362, 109, 61, 21, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(532, 68, 61, 21, 10, 0xD6BA);
	TFT_Draw_Fill_Round_Rect(532, 109, 61, 21, 10, 0xD6BA);
	LCD_centered_Font(132, 9 + 22, 70, "SELECT", _Open_Sans_Bold_14, 1, BLACK); //opisy przyciskow
	LCD_centered_Font(212, 9 + 22, 70, "NEW P.", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(291, 9 + 22, 70, "EDIT P.", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(371, 9 + 22, "DELETE P.", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(462, 9 + 22, 70, "SET T.P.", _Open_Sans_Bold_14, 1,
			BLACK);
	LCD_centered_Font(544, 9 + 22, 70, "SET H.P", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(155, 67 + 11, "Name:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(155, 109 + 11, "Tool:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(295, 67 + 11, "Move:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(295, 109 + 11, "Speed:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(446, 67 + 11, "Type:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_Font(446, 109 + 11, "at Target:", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(211, 68 + 11, 61, "P11", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(211, 109 + 11, 41, "OFF", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(362, 68 + 11, 41, "Circ", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(362, 109 + 11, 41, "100%", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(532, 68 + 11, 41, "Cont", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(532, 109 + 11, 61, "YES", _Open_Sans_Bold_14, 1, BLACK);
	LCD_FillTriangle(636, 42, 636 + 23, 42, 647, 22, 0x00FD);
	LCD_FillTriangle(636, 42 + 59, 636 + 23, 42 + 59, 647, 22 + 40 + 59,
			0x00FD);
	LCD_FillTriangle(574, 74, 573 + 13, 74, 580, 74 + 11, 0x00FD);
	LCD_FillTriangle(574 - 170, 74, 573 + 13 - 170, 74, 580 - 170, 74 + 11,
			0x00FD);
	LCD_FillTriangle(574 - 170, 74 + 41, 573 + 13 - 170, 74 + 41, 580 - 170,
			74 + 11 + 41, 0x00FD);
	LCD_FillTriangle(574 - 322, 74 + 41, 573 + 13 - 322, 74 + 41, 580 - 322,
			74 + 11 + 41, 0x00FD);
}
