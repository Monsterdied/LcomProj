#include "kbc_controller.h"
char getChar(int scanCode[2]) {
    if (scanCode[0] == 0x1e) {
        return 'A';
    } else if (scanCode[0] == 0x30) {
        return 'B';
    } else if (scanCode[0] == 0x2e) {
        return 'C';
    } else if (scanCode[0] == 0x20) {
        return 'D';
    } else if (scanCode[0] == 0x12) {
        return 'E';
    } else if (scanCode[0] == 0x21) {
        return 'F';
    } else if (scanCode[0] == 0x22) {
        return 'G';
    } else if (scanCode[0] == 0x23) {
        return 'H';
    } else if (scanCode[0] == 0x17) {
        return 'I';
    } else if (scanCode[0] == 0x24) {
        return 'J';
    } else if (scanCode[0] == 0x25) {
        return 'K';
    } else if (scanCode[0] == 0x26) {
        return 'L';
    } else if (scanCode[0] == 0x32) {
        return 'M';
    } else if (scanCode[0] == 0x31) {
        return 'N';
    } else if (scanCode[0] == 0x18) {
        return 'O';
    } else if (scanCode[0] == 0x19) {
        return 'P';
    } else if (scanCode[0] == 0x10) {
        return 'Q';
    } else if (scanCode[0] == 0x13) {
        return 'R';
    } else if (scanCode[0] == 0x1f) {
        return 'S';
    } else if (scanCode[0] == 0x14) {
        return 'T';
    } else if (scanCode[0] == 0x16) {
        return 'U';
    } else if (scanCode[0] == 0x2f) {
        return 'V';
    } else if (scanCode[0] == 0x11) {
        return 'W';
    } else if (scanCode[0] == 0x2d) {
        return 'X';
    } else if (scanCode[0] == 0x15) {
        return 'Y';
    } else if (scanCode[0] == 0x2c) {
        return 'Z';
    }
    return '=';
}
