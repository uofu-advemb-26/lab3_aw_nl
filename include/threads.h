#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>


#ifndef THREADS
#define THREADS

struct DeadArgs {
    SemaphoreHandle_t a;
    SemaphoreHandle_t b;
    int counter;
};

int inc_counter(int *count, SemaphoreHandle_t semaphore, TickType_t timeout, const char* msg);
void two_locks(void *args);

#endif