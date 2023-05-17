#include "keyboard.h"


#define DELAY_US    10000
int scan_code[2];

int static kbc_id = 1;//static esperimenta 0
extern int i ;


int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t tmp_value = 0x00;
  int ret = sys_inb(port , &tmp_value);
  *value = tmp_value;
  return ret;
}


int (kbc_Subscribe)(uint8_t *bit_no){
    *bit_no = kbc_id;
    return sys_irqsetpolicy(IRQ_KEYBOARD,IRQ_REENABLE|IRQ_EXCLUSIVE , &kbc_id);
}
int (kbc_Unsubscribe)(){
    return sys_irqrmpolicy(&kbc_id);
}
int (kbc_error_checking)(uint8_t st){
    if(st & PARITY_ERROR){
        return 1;
    }
    if(st & TIMEOUT_ERROR){
        return 1;
    }
    //PROB ERRO AQUI
    if(!(st & FULL_OUT_BUFFER)){
        return 1;
    }/*
    if(st & FULL_IN_BUFFER){
        return printf("Full in buffer");
    }*/
    return 0;
}

int(keyboard_get_status)(uint8_t *st){
    return util_sys_inb(KBC_STATUS_REG ,st);
}

int(keyboard_read_out_buffer)(uint8_t *output){
    return util_sys_inb(KBC_OUT_CMD,output);
}

int (writing_command_kbc)(int port ,uint8_t cmdb){
  int timeout = 0;
  uint8_t st;

  while (timeout < 2) {  // used to retry writing a command byte to the keyboard controller if the input buffer is full.
                        /*When the input buffer is full, any further write attempts will be blocked until the buffer is emptied by reading the data byte. 
                        This can cause a delay in executing the desired operation and potentially lead to data loss if the command byte is not written properly.*/
    
    keyboard_get_status(&st); //guarda o status

    if((st & FULL_IN_BUFFER)==0){  //Check if the input buffer is empty by checking if the FULL_IN_BUFFER bit is not set in the st variable. If the input buffer is empty, continue to the next line.
        sys_outb(port,cmdb);        //escrever o cmdb no port
        return 0;
    }

    tickdelay(micros_to_ticks(10000)); //delays for 10000 ms
    timeout++;
  }

    return 1;
}

int (reading_from_kbc)(uint8_t *data){
 int timeout = 0;
  uint8_t st;

  while (timeout < 2) {  // used to retry writing a command byte to the keyboard controller if the input buffer is full.
                        /*When the input buffer is full, any further write attempts will be blocked until the buffer is emptied by reading the data byte. 
                        This can cause a delay in executing the desired operation and potentially lead to data loss if the command byte is not written properly.*/
    
    keyboard_get_status(&st); //guarda o status do byte

    if (st & FULL_OUT_BUFFER && !(st & (PARITY_ERROR | TIMEOUT_ERROR | AUX))) { //checks if the output buffer is full and there are no transmission errors, indicating that a command byte is available to be read from the output buffer.
                                        //this creates a byte with these specific bits set to 0.
      keyboard_read_out_buffer(data); //read the data from the output buffer and store it in data

      return 0;
    
    } else return -1;

    tickdelay(micros_to_ticks(10000));  
    timeout++;

  }
  
  return 0;

}

int(kbd_reenable_ints)() {

        uint8_t output;

        writing_command_kbc(KBC_IN_CMD,KBC_READ_CMD); //Write the read command (0x20) to the command port (0x64) of the keyboard controller to read the status byte.

        reading_from_kbc(&output); //Read the status byte from the data port (0x60) of the keyboard controller and store it in the output variable.

        output |= KBC_INT; //Set the interrupt enable bit of the output variable to 1 by performing a bitwise OR operation with the constant KBC_INT.

        writing_command_kbc(KBC_IN_CMD,KBC_WRITE_CMD); // Write the write command (0x60) to the command port of the keyboard controller to prepare for writing the modified status byte.

        writing_command_kbc(KBC_OUT_CMD,output); // Write the modified status byte to the data port of the keyboard controller.

        return 0;
}
void (kbc_ih)() {
  uint8_t st;
  util_sys_inb(KBC_STATUS_REG ,&st );
  if(kbc_error_checking(st)==OK){
    uint8_t output;
    util_sys_inb(KBC_OUT_BUFFER,&output);
    scan_code[i] = output;
  }
}


