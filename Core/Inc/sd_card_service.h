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
#include "gpio.h"
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>


extern FATFS file_system;
extern DIR directory;
extern FILINFO fno;
extern FIL file;
extern std::vector<struct file_info2> sd_files;

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

struct file_info2{
	FSIZE_t	size;
	WORD date;
	std::string name;

    file_info2(FSIZE_t s, WORD d, const std::string& n)
        : size(s), date(d), name(n) {}
};

enum sort_option{
	by_name,
	by_size,
	by_date,
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

void sort_sd_files(enum sort_option option, bool ascending);
void get_sd_files();
int get_sd_files_number();
bool create_file(char file_name[20]);
bool unmount_SD_card();
bool init_SD_card();
struct file_info2 get_file_info(int file_number);
int count_points_in_file(char file_name[20]);


#endif /* INC_SD_CARD_SERVICE_H_ */
