/*
 * sd_card_service.c
 *
 *  Created on: Jul 11, 2024
 *      Author: kobie
 */

#include "sd_card_service.h"


DIR directory;
FILINFO fno;
FATFS file_system;
FIL file;

int count_points_in_file(char file_name[20]){
	int counter=0;
	char line[100];
	char *word;
	if (f_open(&file, file_name, FA_READ)== FR_OK) {
		while (f_gets(line, sizeof(line), &file)) {
			word = strtok(line, " \t\r\n");
			if (strstr(word, "trzecia") != NULL){
				counter++;
				LCD_Font(450, 250+counter*14, word, _Open_Sans_Bold_14, 1, BLACK);
			}

        }
        f_close(&file); // Close the file after reading
}
	return counter;
}

bool create_file(char file_name[20]){
//	if(f_open(&file, file_name, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK){
//		_close(&file);
//		return true;
//	}
//	else return false;
	return false;
}

bool init_SD_card(){
	if (f_mount(&file_system, "/", 1) == FR_OK) return true;
	else return false;
}

bool unmount_SD_card(){
	      	if ( f_mount(NULL, "/", 1)== FR_OK) return true;
	    	else return false;
}

int count_files (){
  int number_of_files=0;
  if (f_opendir (&directory,"/") == FR_OK) {
	  for (;;) {
		  if (f_readdir(&directory, &fno)!=FR_OK || fno.fname[0] == 0) break;  /* Error or end of dir */
		  if ((strstr(fno.fname, ".txt") != NULL)) {            /* Directory */
			number_of_files++;
		  }
	  }
	  f_closedir(&directory);
  }
  return number_of_files;
}

struct file_info get_file_info(int file_number){
  int counter=0;
  struct file_info info;
  if (f_opendir (&directory,"/")== FR_OK) {
	  for (;;) {
		  if (f_readdir(&directory, &fno) != FR_OK|| fno.fname[0] == 0) break;  /* Error or end of dir */
		  if ((strstr(fno.fname, ".txt") != NULL)) {
			  counter++;
			  if(counter == file_number){
				  info.date = fno.fdate;
				  strcpy(info.name, fno.fname);
				  info.size = fno.fsize;
			  }
		  }

	  }
	  f_closedir(&directory);
  }
  return info;
}



