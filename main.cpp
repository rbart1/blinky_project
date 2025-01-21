/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


// Initialise the digital pin LED1 as an output

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

#ifdef BUTTON1
    InterruptIn button(BUTTON1);
#else
    bool button;
#endif

Ticker ticker;
volatile int clign_inter_index = 0;
volatile bool update_flag = false;

const std::chrono::milliseconds clign_inter[] = {200ms, 500ms, 1000ms};
const int NUM_INTERVALS = sizeof(clign_inter) / sizeof(clign_inter[0]);


void toggle_led()
{
    led = !led;
}

void change_freq() {
    clign_inter_index = (clign_inter_index + 1) % NUM_INTERVALS;
    update_flag = true; 
}

int main() {
    ticker.attach(&toggle_led, clign_inter[clign_inter_index]);

    button.fall(&change_freq);
 
    while (true) {
        if (update_flag) {
            ticker.attach(&toggle_led, clign_inter[clign_inter_index]);
            update_flag = false;
            printf("Nouvelle freq de clignotement: %lld ms\n", clign_inter[clign_inter_index].count());
        }
        ThisThread::sleep_for(100ms); 
    }
}
 