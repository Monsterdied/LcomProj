#ifndef __RTC_H
#define __RTC_H

#include <lcom/lcf.h>
#include <stdint.h>

// Macros

#define IRQ_RTC 8
#define REGISTER_INPUT 0x70 //Which must be loaded with the address of the RTC register to be accessed
#define REGISTER_OUTPUT 0x71 //Which is used to transfer the data to/from the RTC’s register accessed


//REGISTERS
#define SECONDS 0
#define SECONDS_ALARM 1
#define MINUTES 2
#define MINUTES_ALARM 3
#define HOURS 4
#define HOURS_ALARM 5  
#define DAY_OF_WEEK 6 
#define DAY 7
#define MONTH 8
#define YEAR 9

//REGISTER A
#define REGISTER_A 10
#define UPDATING BIT(7)

//REGISTER B
#define REGISTER_B 11
#define BINARY BIT(2)
#define FORMAT_TIME BIT(1)


//REGISTER C
#define REGISTER_C 12

//REGISTER D
#define REGISTER_D 13
typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week_day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time_display; 



int rtc_subscribe_interrupts(uint8_t *bit_rtc);
int rtc_unsubcribe_interrupts();
int rtc_output(uint8_t cmd , uint8_t *output);
int is_updating_rtc();
void convert_binary(uint8_t *value);
int update_time_display(time_display *time_info);
int getHours();
int getMinutes();
int getSeconds();
#endif
