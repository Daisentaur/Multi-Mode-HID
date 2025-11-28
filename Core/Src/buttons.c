// buttons.c

#include "buttons.h"
#include "payloads.h"
#include "i2c_lcd.h" // Make sure this matches your LCD header file name
#include <stdint.h>
#include "uart_bridge.h"

extern uint8_t uart_ready;  // Change from usb_ready
#define NUM_PAYLOADS 4


// --- Payload names for the menu ---
char* payload_names[NUM_PAYLOADS] = {
    "1.Rickroll",
    "2.Notepad Demo",
    "3.RAM Education",
    "4.Data Collection"
};

// --- Private Variables for Debouncing and State Management ---

// Debounce state machine timing (in milliseconds)
#define DEBOUNCE_TIME_MS 100

// Tracks when the button was last successfully pressed
static uint32_t last_cycle_press_time = 0;
static uint32_t last_select_press_time = 0;

// Global index variable (tracks the current payload)
static uint8_t current_payload_index = 0;

// --- LCD Update Menu Function ---
void LCD_UpdateMenu(uint8_t index) {
    lcd_clear();

    // Line 1: Header
    lcd_put_cursor(0, 0);
    lcd_send_string("> Payload Select");

    // Line 2: Selected Payload Name
    lcd_put_cursor(1, 0);

    if (index < NUM_PAYLOADS) {
        lcd_send_string(payload_names[index]);
    } else {
        lcd_send_string("Index Error!");
    }
}

// --- Internal Helper Function for Reading a Debounced Button ---

/**
 * @brief Checks if a button is pressed and handles debouncing.
 * @param GPIO_PORT: Port of the button (e.g., GPIOA, GPIOC)
 * @param GPIO_PIN: Pin of the button (e.g., GPIO_PIN_0, GPIO_PIN_13)
 * @param last_press_time_ptr: Pointer to the static timestamp variable
 * @return 1 if a debounced press occurred, 0 otherwise.
 */
static uint8_t is_button_pressed_debounced(
    GPIO_TypeDef *GPIO_PORT,
    uint16_t GPIO_PIN,
    uint32_t *last_press_time_ptr)
{
    // The button is wired as Pull-Up, so LOW means PRESSED
    if (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN) == GPIO_PIN_RESET)
    {
        uint32_t current_time = HAL_GetTick();

        // Check if enough time has passed since the last valid press
        if (current_time - *last_press_time_ptr > DEBOUNCE_TIME_MS)
        {
            *last_press_time_ptr = current_time; // Update timestamp
            return 1; // Button press confirmed
        }
    }
    return 0;
}

// --- Public Main Function (Called inside main's while(1) loop) ---

void BUTTONS_HandleInput(void) {
    static uint8_t executing = 0;  // Prevents multiple simultaneous executions

    // 1. CYCLE Button (PA0 - Black Button) - Change payload selection
    if (is_button_pressed_debounced(
        BUTTON_CYCLE_PORT,
        BUTTON_CYCLE_PIN,
        &last_cycle_press_time))
    {
        // Only allow cycling if not currently executing a payload
        if (!executing) {
            // Cycle through payloads (0,1,2,3,0,1,2,3,...)
            current_payload_index = (current_payload_index + 1) % NUM_PAYLOADS;

            // Update LCD display with new selection
            LCD_UpdateMenu(current_payload_index);
            HAL_Delay(100);
        }
    }

    // 2. SELECT Button (PC13 - Blue Button) - Execute selected payload
    if (is_button_pressed_debounced(
        BUTTON_SELECT_PORT,
        BUTTON_SELECT_PIN,
        &last_select_press_time))
    {
        // Only execute if USB is ready and not already executing
        if (!executing && uart_ready) {
            executing = 1;  // Set flag to prevent re-entry

            // Show execution message on LCD
            lcd_put_cursor(0, 0);
            lcd_send_string(">> EXECUTING... ");

            // Execute the selected payload
            execute_payload(current_payload_index);

            // Wait a moment after execution completes
            HAL_Delay(1000);

            // Return to normal menu display
            LCD_UpdateMenu(current_payload_index);
            executing = 0;  // Clear execution flag
        }
    }
}
