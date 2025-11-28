#ifndef PAYLOADS_H
#define PAYLOADS_H

#include <stdint.h>

// Function to execute payload based on index (0-3)
void execute_payload(uint8_t index);

// Individual payload functions
void payload_random_link(void);    // Payload 1: Rickroll video
void payload_notepad(void);        // Payload 2: Notepad demo
void payload_ram_crashing(void);   // Payload 3: RAM education
void payload_illegal_work(void);   // Payload 4: Data collection demo

#endif
