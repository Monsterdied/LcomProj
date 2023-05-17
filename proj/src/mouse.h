#include <lcom/lcf.h>

typedef struct {
  int x,y;             /**< current sprite position */
  int width, height;   /**< sprite dimensions */
  int xspeed, yspeed;  /**< current speeds in the x and y direction */
  char *map;           /**< the sprite pixmap (use read_xpm()) */
} Mouse;
int (mouse_Subscribe)(uint8_t *bit_no);
int (mouse_Unsubscribe)();
int (error_checking_mouse)(uint8_t status_mouse);
void (mouse_ih)();
int (mouse_disable_data_reporting)();
int (mouse_get_status)(uint8_t  *st);
int(mouse_read_buffer)(uint8_t port, uint8_t *output);
void (mouse_ih_new)( Mouse *mouse , const vbe_mode_info_t vmi) ;
