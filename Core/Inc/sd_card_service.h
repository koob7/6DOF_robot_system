/*
 * sd_card_service.h
 *
 *  Created on: Jul 11, 2024
 *      Author: kobie
 */

#ifndef INC_SD_CARD_SERVICE_H_
#define INC_SD_CARD_SERVICE_H_

#include "string.h"
#include "stdio.h"
#include "fatfs.h"
#include <stdbool.h>
#include "draw_display.h"
#include "gpio.h"

extern FATFS file_system;
extern DIR directory;
extern FILINFO fno;
extern FIL file;

enum tool_status{
	On,
	Switch,
	Off
};

enum movement_type{
	circ,
	lin,
};

struct file_info{
	FSIZE_t	size;
	WORD date;
	char name[50];
};

struct circ_point{
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

struct lin_point{
	enum tool_status tool_status;
	int8_t speed;
	float target_x;
	float target_y;
	float target_z;
	float target_a;
	float target_b;
	float target_c;
};

bool create_file(char file_name[20]);
bool unmount_SD_card();
bool init_SD_card();
int count_files ();
struct file_info get_file_info(int file_number);
int count_points_in_file(char file_name[20]);


#endif /* INC_SD_CARD_SERVICE_H_ */
