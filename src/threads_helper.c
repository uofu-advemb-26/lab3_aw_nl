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

int two_locks(int *count, SemaphoreHandle_t lock_a, SemaphoreHandle_t lock_b, TickType_t timeout)
{
    if (xSemaphoreTake(lock_a, timeout) == pdFALSE)
        return pdFALSE;
    {
        vTaskDelay(100);
        if (xSemaphoreTake(lock_b, timeout) == pdFALSE)
            return pdFALSE;
        {
            (*count)++;
            printf("Obtained both locks! count %d",  *count);
        }
        xSemaphoreGive(lock_b);
    }   
    xSemaphoreGive(lock_a);
    vTaskSuspend(NULL);
    return pdTRUE;
}