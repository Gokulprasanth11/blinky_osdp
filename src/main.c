/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifiers for the "led0", "led1", and "led2" aliases. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

int main(void)
{
    int ret;

    /* Ensure all GPIOs are ready */
    if (!gpio_is_ready_dt(&led0) ||
        !gpio_is_ready_dt(&led1) ||
        !gpio_is_ready_dt(&led2)) {
        printf("Error: One or more LED GPIOs are not ready\n");
        return 1;
    }

    /* Configure each LED GPIO as output */
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printf("Error: Failed to configure LED0\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printf("Error: Failed to configure LED1\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printf("Error: Failed to configure LED2\n");
        return ret;
    }

    /* Main loop to toggle LEDs sequentially */
    while (1) {
        /* Turn on Red LED, turn off others */
        gpio_pin_set_dt(&led0, 1);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 0);
        printf("LED state: RED ON\n");
        k_msleep(SLEEP_TIME_MS);

        /* Turn on Green LED, turn off others */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 1);
        gpio_pin_set_dt(&led2, 0);
        printf("LED state: GREEN ON\n");
        k_msleep(SLEEP_TIME_MS);

        /* Turn on Blue LED, turn off others */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 1);
        printf("LED state: BLUE ON\n");
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}
