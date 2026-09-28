#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <threads.h>

int inc_counter(int *count, SemaphoreHandle_t semaphore)
{
    int new_count;
    xSemaphoreTake(semaphore, portMAX_DELAY);
    {
        new_count = *count += 1;
    }
    xSemaphoreGive(semaphore);
    return new_count;
}
