#include "rtc.h"

int hook_id_rtc = 5;

int (rtc_subscribe_interrupts)(uint8_t *bit_rtc) {
    *bit_rtc = hook_id_rtc;
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &hook_id_rtc);
}

int (rtc_unsubcribe_interrupts)() {
    return sys_irqrmpolicy(&hook_id_rtc);
}

int (rtc_output)(uint8_t cmd, uint8_t *output) {
    if (sys_outb(REGISTER_INPUT, cmd) != 0) {
        printf("sys_outb failed.");
        return 1;
    }

    if (util_sys_inb(REGISTER_OUTPUT, output) != 0) {
        printf("util_sys_inb failed.");
        return 1;
    }
    return 0;
}

int (is_updating_rtc)() {
    uint8_t status_updating;
    if (rtc_output(REGISTER_A, &status_updating) != 0) {
        printf("rtc_output failed.");
        return 1;
    }
    return status_updating & UPDATING;
}

void (convert_binary)(uint8_t *value) {
    *value = ((*value >> 4) * 10) + (*value & 0xF);
}

int (update_time_display)(time_display *time_info) {
    if (is_updating_rtc() != 0) {
        printf("Values are being updated, so it can't be accessed.");
        return 1;
    }
    uint8_t output;

    if (rtc_output(SECONDS, &output) != 0) {
        printf("Failed to access SECONDS register.");
        return 1;
    }
    convert_binary(&output);
    time_info->seconds = output;

    if (rtc_output(MINUTES, &output) != 0) {
        printf("Failed to access MINUTES register.");
        return 1;
    }
    convert_binary(&output);
    time_info->minutes = output;

    if (rtc_output(HOURS, &output) != 0) {
        printf("Failed to access HOURS register.");
        return 1;
    }
    convert_binary(&output);
    time_info->hours = output;

    return 0;
}

int (getHours)(time_display time_info) {
    return time_info.hours;
}

int (getMinutes)(time_display time_info) {
    return time_info.minutes;
}

int (getSeconds)(time_display time_info) {
    return time_info.seconds;
}
