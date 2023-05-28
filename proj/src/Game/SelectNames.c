#include "SelectNames.h"

Mouse mouse;
extern time_display time_info;
int number_of_player;
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

void (kbc_api_select_names)(struct ArenaModel* model, enum GameState* state) {
    if (scan_code[0] == KBC_MAKE_CODE_ENTER && model->players[number_of_player].nameSize > 0) {
        model->players[number_of_player].name[model->players[number_of_player].nameSize] = '\0';
        number_of_player += 1;
        if (number_of_player == 2) {
            *state = GAME;
            return;
        }
    } else if (scan_code[0] == 0x0e) {
        if (model->players[number_of_player].nameSize > 0) {
            model->players[number_of_player].nameSize--;
        }
    }
    char c = getChar(scan_code);
    if (c != '=') {
        if (model->players[number_of_player].nameSize < 10) {
            model->players[number_of_player].name[model->players[number_of_player].nameSize] = c;
            model->players[number_of_player].nameSize++;
        }
    }
}

int (get_started_select_names)() {
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

struct ArenaModel (SelectNames)(enum GameState* state, struct ArenaModel* model) {
    number_of_player = 0;
    if (get_started_select_names() != OK) {
        printf("Error in get_started_select_names");
    }

    while (*state == SELECTNAMES) {
        if (timer_interrupts_counter % timer_interrupts_per_frame == 0) {
            timer_interrupts_counter = 1;
            draw_select_names(number_of_player, *model, mouse);
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
                        kbc_api_select_names(model, state);

                        i = 0;
                        if (scan_code[0] == BREAK_ESC) {
                            *state = EXIT;
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
                        /*
                        mouse_api_menu();*/
                        mouse_ih_new(&mouse);
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
    return *model;
}
