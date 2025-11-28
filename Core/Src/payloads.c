// payloads.c - Updated for UART bridge

#include "payloads.h"
#include "uart_bridge.h"
#include <string.h>

// Execute payload based on index (0-3)
void execute_payload(uint8_t index) {
    switch (index) {
        case 0:
            payload_random_link();
            break;
        case 1:
            payload_notepad();
            break;
        case 2:
            payload_ram_crashing();
            break;
        case 3:
            payload_illegal_work();
            break;
        default:
            break;
    }
}

// Payload 1: Open Rickroll video in browser
void payload_random_link(void) {
    uart_send_delay(2000);  // Wait 2 seconds

    // Open Run dialog (Windows key + R)
    uart_send_gui_r();
    uart_send_delay(500);

    // Type YouTube URL
    uart_send_string("www.youtube.com/watch?v=dQw4w9WgXcQ");
    uart_send_delay(500);
    uart_send_enter();
}

// Payload 2: Open Notepad with security message
void payload_notepad(void) {
    uart_send_delay(2000);

    // Open Notepad via Run dialog
    uart_send_gui_r();
    uart_send_delay(500);
    uart_send_string("notepad");
    uart_send_enter();
    uart_send_delay(1000);

    // Type security awareness message
    uart_send_string("This is a security demonstration!");
    uart_send_enter();
    uart_send_enter();
    uart_send_string("Your system could be vulnerable to USB attacks.");
    uart_send_enter();
    uart_send_string("Always use trusted USB devices!");
    uart_send_enter();
    uart_send_string("Educational purpose only.");
}

// Payload 3: Demonstrate RAM attack concepts (educational)
void payload_ram_crashing(void) {
    uart_send_delay(2000);

    // Open command prompt
    uart_send_gui_r();
    uart_send_delay(500);
    uart_send_string("cmd");
    uart_send_enter();
    uart_send_delay(1000);

    // Educational message about RAM vulnerabilities
    uart_send_string("echo ===== RAM SECURITY DEMONSTRATION =====");
    uart_send_enter();
    uart_send_delay(500);
    uart_send_string("echo Real RAM attacks could:");
    uart_send_enter();
    uart_send_delay(500);
    uart_send_string("echo 1. Exhaust memory resources");
    uart_send_enter();
    uart_send_delay(500);
    uart_send_string("echo 2. Perform buffer overflow attacks");
    uart_send_enter();
    uart_send_delay(500);
    uart_send_string("echo 3. Scrape sensitive data from memory");
    uart_send_enter();
    uart_send_delay(500);
    uart_send_string("echo 4. Cause system instability");
    uart_send_enter();
    uart_send_delay(1000);
    uart_send_string("echo This is simulation only - no actual harm!");
    uart_send_enter();
}

// Payload 4: Simulate data collection (educational)
void payload_illegal_work(void) {
    uart_send_delay(2000);

    // Open command prompt
    uart_send_gui_r();
    uart_send_delay(500);
    uart_send_string("cmd");
    uart_send_enter();
    uart_send_delay(1000);

    // Create temporary directory for demonstration
    uart_send_string("mkdir C:\\temp_demo 2>nul");
    uart_send_enter();
    uart_send_delay(500);

    // Simulate collecting system information
    uart_send_string("echo === SECURITY DEMONSTRATION === > C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(300);
    uart_send_string("echo Simulated data collection >> C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(300);
    uart_send_string("echo This demonstrates what malicious USB >> C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(300);
    uart_send_string("echo devices could potentially do >> C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(300);
    uart_send_string("echo Educational purpose only! >> C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(1000);

    // Display the collected "data"
    uart_send_string("notepad C:\\temp_demo\\info.txt");
    uart_send_enter();
    uart_send_delay(1000);

    // Cleanup message
    uart_send_string("echo Demonstration complete. This was harmless.");
    uart_send_enter();
}
