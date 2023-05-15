#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
    if (lsb == NULL) {
    return 1;
  }
  *lsb = (uint8_t) val;
  return 0;

}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
    if (msb == NULL) {
    printf("util_get_MSB: invalid pointer to msb\n");
    return 1;
  }

  *msb = (uint8_t) (val >> 8);

  return 0;


}


int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t temp; //Para guardar o valor do temp
  if (sys_inb(port, &temp) != OK) {   
    printf("timer_get_conf: failed to read timer status byte for selected timer\n");
    return 1;
  }
  *value = (uint8_t) temp;    // converte o temp de 32bits para 8bits

  return 0;

}
