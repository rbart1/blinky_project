/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     200ms


int main()
{
    // Initialise the digital pin LED1 as an output

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;

#endif

#ifdef BUTTON1
    DigitalIn button(BUTTON1);
#else
    bool button;

#endif

    while (true) {
        if(button.read() == 1){
            led = 1 ;
            printf("BTN1_ON\n");
        }
        else{
            led = 0;
            printf("BTN1_OFF\n");
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
