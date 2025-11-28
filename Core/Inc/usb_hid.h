#ifndef USB_HID_H
#define USB_HID_H

#include "usbd_hid.h"
#include "main.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
// Keyboard modifier keys (CTRL, SHIFT, ALT, GUI/Win key)
#define KEY_CTRL_LEFT    0x01
#define KEY_SHIFT_LEFT   0x02
#define KEY_ALT_LEFT     0x04
#define KEY_GUI_LEFT     0x08

// Function declarations for keyboard emulation
void usb_hid_init(void);                          // Initialize USB HID
void usb_send_keypress(uint8_t key, uint8_t modifier); // Send single keypress
void send_string(const char* text);               // Type a string of text
void enter_key(void);                             // Press Enter key
void delay_ms(uint32_t ms);                       // Custom delay function

#endif
