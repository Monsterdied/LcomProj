#include <lcom/lcf.h>
#pragma once
typedef struct {
  int x,y;             /**< current sprite position */
  int width, height;   /**< sprite dimensions */
  int xspeed, yspeed;  /**< current speeds in the x and y direction */      
} Mouse;
int (mouse_Subscribe)(uint8_t *bit_no);
int (mouse_Unsubscribe)();
int (error_checking_mouse)(uint8_t status_mouse);
void (mouse_ih)();
int (mouse_disable_data_reporting)();
int (mouse_get_status)(uint8_t  *st);
int(mouse_read_buffer)(uint8_t port, uint8_t *output);
void (mouse_ih_new)( Mouse *mouse) ;
