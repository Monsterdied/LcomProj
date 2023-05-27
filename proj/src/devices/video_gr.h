#pragma once
#include <machine/int86.h>
#include <stdint.h>
#include <lcom/lcf.h>
 #define CHROMA_KEY_GREEN_888 0x00b140
int (map_vram)(uint16_t mode);
int (drawXpm)(xpm_map_t xpm,int x , int y);
int (drawXpm8_8_8)(xpm_image_t img,int x , int y);
int (vg_init_new)(uint16_t mode);
int (R)(uint32_t color);
int (G)(uint32_t color);
int (B)(uint32_t color);
int (vg_update)();
int (draw_pixel)(uint16_t x , uint16_t y , uint32_t color);
int (vg_draw_Character)(char c,xpm_image_t img,int x , int y,uint32_t colorChosen);
int (vg_draw_rectangle_background)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
