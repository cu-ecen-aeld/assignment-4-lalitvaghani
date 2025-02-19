#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)


void* threadfunc(void* thread_param)
{

    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    if (!thread_func_args) {
        ERROR_LOG("Invalid thread function arguments");
        return NULL;
    }

    // Wait before obtaining mutex
    usleep(thread_func_args->wait_to_obtain_ms * 1000);

    // Obtain mutex
    if (pthread_mutex_lock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to obtain mutex");
        free(thread_func_args);
        return NULL;
    }
    DEBUG_LOG("Mutex obtained");

    // Wait before releasing mutex
    usleep(thread_func_args->wait_to_release_ms * 1000);

    // Release mutex
    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to release mutex");
    } else {
        DEBUG_LOG("Mutex released");
    }

    free(thread_func_args);
    return NULL;

}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     if (!thread || !mutex) {
        ERROR_LOG("Invalid thread or mutex pointer");
        return false;
    }

    struct thread_data *thread_args = malloc(sizeof(struct thread_data));
    if (!thread_args) {
        ERROR_LOG("Failed to allocate memory for thread_data");
        return false;
    }

    thread_args->mutex = mutex;
    thread_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_args->wait_to_release_ms = wait_to_release_ms;

    if (pthread_create(thread, NULL, threadfunc, thread_args) != 0) {
        ERROR_LOG("Failed to create thread");
        free(thread_args);
        return false;
    }

    return true;

    return false;
}

