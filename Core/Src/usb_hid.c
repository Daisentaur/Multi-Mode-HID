#include "usb_hid.h"
#include "usbd_hid.h"  // This is from the USB HID middleware

// Keyboard modifier keys
#define KEY_CTRL_LEFT    0x01
#define KEY_SHIFT_LEFT   0x02
#define KEY_ALT_LEFT     0x04
#define KEY_GUI_LEFT     0x08

// We'll get the USB device handle from the HID layer
extern USBD_HandleTypeDef hUsbDeviceFS;

// HID keycode mapping
static uint8_t ascii_to_hid(uint8_t c) {
    if (c >= 'a' && c <= 'z') return (4 + (c - 'a'));
    if (c >= 'A' && c <= 'Z') return (4 + (c - 'A'));
    if (c >= '1' && c <= '9') return (30 + (c - '1'));
    if (c == '0') return 39;

    switch (c) {
        case ' ': return 0x2C;
        case '\n': return 0x28;
        case '\t': return 0x2B;
        case '!': return 0x1E;
        case '@': return 0x1F;
        case '#': return 0x20;
        case '$': return 0x21;
        case '%': return 0x22;
        case '^': return 0x23;
        case '&': return 0x24;
        case '*': return 0x25;
        case '(': return 0x26;
        case ')': return 0x27;
        case '-': return 0x2D;
        case '=': return 0x2E;
        case '[': return 0x2F;
        case ']': return 0x30;
        case '\\': return 0x31;
        case ';': return 0x33;
        case '\'': return 0x34;
        case '`': return 0x35;
        case ',': return 0x36;
        case '.': return 0x37;
        case '/': return 0x38;
        case '_': return 0x2D;
        case '+': return 0x2E;
        case '{': return 0x2F;
        case '}': return 0x30;
        case '|': return 0x31;
        case ':': return 0x33;
        case '"': return 0x34;
        case '~': return 0x35;
        case '<': return 0x36;
        case '>': return 0x37;
        case '?': return 0x38;
        default: return 0;
    }
}

void usb_hid_init(void) {
    // USB is initialized by MX_USB_DEVICE_Init() from CubeMX
    // We just need to wait a bit for enumeration
    HAL_Delay(2000);
}

void usb_send_keypress(uint8_t key, uint8_t modifier) {
    uint8_t report[8] = {modifier, 0, key, 0, 0, 0, 0, 0};

    // Use the correct HID send function
    USBD_HID_SendReport(&hUsbDeviceFS, report, 8);
    HAL_Delay(10);

    // Send release report
    uint8_t release[8] = {0};
    USBD_HID_SendReport(&hUsbDeviceFS, release, 8);
    HAL_Delay(10);
}

void send_string(const char* text) {
    while (*text) {
        uint8_t key = ascii_to_hid(*text);
        uint8_t modifier = 0;

        if ((*text >= 'A' && *text <= 'Z') ||
            (*text >= '!' && *text <= '&') ||
            (*text == '(') || (*text == ')') ||
            (*text == '_') || (*text == '+') ||
            (*text == '{') || (*text == '}') ||
            (*text == '|') || (*text == ':') ||
            (*text == '"') || (*text == '~') ||
            (*text == '<') || (*text == '>') ||
            (*text == '?')) {
            modifier = KEY_SHIFT_LEFT;
        }

        if (key != 0) {
            usb_send_keypress(key, modifier);
        }
        text++;
    }
}

void enter_key(void) {
    usb_send_keypress(0x28, 0);
}

void delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}
