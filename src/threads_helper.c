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
