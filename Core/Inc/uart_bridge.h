// uart_bridge.h

#ifndef UART_BRIDGE_H
#define UART_BRIDGE_H

#include <stdint.h>

void uart_init(void);
void uart_send_keypress(uint8_t key, uint8_t modifier);
void uart_send_string(const char* text);
void uart_send_enter(void);
void uart_send_delay(uint32_t ms);
void uart_send_gui_r(void);

#endif
