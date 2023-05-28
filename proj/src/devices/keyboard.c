#include "keyboard.h"

#define DELAY_US    10000
int scan_code[2];

int static kbc_id = 1;  // static esperimenta 0
extern int i;

int util_sys_inb(int port, uint8_t *value) {
    uint32_t tmp_value = 0x00;
    int ret = sys_inb(port, &tmp_value);
    *value = tmp_value;
    return ret;
}

int kbc_Subscribe(uint8_t *bit_no) {
    *bit_no = kbc_id;
    return sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_id);
}

int kbc_Unsubscribe() {
    return sys_irqrmpolicy(&kbc_id);
}

int kbc_error_checking(uint8_t st) {
    if (st & PARITY_ERROR) {
        return 1;
    }
    if (st & TIMEOUT_ERROR) {
        return 1;
    }
    if (!(st & FULL_OUT_BUFFER)) {
        return 1;
    }
    return 0;
}

int keyboard_get_status(uint8_t *st) {
    return util_sys_inb(KBC_STATUS_REG, st);
}

int keyboard_read_out_buffer(uint8_t *output) {
    return util_sys_inb(KBC_OUT_CMD, output);
}

int writing_command_kbc(int port, uint8_t cmdb) {
    int timeout = 0;
    uint8_t st;

    while (timeout < 2) {
        keyboard_get_status(&st);

        if ((st & FULL_IN_BUFFER) == 0) {
            sys_outb(port, cmdb);
            return 0;
        }

        tickdelay(micros_to_ticks(10000));
        timeout++;
    }

    return 1;
}

int reading_from_kbc(uint8_t *data) {
    int timeout = 0;
    uint8_t st;

    while (timeout < 2) {
        keyboard_get_status(&st);

        if (st & FULL_OUT_BUFFER && !(st & (PARITY_ERROR | TIMEOUT_ERROR | AUX))) {
            keyboard_read_out_buffer(data);
            return 0;
        } else {
            return -1;
        }

        tickdelay(micros_to_ticks(10000));
        timeout++;
    }

    return 0;
}

int kbd_reenable_ints() {
    uint8_t output;

    writing_command_kbc(KBC_IN_CMD, KBC_READ_CMD);
    reading_from_kbc(&output);
    output |= KBC_INT;
    writing_command_kbc(KBC_IN_CMD, KBC_WRITE_CMD);
    writing_command_kbc(KBC_OUT_CMD, output);

    return 0;
}

void kbc_ih() {
    uint8_t st;
    util_sys_inb(KBC_STATUS_REG, &st);
    if (kbc_error_checking(st) == OK) {
        uint8_t output;
        util_sys_inb(KBC_OUT_BUFFER, &output);
        scan_code[i] = output;
    }
}
