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

Timer button_timer;
volatile int press_duration = 0;
volatile bool pressed = false;


void toggle_led()
{
    led = !led;
}


void button_pressed() {
    button_timer.start();
    pressed = true;
}
 

void button_released() {
    button_timer.stop();
    press_duration = chrono::duration_cast<chrono::milliseconds>(button_timer.elapsed_time()).count();
    button_timer.reset();
    pressed = false;
}

int main()
{
    button.fall(&button_pressed);
    button.rise(&button_released);
    while (true) {
        if (!pressed && press_duration > 0) {
            printf("Bouton relache apres %d ms\n", press_duration);
            press_duration = 0;
        }
        led = pressed ? 1 : 0;
 
        ThisThread::sleep_for(BLINKING_RATE);
    }

}
