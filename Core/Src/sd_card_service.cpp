/*
 * sd_card_service.c
 *
 *  Created on: Jul 11, 2024
 *      Author: kobie
 */

#include "sd_card_service.h"

//DIR directory;
//FILINFO fno;
//FATFS file_system;
//FIL file;
//std::vector<struct file_info> sd_files;
//
//bool create_file(char file_name[20]) {
//	if (f_open(&file, file_name, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
//		f_close(&file);
//		return true;
//	} else
//		return false;
//}
//
//bool init_SD_card() {
//	if (f_mount(&file_system, "/", 1) == FR_OK) {
//		get_sd_files();
//		return true;
//	} else
//		return false;
//}
//
//bool unmount_SD_card() {
//	if (f_mount(NULL, "/", 1) == FR_OK)
//		return true;
//	else
//		return false;
//}
//
//void get_sd_files() {
//	sd_files.clear();
//	char name[50];
//	std::string filename;
//	if (f_opendir(&directory, "/") == FR_OK) {
//		for (;;) {
//			if (f_readdir(&directory, &fno) != FR_OK || fno.fname[0] == 0)
//				break;
//			strcpy(name, fno.fname);
//			filename.assign(name);
//			if (filename.find(".txt") != std::string::npos) {
//				sd_files.push_back(file_info(fno.fsize, fno.fdate, name));
//			}
//		}
//	}
//}
//
//int get_sd_files_number() {
//	return sd_files.size();
//}
//
//void sort_sd_files(enum sort_option option, bool ascending) {
//	auto compare = [option, ascending](const file_info &a, const file_info &b) {
//		switch (option) {
//		case by_name:
//			return ascending ? a.name < b.name : a.name > b.name;
//		case by_size:
//			return ascending ? a.size < b.size : a.size > b.size;
//		case by_date:
//			return ascending ? a.date < b.date : a.date > b.date;
//		default:
//			return false;
//		}
//	};
//
//	std::sort(sd_files.begin(), sd_files.end(), compare);
//}
//
//struct file_info get_file_info(int file_number) {
//	return (sd_files[file_number]);
//}
