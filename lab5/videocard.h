#ifndef _VIDEOCARD_H_
#define _VIDEOCARD_H_

void (videographics_init)(uint16_t mode);
int (mappVm)(uint16_t mode);

void (vg_draw_Pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint32_t (R)(uint32_t first);
uint32_t (B)(uint32_t first);
uint32_t (G)(uint32_t first);

#endif /* _VIDEOCARD_H_ */
