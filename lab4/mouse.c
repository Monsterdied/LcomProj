#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include <stdint.h>

int static hookid=0;
struct packet mouse_packet;
int mouse_byte_number = 0;
bool flag = true;


int (mouse_subscribe)(uint8_t *bitno){
    hookid=*bitno;
    return sys_irqsetpolicy(IRQ_MOUSE,IRQ_REENABLE | IRQ_EXCLUSIVE, &hookid);
}
int (mouse_unsubscribe)(){
    return sys_irqrmpolicy(&hookid);
}
int (error_checking_mouse)(uint8_t status_mouse){
    if(status_mouse & X_OVERFLOW){
        return 1;
    }
    if(status_mouse & Y_OVERFLOW){
        return 1;
    }
    return 0;
}
int (get_stat_mouse)(uint8_t *stat){
    if(util_sys_inb(KBC_stat_reg,stat)){
        printf("error on (get_stat_mouse)");
        return 1;
    }
    return 0;
}

int(mouse_read_buffer)(uint8_t port, uint8_t *output) {

  uint8_t st;
    get_stat_mouse(&st);

    if ((st & ( OBF| STATUS_AUX)) && !((st & (STATUS_PARITY| STATUS_TIMEOUT)))) {
      util_sys_inb(port, output);
      return 0;
    }


  return 1;
}
int (mouse_write_cmd)(uint8_t input){
    uint8_t st;
    get_stat_mouse(&st);
    if(!(st & IBF)) sys_outb( KBC_write_port ,WRITE_BYTE_TO_MOUSE);
    

    get_stat_mouse(&st);


    if (!(st & IBF)) sys_outb(KBC_args, input);
    


    uint8_t ack_byte;
    util_sys_inb(OUT_BUF, &ack_byte);

    if (ack_byte == ACK) return 0;
        return 1;
}

int (mouse_disable_data_reporting)(){
    if(mouse_write_cmd(DISABLE_DATA_REPORTING )!=0)
        return 1;
    
    return 0;
}
void (mouse_ih)(){
    uint8_t  st; 
    if(get_stat_mouse(&st)!=0)
        printf("error get status mouse ih");
    
    if(!(st & OBF)||(st & (STATUS_PARITY | STATUS_TIMEOUT))){
        printf("error on mouse_ih");
        return ;
    }
    uint8_t output=0;
    mouse_read_buffer(OUT_BUF,&output);
    mouse_packet.bytes[mouse_byte_number]=output;
    //printf("%d      %d         %d\n",mouse_byte_number,mouse_packet.bytes[mouse_byte_number] ,output);

    if((output & FIRST_BYTE) && mouse_byte_number ==0){
        flag=false;
        mouse_packet.lb =output & LMOUSE_BUTTON;
        mouse_packet.rb=output & RMOUSE_BUTTON;
        mouse_packet.mb = output & MMOUSE_BUTTON;
        mouse_packet.x_ov=output & X_OVERFLOW ;
        mouse_packet.y_ov=output & Y_OVERFLOW;
    }
    else if(mouse_byte_number ==1){
        mouse_packet.delta_x = output;
        if(mouse_packet.bytes[0] & MOUSE_MSB_X) mouse_packet.delta_x |= 0xFF00;
    }
    else if(mouse_byte_number==2){
        mouse_packet.delta_y=output;
        if(mouse_packet.bytes[0] & MOUSE_MSB_Y) mouse_packet.delta_y |= 0xFF00;
        mouse_byte_number = -1;
        flag = true;

    }

    
    mouse_byte_number++;
    
}



