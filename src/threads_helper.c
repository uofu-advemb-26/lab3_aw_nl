#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <threads.h>
#include <stdio.h>

int inc_counter(int *count, SemaphoreHandle_t semaphore, TickType_t timeout, const char* msg)
{
    if (xSemaphoreTake(semaphore, timeout) == pdFALSE) 
        return pdFALSE;
    {
        (*count)++;
        printf("HELLO WORLD FROM %s: count %d", msg,  *count);
    }
    xSemaphoreGive(semaphore);
    return pdTRUE;
}

void two_locks(void *args)
{
    struct DeadArgs *dead_args = (struct DeadArgs *)args;

    xSemaphoreTake(dead_args->a, portMAX_DELAY);
    {
        vTaskDelay(100);
        xSemaphoreTake(dead_args->b, portMAX_DELAY);
        {
            (dead_args->counter)++;
            printf("Obtained both locks! count %d",  dead_args->counter);
        }
        xSemaphoreGive(dead_args->b);
    }   
    xSemaphoreGive(dead_args->a);
    vTaskSuspend(NULL);
}

int orphaned_lock(int *counter, SemaphoreHandle_t semaphore, TickType_t timeout)
{
    if (xSemaphoreTake(semaphore, timeout) == pdFALSE)
        return pdFALSE;
    {
        (*counter)++;
        if (*counter % 2) {
            return 0;
        }
        printf("Count %d\n", counter);
    }
    xSemaphoreGive(semaphore);
    return pdTRUE;
}

int unorphaned_lock(int *counter, SemaphoreHandle_t semaphore, TickType_t timeout)
{
    if (xSemaphoreTake(semaphore, timeout) == pdFALSE)
        return pdFALSE;
    {
        (*counter)++;
        if (!(*counter % 2)) {
            return 0;
        }
        printf("Count %d\n", counter);
    }
    xSemaphoreGive(semaphore);
    return pdTRUE;
}