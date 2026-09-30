#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "threads.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 5UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE


int counter;

void setUp(void) 
{
    counter = 0;
}

void tearDown(void) {}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_main_print(void)
{        
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int before = counter;
    inc_counter(&counter, semaphore, 10, "test");
    int after = counter;
    TEST_ASSERT_TRUE_MESSAGE(after == before + 1, "Side print failed");
}

void test_side_print(void)
{
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int before = counter;
    inc_counter(&counter, semaphore, 10, "test");
    int after = counter;
    TEST_ASSERT_TRUE_MESSAGE(after == before + 1, "Side print failed");
}


void test_increment_semaphore_taken(void)
{

    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int counter = 0;
    xSemaphoreTake(semaphore, portMAX_DELAY);

    // call inc count with semaphore taken
    int result = inc_counter(&counter, semaphore, 10, "test");

    TEST_ASSERT_EQUAL_MESSAGE(pdFALSE, result, "Result from inc counter was not pdFALSE (timeout) when semaphore was taken");
    TEST_ASSERT_TRUE_MESSAGE(counter == 0, "Counter incremented incorrectly");
}

void test_increment_semaphore_available(void)
{

    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int counter = 0;
    // call inc count with semaphore taken
    int result = inc_counter(&counter, semaphore, 10, "test");

    TEST_ASSERT_EQUAL_MESSAGE(pdTRUE, result, "Result from inc counter was not pdTRUE (success) when semaphore was not taken");
    TEST_ASSERT_TRUE_MESSAGE(counter == 1, "Counter incremented incorrectly");
}




void main_thread(void *params)
{
    while (1) {

        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_side_print);
        RUN_TEST(test_main_print);
        RUN_TEST(test_increment_semaphore_taken);
        RUN_TEST(test_increment_semaphore_available);
        sleep_ms(5000);
        UNITY_END();
    }
}


int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    xTaskCreate(main_thread, "TestRunner",
            MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, NULL);

    vTaskStartScheduler();
    return 0;
}
