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


Ticker ticker;


void toggle_led()
{
    led = !led;
}


int main() {
    ticker.attach(&toggle_led, BLINKING_RATE);

    while (true) { // Est ici pour garder le thread actif, je peux utiliser par exemple queue.dispatch_forever() à la place du while ! 
        ThisThread::sleep_for(BLINKING_RATE); 
    }
}
