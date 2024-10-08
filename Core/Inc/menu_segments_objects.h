#ifndef INC_MENU_SEGMENTS_OBJECTS_H
#define INC_MENU_SEGMENTS_OBJECTS_H

#include "bitmap_arrays.h"
#include "display_ssd1963.h"
#include "ff.h"
#include "menu_block.h"
#include "menu_popup.h"
#include "project_editor.h"
#include "project_explorer.h"
#include "sd_card_service.h"
#include "string.h"
#include <menu_segment.h>
#include <stdint.h>

#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"

#define _Open_Sans_Bold_8 &Open_Sans_Bold_8
#define _Open_Sans_Bold_9 &Open_Sans_Bold_9
#define _Open_Sans_Bold_10 &Open_Sans_Bold_10
#define _Open_Sans_Bold_11 &Open_Sans_Bold_11
#define _Open_Sans_Bold_12 &Open_Sans_Bold_12
#define _Open_Sans_Bold_14 &Open_Sans_Bold_14
#define _Open_Sans_Bold_16 &Open_Sans_Bold_16
#define _Open_Sans_Bold_18 &Open_Sans_Bold_18
#define _Open_Sans_Bold_20 &Open_Sans_Bold_20
#define _Open_Sans_Bold_22 &Open_Sans_Bold_22
#define _Open_Sans_Bold_24 &Open_Sans_Bold_24
#define _Open_Sans_Bold_26 &Open_Sans_Bold_26
#define _Open_Sans_Bold_28 &Open_Sans_Bold_28
#define _Open_Sans_Bold_36 &Open_Sans_Bold_36
#define _Open_Sans_Bold_48 &Open_Sans_Bold_48
#define _Open_Sans_Bold_72 &Open_Sans_Bold_72
#define _Open_Sans_Bold_96 &Open_Sans_Bold_96
#define _Open_Sans_Bold_112 &Open_Sans_Bold_112
#define _Open_Sans_Bold_128 &Open_Sans_Bold_128

#define top_menu_button_color 0xD6BA
#define top_menu_text_color BLACK
#define top_menu_background_color 0xD61F
#define top_menu_font const_cast<GFXfont *>(_Open_Sans_Bold_14)

#define left_menu_button_color 0xD6BA
#define left_menu_text_color BLACK
#define left_menu_background_color 0x8C51
#define left_menu_font const_cast<GFXfont *>(_Open_Sans_Bold_14)

#define right_menu_button_color 0xD6BA
#define right_menu_text_color 0x7D3D
#define right_menu_background_color 0x8C51
#define right_menu_font const_cast<GFXfont *>(_Open_Sans_Bold_48)

extern menu_segment main_left_menu;
extern menu_segment main_right_menu;
extern menu_segment project_explorer_menu;
extern menu_segment project_editor_menu;
extern menu_segment straight_mov_menu;
extern menu_segment circular_mov_menu;
extern menu_segment wait_command_menu;
extern menu_segment set_pin_command_menu;
extern menu_segment settings_menu;
extern menu_segment cleer_working_screen;

void init_objects();
void init_main_left_menu();
void init_main_right_menu();
void init_project_explorer_menu();
void init_project_editor_menu();
void init_straight_mov_menu();
void init_circular_mov_menu();
void init_wait_commands_menu();
void init_set_pin_command_menu();
void init_settings_menu();
void init_cleer_working_screen();

// void draw_file_list(int start, int end, bool ascending,
//		enum sort_option option);

#endif
