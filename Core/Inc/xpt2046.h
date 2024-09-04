#ifndef INC_XPT2046_H_
#define INC__XPT2046_H_

#include "main.h"

extern volatile uint16_t touch_x;
extern volatile uint16_t touch_y;

#define XPT2046_ACCURACY 1
#define XPT2046_REVERSED 0
#define XPT2046_MIRROR_X 0
#define XPT2046_MIRROR_Y 0

#define RAW_MIN_X 4300 // 260//270//130
#define RAW_MAX_X 8064 // 3770//3820//3936
#define OUT_MIN_X 0
#define OUT_MAX_X 800

#define RAW_MIN_Y 4500 // 470//480//310
#define RAW_MAX_Y 7900 // 3790//3780//3910
#define OUT_MIN_Y 0
#define OUT_MAX_Y 480

#define XPT2046_SPI hspi2
#define XPT2046_NSS_SOFT 1
#define XPT2046_NSS_PORT GPIOB
#define XPT2046_NSS_PIN GPIO_PIN_12

#define XPT2046_ADDR_I 0x83       // 0x80
#define XPT2046_ADDR_X 0b11010011 // 0xD1 		0xD0
#define XPT2046_ADDR_Y 0b10010011 // 0x91 	0x90

void XPT2046_Init(void);
uint16_t getRaw(uint8_t address);
uint16_t getX(void);
uint16_t getY(void);

#endif /* _XPT2046_H_ */
