#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "threads.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

int counter;
SemaphoreHandle_t semaphore;

void setUp(void) 
{
    counter = 0;
    semaphore = xSemaphoreCreateCounting(1, 1);
}

void tearDown(void) {}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_main_print(void)
{
    int before = counter;
    inc_counter(&counter, semaphore);
    int after = counter;
    TEST_ASSERT_TRUE_MESSAGE(after == before + 1, "Side print failed");
}

void test_side_print(void)
{
    int before = counter;
    inc_counter(&counter, semaphore);
    int after = counter;
    TEST_ASSERT_TRUE_MESSAGE(after == before + 1, "Side print failed");
}



int main (void)
{
    stdio_init_all();
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_side_print);
        RUN_TEST(test_main_print);
        sleep_ms(5000);
        UNITY_END();
    }
}
