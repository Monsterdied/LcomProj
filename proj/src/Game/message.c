#include "message.h"
#include "models/models.h"
#include "draw/draw.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

Mouse mouse;
extern time_display time_info;

message msg;
int ipc_status;
int r;
int timer_interrupts_per_frame;
int timer_rtc_interrupts_counter;
int timer_interrupts_counter;
uint8_t irq_set_timer;
uint32_t irq_set_mouse;
uint32_t irq_set_kbc;
uint8_t bit_no_mouse;
uint8_t bit_no_kbc;
uint8_t bit_no_timer;
extern int fr_rate;
extern int scan_code[2];
int i;

bool is_selected = false;

void (mouse_api_message)(enum GameState* state) {
    if (mouse.x > 150 && mouse.x < 300 && mouse.y > 400 && mouse.y < 420) {
        is_selected = true;
        if (mouse.left_click) {
            *state = MENU;
        }
    } else {
        is_selected = false;
    }
}

int (get_started_on_message)() {
    mouse.x = 600;
    mouse.y = 300;
    mouse.height = 44;
    mouse.width = 44;

    if (map_vram(0x115)) {
        return 1;
    }
    if (vg_init_new(0x115) != OK) {
        return 1;
    }
    if (kbc_Subscribe(&bit_no_kbc) != OK) {
        return 1;
    }
    if (timer_subscribe_int(&bit_no_timer) != OK) {
        return 1;
    }
    if (mouse_Subscribe(&bit_no_mouse) != OK) {
        return 1;
    }

    i = 0;
    irq_set_timer = BIT(bit_no_timer);
    irq_set_kbc = BIT(bit_no_kbc);
    irq_set_mouse = BIT(bit_no_mouse);
    timer_interrupts_per_frame = 60 / fr_rate;
    timer_interrupts_counter = 0;
    timer_rtc_interrupts_counter = 0;
    return 0;
}

void (Message)(enum GameState* state, struct ArenaModel model) {
    enum GameState oldstate = *state;
    get_started_on_message();

    while (*state == oldstate) {
        if (timer_interrupts_counter % timer_interrupts_per_frame == 0) {
            timer_interrupts_counter = 1;
            draw_message(model, *state, mouse, is_selected);
            if (vg_update() != OK) {
                printf("Screen didn't update");
            }
        }
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set_kbc) { /* subscribed interrupt */
                        kbc_ih(); // calls the kbc_ih()
                        if (scan_code[i] == TWO_BYTES) {   // if the scan code is 2 bytes, increment i and continue to read the next byte (the second one in this case)
                            i++;
                            continue;
                        }
                        // Prints the input scancode.
                        i = 0;
                        if (scan_code[0] == BREAK_ESC) {
                            *state = EXIT;
                        }
                        if (is_selected && scan_code[0] == KBC_MAKE_CODE_ENTER) {
                            *state = MENU;
                        }
                        // Read the first byte again
                    }

                    if (msg.m_notify.interrupts & irq_set_timer) {
                        timer_interrupts_counter++;
                        timer_rtc_interrupts_counter++;
                        if (timer_rtc_interrupts_counter % 60 == 0) {
                            timer_rtc_interrupts_counter = 1;
                            update_time_display(&time_info);
                        }
                    }

                    if (msg.m_notify.interrupts & irq_set_mouse) {
                        mouse_ih_new(&mouse);
                        mouse_api_message(state);
                    }

                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }

    mouse_Unsubscribe();
    kbc_Unsubscribe();
    timer_unsubscribe_int();
    vg_exit();
}
