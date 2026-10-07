#ifndef TEST_HELPER
#define TEST_HELPER

#include <FreeRTOS.h>
#include <semphr.h>

struct DeadArgs {
    SemaphoreHandle_t a;
    SemaphoreHandle_t b;
    int counter;
};

struct OrphanedArgs {
    SemaphoreHandle_t lock;
    int counter;
};
void two_locks(void *args);
int orphaned_lock(int *counter, SemaphoreHandle_t semaphore, TickType_t timeout);
int unorphaned_lock(int *counter, SemaphoreHandle_t semaphore, TickType_t timeout);

#endif