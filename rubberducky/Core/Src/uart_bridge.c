// uart_bridge.c - Sends keyboard commands over UART instead of USB HID

#include "uart_bridge.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;  // Using UART2 (ST-Link Virtual COM Port)

// Command protocol:
// CMD:type:data\n
// Examples:
//   CMD:KEY:0x28:0x00\n  (Enter key, no modifier)
//   CMD:STR:Hello World\n (Type string)
//   CMD:DELAY:1000\n (Delay 1000ms)

void uart_init(void) {
    // UART2 is already initialized by CubeMX for ST-Link VCP
    HAL_Delay(100);
}

void uart_send_keypress(uint8_t key, uint8_t modifier) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "CMD:KEY:0x%02X:0x%02X\n", key, modifier);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
    HAL_Delay(10);  // Small delay between commands
}

void uart_send_string(const char* text) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "CMD:STR:%s\n", text);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
}

void uart_send_enter(void) {
    const char* cmd = "CMD:ENTER\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
}

void uart_send_delay(uint32_t ms) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "CMD:DELAY:%lu\n", ms);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
}

// Helper function to send GUI key (Windows key)
void uart_send_gui_r(void) {
    // Windows Key + R
    uart_send_keypress(0x15, 0x08);  // R key + GUI modifier
}
