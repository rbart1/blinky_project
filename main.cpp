
#include "mbed.h"
#include "scd4x.h"

sixtron::SCD4X scd4x(P1_I2C_SDA, P1_I2C_SCL);

static void display_measurement(sixtron::SCD4X::ErrorType err, uint16_t co2, double t, double rh)
{
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Erreur ecture des données: %d\n", err);
    } else {
        printf("CO2: %dppm ppm, Temp: %.2f C, Humidite: %.2f%%\n", co2, t, rh);
    }
}

int main() {
    printf("\n\n-------------------\n");

    scd4x.stop_periodic_measurement();
    ThisThread::sleep_for(500ms);

    if (scd4x.start_periodic_measurement() != sixtron::SCD4X::ErrorType::Ok) {
        printf("Erreur load mesures périodiques\n");
        return 1;
    }

    while (true) {
        if (scd4x.get_data_ready_status() == sixtron::SCD4X::ErrorType::Ok) {
            sixtron::scd4x_measurement_t measurement;
            sixtron::SCD4X::ErrorType err = scd4x.read_measurement(&measurement);
            display_measurement(err, measurement.co2, measurement.temperature, measurement.rh);
        } else {
            printf("attente\n");
        }

        ThisThread::sleep_for(5s);
    }
}


/*
 * Copyright (c) 2021, Koncepto.io
 * SPDX-License-Identifier: Apache-2.0
 */

/*
#include "MbedCRC.h"
#include "PinNameAliases.h"
#include "mbed.h"
#include "scd4x/scd4x.h"

static void display_value_result(sixtron::SCD4X::ErrorType err, uint16_t co2, double t, double rh)
{
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Error reading data: %d\n", err);
    } else {
        printf("CO2: %dppm, Temp: %f°C, RH: %f%%\n", co2, t, rh);
    }
}

static void test_get_serial(sixtron::SCD4X &sensor)
{
    uint16_t data[3];
    sixtron::SCD4X::ErrorType err;

    err = sensor.get_serial_number(data);
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Could not get serial\n");
    } else {
        printf("Sensor serial: %2x%2x%2x\n", data[0], data[1], data[2]);
    }
}

static void test_low_power_measurement(sixtron::SCD4X &sensor)
{
    float t, rh;
    uint16_t co2;
    sixtron::SCD4X::ErrorType err;
    sixtron::scd4x_measurement_t meas;

    printf("Periodic low power measurement\n");
    err = sensor.start_low_power_periodic_measurement();
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Periodic low power measurement cannot be started\n");
        sensor.stop_periodic_measurement();
        return;
    }

    for (int i = 0; i < 3; i++) {
        while (sensor.get_data_ready_status() != sixtron::SCD4X::ErrorType::Ok) {
            ThisThread::sleep_for(1s);
        }

        err = sensor.read_measurement(&meas);
        display_value_result(err, meas.co2, meas.temperature, meas.rh);

        ThisThread::sleep_for(10s);
    }
    sensor.stop_periodic_measurement();
    ThisThread::sleep_for(500ms);
}

static void test_periodic_measurement(sixtron::SCD4X &sensor)
{
    sixtron::scd4x_measurement_t meas;
    sixtron::SCD4X::ErrorType err;

    printf("Periodic measurement\n");
    err = sensor.start_periodic_measurement();
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Periodic measurement cannot be started\n");
        sensor.stop_periodic_measurement();
        return;
    }
    while (true) {
        err = sensor.get_data_ready_status();
        if (err != sixtron::SCD4X::ErrorType::Ok) {
            ThisThread::sleep_for(1s);
            continue;
        }
        err = sensor.read_measurement(&meas);
        display_value_result(err, meas.co2, meas.temperature, meas.rh);

        ThisThread::sleep_for(10s);
    }
}

static void test_single_shot_measurement(sixtron::SCD4X &sensor)
{
    sixtron::scd4x_measurement_t meas;
    sixtron::SCD4X::ErrorType err;

    printf("Single shot measurement\n");

    sensor.measure_single_shot();
    ThisThread::sleep_for(5s);

    err = sensor.read_measurement(&meas);
    display_value_result(err, meas.co2, meas.temperature, meas.rh);
}

static void test_single_shot_measurement_rht_only(sixtron::SCD4X &sensor)
{
    sixtron::scd4x_measurement_t meas = { 0 };
    sixtron::SCD4X::ErrorType err;

    printf("Single shot measurement (RHT only)\n");

    sensor.measure_single_shot_rht_only();
    ThisThread::sleep_for(50ms);

    err = sensor.read_measurement(&meas);
    display_value_result(err, meas.co2, meas.temperature, meas.rh);
}

static void test_selftest(sixtron::SCD4X &sensor)
{
    sixtron::SCD4X::ErrorType err;

    printf("Self test\n");
    err = sensor.perform_self_test();
    if (err != sixtron::SCD4X::ErrorType::Ok) {
        printf("Self test failed with error: %d\n", err);
    } else {
        printf("Self test succeeded\n");
    }
}

// main() runs in its own thread in the OS
int main()
{
    sixtron::SCD4X sensor(P1_I2C_SDA, P1_I2C_SCL);
    sixtron::SCD4X::ErrorType err;

    printf("\n\n-------------------\n");
    printf("--- SCD4X Demo ---\n");

    sensor.stop_periodic_measurement();
    ThisThread::sleep_for(500ms);

    test_get_serial(sensor);

    test_single_shot_measurement_rht_only(sensor);
    test_single_shot_measurement(sensor);
    test_low_power_measurement(sensor);
    test_selftest(sensor);
    test_periodic_measurement(sensor);
}

*/