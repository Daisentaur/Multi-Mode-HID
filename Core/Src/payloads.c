#include "payloads.h"
#include "usb_hid.h"
#include <string.h>

// Execute payload based on index (0-3)
void execute_payload(uint8_t index) {
    // Route to the appropriate payload function
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
            // Invalid index - do nothing
            break;
    }
}

// Payload 1: Open Rickroll video in browser
void payload_random_link(void) {
    delay_ms(2000);  // Wait 2 seconds for user to focus target
    
    // Open Run dialog (Windows key + R)
    usb_send_keypress(0x15, 0x08); // 'R' key + GUI (Windows key)
    delay_ms(500);
    
    // Type YouTube URL
    send_string("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    enter_key();
    delay_ms(3000);
    
    // Make video fullscreen
    usb_send_keypress(0x0F, 0); // 'F' key for fullscreen
}

// Payload 2: Open Notepad with security message
void payload_notepad(void) {
    delay_ms(2000);
    
    // Open Notepad via Run dialog
    usb_send_keypress(0x15, 0x08); // Win + R
    delay_ms(500);
    send_string("notepad");
    enter_key();
    delay_ms(1000);
    
    // Type security awareness message
    send_string("This is a security demonstration!");
    enter_key();
    enter_key();  // Extra enter for spacing
    send_string("Your system could be vulnerable to USB attacks.");
    enter_key();
    send_string("Always use trusted USB devices!");
    enter_key();
    send_string("Educational purpose only.");
}

// Payload 3: Demonstrate RAM attack concepts (educational)
void payload_ram_crashing(void) {
    delay_ms(2000);
    
    // Open command prompt
    usb_send_keypress(0x15, 0x08); // Win + R
    delay_ms(500);
    send_string("cmd");
    enter_key();
    delay_ms(1000);
    
    // Educational message about RAM vulnerabilities
    send_string("echo ===== RAM SECURITY DEMONSTRATION =====");
    enter_key();
    delay_ms(500);
    send_string("echo Real RAM attacks could:");
    enter_key();
    delay_ms(500);
    send_string("echo 1. Exhaust memory resources");
    enter_key();
    delay_ms(500);
    send_string("echo 2. Perform buffer overflow attacks");
    enter_key();
    delay_ms(500);
    send_string("echo 3. Scrape sensitive data from memory");
    enter_key();
    delay_ms(500);
    send_string("echo 4. Cause system instability");
    enter_key();
    delay_ms(1000);
    send_string("echo This is simulation only - no actual harm!");
    enter_key();
}

// Payload 4: Simulate data collection (educational)
void payload_illegal_work(void) {
    delay_ms(2000);
    
    // Open command prompt
    usb_send_keypress(0x15, 0x08); // Win + R
    delay_ms(500);
    send_string("cmd");
    enter_key();
    delay_ms(1000);
    
    // Create temporary directory for demonstration
    send_string("mkdir C:\\temp_demo 2>nul");
    enter_key();
    delay_ms(500);
    
    // Simulate collecting system information
    send_string("echo === SECURITY DEMONSTRATION === > C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(300);
    send_string("echo Simulated data collection >> C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(300);
    send_string("echo This demonstrates what malicious USB >> C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(300);
    send_string("echo devices could potentially do >> C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(300);
    send_string("echo Educational purpose only! >> C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(1000);
    
    // Display the collected "data"
    send_string("notepad C:\\temp_demo\\info.txt");
    enter_key();
    delay_ms(1000);
    
    // Cleanup message
    send_string("echo Demonstration complete. This was harmless.");
    enter_key();
}
