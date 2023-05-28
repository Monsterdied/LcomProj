#ifndef UNTITLED10_KBC_CONTROLLER_H
#define UNTITLED10_KBC_CONTROLLER_H
#pragma once
/**
 * @brief Read scancode
 *
 * it reads the scancode and return a char with the key pressed if it is a normal letter not number nor special char
 *
 * @param scanCode The scancode from the keyboard.
 * @return A char with the key pressed if it is a normal letter not number nor special char
 */
char getChar(int scanCode[2]);

#endif //UNTITLED10_KBC_CONTROLLER_H
