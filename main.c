#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Pin definitions
#define RED_LED     GPIO_NUM_2
#define YELLOW_LED  GPIO_NUM_16
#define GREEN_LED   GPIO_NUM_26
#define BUTTON_PIN  GPIO_NUM_4

// Timing in milliseconds
#define RED_TIME     3000
#define GREEN_TIME   3000
#define YELLOW_TIME  2000

volatile bool force_red = false; // Shared flag

// Function to turn on only one LED
void turn_on_only(gpio_num_t ledPin) {
    gpio_set_level(RED_LED, ledPin == RED_LED ? 1 : 0);
    gpio_set_level(YELLOW_LED, ledPin == YELLOW_LED ? 1 : 0);
    gpio_set_level(GREEN_LED, ledPin == GREEN_LED ? 1 : 0);
}

// Smart delay with button check
void smart_delay(int total_ms) {
    int elapsed = 0;
    while (elapsed < total_ms) {
        if (gpio_get_level(BUTTON_PIN) == 0) { // Button pressed
            force_red = true;
        }
        if (force_red) {
            turn_on_only(RED_LED);
            vTaskDelay(pdMS_TO_TICKS(RED_TIME));
            force_red = false;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
        elapsed += 10;
    }
}

// Main traffic light task
void traffic_light_task(void *pvParameter) {
    while (1) {
        turn_on_only(RED_LED);
        smart_delay(RED_TIME);

        turn_on_only(GREEN_LED);
        smart_delay(GREEN_TIME);

        turn_on_only(YELLOW_LED);
        smart_delay(YELLOW_TIME);
    }
}

// Main application entry point
void app_main(void) {
    // Configure LEDs as outputs
    gpio_reset_pin(RED_LED);
    gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
    gpio_reset_pin(YELLOW_LED);
    gpio_set_direction(YELLOW_LED, GPIO_MODE_OUTPUT);
    gpio_reset_pin(GREEN_LED);
    gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);

    // Configure button as input with pull-up
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);

    // Start traffic light task
    xTaskCreate(&traffic_light_task, "traffic_light_task", 2048, NULL, 5, NULL);
}
