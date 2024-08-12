/*
 * sd_card_service.h
 *
 *  Created on: Jul 11, 2024
 *      Author: kobie
 */

#ifndef INC_SD_CARD_SERVICE_H_
#define INC_SD_CARD_SERVICE_H_

#include "fatfs.h"
#include "gpio.h"
#include "stdio.h"
#include "string.h"
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

//extern FATFS file_system;
//extern DIR directory;
//extern FILINFO fno;
//extern FIL file;
//extern std::vector<struct file_info> sd_files;
//
//
//
//struct file_info {
//  FSIZE_t size;
//  WORD date;
//  char name[50];
//
//  file_info(FSIZE_t s, WORD d, char* n)
//      : size(s), date(d) {
//	  strcpy(name, n);}
//};
//
//enum sort_option {
//  by_name,
//  by_size,
//  by_date,
//};
//
//
//
//void sort_sd_files(enum sort_option option, bool ascending);
//void get_sd_files();
//int get_sd_files_number();
//bool create_file(char file_name[20]);
//bool unmount_SD_card();
//bool init_SD_card();
//struct file_info get_file_info(int file_number);
//int count_points_in_file(char file_name[20]);

#endif /* INC_SD_CARD_SERVICE_H_ */
