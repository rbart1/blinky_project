/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     250ms


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

void toggle_led()
{
    led = !led;
}

int main()
{
    button.fall(&toggle_led);
    button.rise(&toggle_led);

    while (true) {
        printf("Alive!\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
