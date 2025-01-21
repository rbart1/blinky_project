#include "mbed.h"
UnBufferedSerial serial(USBTX, USBRX, 9600);

void serial_write(const char *message){
    for (size_t i = 0; i<strlen(message); i++){
        serial.putc(message[i]);
    }
}

void ping() {
    for (int i = 0; i < 100; i++) {
        serial_write("Ping");
        ThisThread::sleep_for(100ms);
    }
}

void pong() {
    for (int i = 0; i < 100; i++) {
        serial_write("Pong");
        ThisThread::sleep_for(100ms);
    }
}

int main() {
    Thread thread1;
    Thread thread2;

    thread1.start(ping);
    thread2.start(pong);

    while (true) {
        serial_write("Alive!\n");
        ThisThread::sleep_for(2s);
    }
}
