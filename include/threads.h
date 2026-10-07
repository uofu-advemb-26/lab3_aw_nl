#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>


#ifndef THREADS
#define THREADS

int inc_counter(int *count, SemaphoreHandle_t semaphore, TickType_t timeout, const char* msg);

#endif