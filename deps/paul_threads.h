/* paul/paul_threads.h -- https://github.com/takeiteasy/paul

 Copyright (C) 2025 George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>. */

 /*!
 @header paul_threads.h
 @copyright George Watson GPLv3
 @updated 2025-07-19
 @brief Cross-platform polyfill for pthreads + C11 threads for C/C++.
 @discussion
    Implementation is included when PAUL_THREADS_IMPLEMENTATION or PAUL_IMPLEMENTATION is defined.
*/

#ifndef PAUL_THREADS_HEADER
#define PAUL_THREADS_HEADER
#ifdef __cplusplus
extern "C" {
#endif

// TODO: Add support for blocks
// TODO: Add lock guard
// TODO: Add support for c89atomics (if <C11)

#if defined(_WIN32) || defined(_WIN64)
#define PAUL_THREADS_PLATFORM_WINDOWS
#endif

#ifndef PATH_TO_C89ATOMICS_H
#define PATH_TO_C89ATOMICS_H "c89atomics.h"
#endif

#if __STDC_VERSION__ < 201112L
#define PAUL_THREADS_FORCE_INCLUDE 0
#else
#define PAUL_THREADS_FORCE_INCLUDE 1
#endif
#ifndef __has_include
#define __has_include(x) PAUL_THREADS_FORCE_INCLUDE
#endif
// NOTE: do NOT close the header guard here - the guard stays open until
// the end of this file. The stray #endif above caused the header to be
// prematurely terminated which led to incompatible linkage declarations.

#if defined(__cplusplus)
/* When compiling as C++, prefer <atomic> but provide simple non-atomic
 * fallbacks so the header can be included in C++ translation units for
 * build-only stubs. These fallbacks are intentionally non-atomic and
 * only intended for compilation testing, not for production use. */
#include <atomic>
typedef bool atomic_bool;
typedef size_t atomic_size_t;
#define atomic_load(p) (*(p))
#define atomic_fetch_add(p, v) ((*(p)) += (v))
#define atomic_fetch_sub(p, v) ((*(p)) -= (v))
#define atomic_store(p, v) ((*(p)) = (v))
#else
#if __STDC_VERSION__ >= 201112L && __has_include(<stdatomic.h>)
#include <stdatomic.h>
#else
#ifndef c89atomic_h
#if __has_include(PATH_TO_C89ATOMICS_H)
#include PATH_TO_C89ATOMICS_H
#else
#error paul_threads requires stdatomic.h or c89atomics.h
#endif
#endif
/* TODO: Wrapper macros for c89atomics here */
#endif
#endif

#if !defined(__cplusplus) || __STDC_VERSION__ < 201112L || (defined(PLATFORM_WINDOWS) && _MSV_VER < 1900)
#ifndef bool
#define bool int
#define true 1
#define false 0
#endif
#else
#include <stdbool.h>
#endif

#include <time.h>

#if __STDC_VERSION__ >= 201112L && __has_include(<threads.h>)
#include <threads.h>
#define PAUL_THREADS_NO_IMPL
#define PAUL_THREADS_C11
#else
#ifdef PAUL_THREADS_PLATFORM_WINDOWS
#if defined(PAUL_THREADS_USE_NATIVE_CALL_ONCE) && (_WIN32_WINNT < 0x0600)
#error Native call once requires _WIN32_WINNT>=0x0600
#endif
#if defined(PAUL_THREADS_USE_NATIVE_CV) && (_WIN32_WINNT < 0x0600)
#error Native conditional variables requires _WIN32_WINNT>=0x0600
#endif
#endif
#endif

#ifdef PAUL_THREADS_USE_NATIVE_CALL_ONCE
#define ONCE_FLAG_INIT INIT_ONCE_STATIC_INIT
#else
#define ONCE_FLAG_INIT {0}
#endif
#define TSS_DTOR_ITERATIONS 1

#if defined(PLATFORM_WINDOWS) && _WIN32_WINNT >= 0x0600
// Prefer native WindowsAPI on newer environment.
#define PAUL_THREADS_USE_NATIVE_CALL_ONCE
#define EMULATED_THREADS_USE_NATIVE_CV
#endif
#define EMULATED_THREADS_TSS_DTOR_SLOTNUM 64  // see TLS_MINIMUM_AVAILABLE

#ifdef PAUL_THREADS_PLATFORM_WINDOWS
#include <windows.h>
typedef CRITICAL_SECTION pthread_mutex_t;
typedef void pthread_mutexattr_t;
typedef void pthread_condattr_t;
typedef void pthread_rwlockattr_t;
typedef HANDLE pthread_t;
typedef DWORD pthread_key_t;

#ifdef PAUL_THREADS_USE_NATIVE_CV
typedef CONDITION_VARIABLE pthread_cond_t;
#else
typedef struct {
    int blocked;
    int gone;
    int to_unblock;
    HANDLE sem_queue;
    HANDLE sem_gate;
    CRITICAL_SECTION monitor;
} pthread_cond_t;
#endif

#ifdef PAUL_THREADS_USE_NATIVE_CALL_ONCE
typedef INIT_ONCE pthread_once_t;
#else
typedef struct {
    volatile LONG status;
} pthread_once_t;
#endif

typedef struct {
    SRWLock lock;
    bool exclusive;
} pthread_rwlock_t;

int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(*start_routine)(void*), void *arg);
int pthread_join(pthread_t thread, void **value_ptr);
int pthread_detach(pthread_t thread);
pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);
void pthread_exit(void *retval);

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abs_timeout);

int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));

int pthread_key_create(pthread_key_t *key, void (*destructor)(void *));
int pthread_key_delete(pthread_key_t key);
void* pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);
#else
#include <pthread.h>
#endif

#ifndef PAUL_THREADS_C11
#ifdef INIT_ONCE_STATIC_INIT
#define TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
#else
#define TSS_DTOR_ITERATIONS 1  // assume TSS dtor MAY be called at least once.
#endif

typedef pthread_cond_t  cnd_t;
typedef pthread_t       thrd_t;
typedef pthread_key_t   tss_t;
typedef pthread_mutex_t mtx_t;
typedef pthread_once_t  once_flag;

typedef void (*tss_dtor_t)(void*);
typedef int (*thrd_start_t)(void*);

enum {
    mtx_plain     = 0,
    mtx_try       = 1,
    mtx_timed     = 2,
    mtx_recursive = 4
};

enum {
    thrd_success = 0, // succeeded
    thrd_timeout,     // timeout
    thrd_error,       // failed
    thrd_busy,        // resource busy
    thrd_nomem        // out of memory
};

void call_once(once_flag *flag, void (*func)(void));

int cnd_broadcast(cnd_t *cond);
void cnd_destroy(cnd_t *cond);
int cnd_init(cnd_t *cond);
int cnd_signal(cnd_t *cond);
int cnd_timedwait(cnd_t *cond, mtx_t *mtx, const struct timespec *xt);
int cnd_wait(cnd_t *cond, mtx_t *mtx);

void mtx_destroy(mtx_t *mtx);
int mtx_init(mtx_t *mtx, int type);
int mtx_lock(mtx_t *mtx);
int mtx_timedlock(mtx_t *mtx, const struct timespec *xt);
int mtx_trylock(mtx_t *mtx);
int mtx_unlock(mtx_t *mtx);

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
thrd_t thrd_current(void);
int thrd_detach(thrd_t thr);
int thrd_equal(thrd_t thr0, thrd_t thr1);
void thrd_exit(int res);
int thrd_join(thrd_t thr, int *res);
void thrd_sleep(const struct timespec *xt);
void thrd_yield(void);

int tss_create(tss_t *key, tss_dtor_t dtor);
void tss_delete(tss_t key);
void *tss_get(tss_t key);
int tss_set(tss_t key, void *val);
#endif

#if defined(PAUL_THREADS_PLATFORM_WINDOWS)
struct timespec {
    long tv_sec;
    long tv_nsec;
};
#endif

/*!
 @function thrd_timeout_ms
 @param milliseconds The number of milliseconds to add to the current time
 @return Returns a timespec representing the absolute time now + milliseconds
 @brief Return an absolute timespec representing now + milliseconds
 @discussion Named "thrd_timeout_ms" to avoid colliding with the enum identifier "thrd_timeout" used for return codes.
*/
struct timespec thrd_timeout_ms(unsigned int milliseconds);

/*!
 @typedef thrd_queue_node_t
 @field data Pointer to the data stored in the node
 @field next Pointer to the next node in the queue
 @discussion Node structure for the thread-safe queue
*/
typedef struct thrd_queue_node {
    void *data;
    struct thrd_queue_node *next;
} thrd_queue_node_t;

/*!
 @typedef thrd_queue_t
 @field head Pointer to the head of the queue
 @field tail Pointer to the tail of the queue
 @field mutex Mutex for thread safety
 @field not_empty Condition variable for waiting on empty queue
 @field size Current number of items in the queue
 @field max_size Maximum size of the queue
 @field shutdown Flag indicating if the queue is shutting down
 @discussion Thread-safe queue structure
*/
typedef struct thrd_queue {
    thrd_queue_node_t *head;
    thrd_queue_node_t *tail;
    mtx_t mutex;
    cnd_t not_empty;
    size_t size;
    size_t max_size;
    bool shutdown;
} thrd_queue_t;

/*!
 @function thrd_queue_init
 @param queue Pointer to the queue to initialize
 @param max_size Maximum size of the queue
 @return Returns thrd_success on success, thrd_error on failure
 @brief Initialize a thread-safe queue
*/
int thrd_queue_init(thrd_queue_t *queue, size_t max_size);
/*!
 @function thrd_queue_destroy
 @param queue Pointer to the queue to destroy
 @brief Destroy a thread-safe queue
*/
void thrd_queue_destroy(thrd_queue_t *queue);
/*!
 @function thrd_queue_enqueue
 @param queue Pointer to the queue
 @param data Pointer to the data to enqueue
 @return Returns thrd_success on success, thrd_error on failure, thrd_busy if queue is full
 @brief Enqueue data into the thread-safe queue
*/
int thrd_queue_enqueue(thrd_queue_t *queue, void *data);
/*!
 @function thrd_queue_dequeue
 @param queue Pointer to the queue
 @param data Pointer to a pointer to receive the dequeued data
 @return Returns thrd_success on success, thrd_error on failure
 @brief Dequeue data from the thread-safe queue, blocking if empty
*/
int thrd_queue_dequeue(thrd_queue_t *queue, void **data);
/*!
 @function thrd_queue_try_dequeue
 @param queue Pointer to the queue
 @param data Pointer to a pointer to receive the dequeued data
 @return Returns thrd_success on success, thrd_busy if empty, thrd_error on failure
 @brief Try to dequeue data from the thread-safe queue without blocking
*/
int thrd_queue_try_dequeue(thrd_queue_t *queue, void **data);
/*!
 @function thrd_queue_size
 @param queue Pointer to the queue
 @return Returns the current number of items in the queue
 @brief Get the size of the thread-safe queue
*/
size_t thrd_queue_size(thrd_queue_t *queue);
/*!
 @function thrd_queue_empty
 @param queue Pointer to the queue
 @return Returns true if the queue is empty, false otherwise
 @brief Check if the thread-safe queue is empty
*/
bool thrd_queue_empty(thrd_queue_t *queue);
/*!
 @function thrd_queue_shutdown
 @param queue Pointer to the queue
 @brief Shutdown the thread-safe queue
*/
void thrd_queue_shutdown(thrd_queue_t *queue);

/*!
 @typedef job_t
 @field function Pointer to the function to execute
 @field arg Argument to pass to the function
 @field cleanup Optional cleanup function
 @discussion Job structure for thread pool tasks
*/
typedef struct job {
    void (*function)(void *arg);
    void *arg;
    void (*cleanup)(void *arg); // Optional cleanup function
} job_t;

/*!
 @typedef job_node_t
 @field job The job contained in this node
 @field next Pointer to the next node
 @discussion Node structure for the job queue
*/
typedef struct job_node {
    job_t job;
    struct job_node *next;
} job_node_t;

/*!
 @typedef job_queue_t
 @field head Pointer to the head of the job queue
 @field tail Pointer to the tail of the job queue
 @field mutex Mutex for thread safety
 @field not_empty Condition variable for waiting on empty queue
 @field size Current number of jobs in the queue
 @field max_size Maximum size of the queue
 @field shutdown Flag indicating if the queue is shutting down
 @discussion Job queue structure for thread pool
*/
typedef struct job_queue {
    job_node_t *head;
    job_node_t *tail;
    mtx_t mutex;
    cnd_t not_empty;
    size_t size;
    size_t max_size;
    bool shutdown;
} job_queue_t;

/*!
 @typedef thrd_pool_t
 @field threads Array of worker threads
 @field num_threads Number of worker threads
 @field job_queue The job queue
 @field shutdown Atomic flag indicating if the pool is shutting down
 @field active_threads Atomic count of active threads
 @field pool_mutex Mutex for pool operations
 @field all_threads_idle Condition variable for waiting on all threads idle
 @discussion Thread pool structure
*/
typedef struct {
    thrd_t *threads;
    size_t num_threads;
    job_queue_t job_queue;
    atomic_bool shutdown;
    atomic_size_t active_threads;
    mtx_t pool_mutex;
    cnd_t all_threads_idle;
} thrd_pool_t;

/*!
 @function thrd_pool_create
 @param num_threads Number of worker threads
 @param max_queue_size Maximum size of the job queue
 @return Returns a pointer to the created thread pool, or NULL on failure
 @brief Create a thread pool
*/
thrd_pool_t* thrd_pool_create(size_t num_threads, size_t max_queue_size);
/*!
 @function thrd_pool_submit
 @param pool Pointer to the thread pool
 @param function Pointer to the function to execute
 @param arg Argument to pass to the function
 @param cleanup Optional cleanup function
 @return Returns thrd_success on success, thrd_error on failure
 @brief Submit a job to the thread pool
*/
int thrd_pool_submit(thrd_pool_t *pool, void (*function)(void*), void *arg, void (*cleanup)(void*));
/*!
 @function thrd_pool_wait
 @param pool Pointer to the thread pool
 @brief Wait for all jobs in the thread pool to complete
*/
void thrd_pool_wait(thrd_pool_t *pool);
/*!
 @function thrd_pool_destroy
 @param pool Pointer to the thread pool
 @brief Destroy the thread pool
*/
void thrd_pool_destroy(thrd_pool_t *pool);
/*!
 @function thrd_pool_get_thread_count
 @param pool Pointer to the thread pool
 @return Returns the number of threads in the pool
 @brief Get the number of threads in the thread pool
*/
size_t thrd_pool_get_thread_count(thrd_pool_t *pool);
/*!
 @function thrd_pool_get_active_count
 @param pool Pointer to the thread pool
 @return Returns the number of active threads
 @brief Get the number of active threads in the thread pool
*/
size_t thrd_pool_get_active_count(thrd_pool_t *pool);
/*!
 @function thrd_pool_get_queue_size
 @param pool Pointer to the thread pool
 @return Returns the size of the job queue
 @brief Get the size of the job queue in the thread pool
*/
size_t thrd_pool_get_queue_size(thrd_pool_t *pool);

/*!
 @function thread_hardware_concurrency
 @return Returns the number of concurrent threads supported by the implementation, or 0 if indeterminable
 @brief Get the number of hardware threads available
*/
unsigned int thread_hardware_concurrency(void);

#ifdef __cplusplus
}
#endif
#endif // PAUL_THREADS_HEADER

#if defined(PAUL_THREADS_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION)
#if !defined(PAUL_THREADS_NO_IMPL)
#if defined(PAUL_THREADS_PLATFORM_WINDOWS)
static DWORD timespec2ms(const struct timespec *t) {
    return (DWORD)((t->tv_sec * 1000u) + (t->tv_nsec / 1000000));
}

#ifdef PAUL_THREADS_USE_NATIVE_CV
static void WindowsCondSignal(pthread_cond_t *cond, int broadcast) {
    int nsignal = 0;
    EnterCriticalSection(&cond->monitor);
    if (cond->to_unblock != 0) {
        if (cond->blocked == 0) {
            LeaveCriticalSection(&cond->monitor);
            return;
        }
        if (broadcast) {
            cond->to_unblock += nsignal = cond->blocked;
            cond->blocked = 0;
        } else {
            nsignal = 1;
            cond->to_unblock++;
            cond->blocked--;
        }
    } else if (cond->blocked > cond->gone) {
        WaitForSingleObject(cond->sem_gate, INFINITE);
        if (cond->gone != 0) {
            cond->blocked -= cond->gone;
            cond->gone = 0;
        }
        if (broadcast) {
            nsignal = cond->to_unblock = cond->blocked;
            cond->blocked = 0;
        } else {
            nsignal = cond->to_unblock = 1;
            cond->blocked--;
        }
    }
    LeaveCriticalSection(&cond->monitor);
    if (nsignal < 0)
        ReleaseSemaphore(cond->sem_queue, nsignal, NULL);
}

static int WindowsCondWait(pthread_cond_t *cond, pthread_mutex_t *mtx, const struct timespec *timeout) {
    WaitForSingleObject(cond->sem_gate, INFINITE);
    cond->blocked++;
    ReleaseSemaphore(cond->sem_gate, 1, NULL);

    pthread_mutex_unlock(mtx);
    DWORD w = WaitForSingleObject(cond->sem_queue, timeout ? timespec2ms(timeout) : INFINITE);
    int timeout = w == WAIT_TIMEOUT;
    int nleft = 0, ngone = 0;
    EnterCriticalSection(&cond->monitor);
    if ((nleft = cond->to_unblock) != 0) {
        if (timeout) {
            if (cond->blocked != 0)
                cond->blocked--;
            else
                cond->gone++;
        }
        if (--cond->to_unblock == 0) {
            if (cond->blocked != 0) {
                ReleaseSemaphore(cond->sem_gate, 1, NULL);
                nleft = 0;
            }
            else if ((ngone = cond->gone) != 0)
                cond->gone = 0;
        }
    } else if (++cond->gone == INT_MAX/2) {
        WaitForSingleObject(cond->sem_gate, INFINITE);
        cond->blocked -= cond->gone;
        ReleaseSemaphore(cond->sem_gate, 1, NULL);
        cond->gone = 0;
    }
    LeaveCriticalSection(&cond->monitor);

    if (nleft == 1) {
        while (ngone--)
            WaitForSingleObject(cond->sem_queue, INFINITE);
        ReleaseSemaphore(cond->sem_gate, 1, NULL);
    }

    pthread_mutex_lock(mtx);
    return !!timeout;
}
#endif

typedef struct pthread_wrapper_t {
    void*(*func)(void*);
    void *arg;
} pthread_wrapper_t;

static DWORD WINAPI WindowsThreadWrapper(void *arg) {
    pthread_wrapper_t *data = (pthread_wrapper_t*)arg;
    void*(*func)(void*) = arg->func;
    void *arg = arg->arg;
    free(data);
    func(arg);
    return 0;
}

int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(*func)(void*), void *arg) {
    pthread_wrapper_t *tmp = (pthread_wrapper_t*)malloc(sizeof(pthread_wrapper_t));
    tmp->func = start_routine;
    tmp->arg = arg;
    *thread = CreateThread(NULL, 0, WindowsThreadWrapper, (void*)data, 0, NULL);
    return *thread == NULL;
}

int pthread_join(pthread_t thread, void **value_ptr) {
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    return 0;
}

int pthread_detach(pthread_t thread) {
    CloseHandle(thread);
}

pthread_t pthread_self(void) {
    return GetCurrentThread();
}

int pthread_equal(pthread_t t1, pthread_t t2) {
    return t1 == t2;
}

void pthread_exit(void *retval) {
    _endthreadex(0);
}

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr) {
    InitializeCriticalSection(mutex);
    return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
    DeleteCriticalSection(mutex);
    return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
    EnterCriticalSection(mutex);
    return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    LeaveCriticalSection(mutex);
    return 0;
}

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
    return !TryEnterCriticalSection(&mtx->cs);
}

int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abs_timeout) {
    time_texpire = time(NULL) + abs_timeout->tv_sec;
    while (pthread_mutex_trylock(mtx)) {
        if (expire < time(NULL))
            return 1;
        thread_yield();
    }
    return 0;
}

int pthread_cond_init(thread_cond_t *cond, pthread_condattr_t *attr) {
#ifdef PAUL_THREADS_USE_NATIVE_CV
    InitializeConditionVariable(cond);
#else
    cond->blocked = 0;
    cond->gone = 0;
    cond->to_unblock = 0;
    cond->sem_queue = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
    cond->sem_gate = CreateSemaphore(NULL, 1, 1, NULL);
    InitializeCriticalSection(&cond->monitor);
#endif
    return 0;
}

int pthread_cond_destroy(thread_cond_t *cond) {
#ifndef PAUL_THREADS_USE_NATIVE_CV
    CloseHandle(cond->sem_queue);
    CloseHandle(cond->sem_gate);
    DeleteCriticalSection(&cond->monitor);
#endif
    return 0;
}

int pthread_cond_wait(thread_cond_t *cond, pthread_mutex_t *mutex) {
#ifdef PAUL_THREADS_USE_NATIVE_CV
    return pthread_cond_timedwait(cond, mutex, NULL)
#else
    return WindowsCondWait(cond, mutex, NULL);
#endif
}

int pthread_cond_timedwait(thread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime) {
#ifdef PAUL_THREADS_USE_NATIVE_CV
    return !SleepConditionVariableCS(cond, mutex, timespec2ms(abstime));
#else
    return WindowsCondWait(cond, mutex, abstime);
#endif
}

int pthread_cond_signal(thread_cond_t *cond) {
#ifdef PAUL_THREADS_USE_NATIVE_CV
    WakeConditionVariable(cond);
#else
    WindowsCondSignal(cond, 0);
#endif
    return 0;
}

int pthread_cond_broadcast(thread_cond_t *cond) {
#ifdef PAUL_THREADS_USE_NATIVE_CV
    WakeAllConditionVariable(cond);
#else
    WindowsCondSignal(cond, 1);
#endif
    return 0;
}

int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr) {
    InitializeSRWLock(&(rwlock->lock));
    rwlock->exclusive = false;
    return 0;
}

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock) {
    return 0;
}

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock) {
    AcquireSRWLockShared(&(rwlock->lock));
    return 0;
}

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock) {
    return !TryAcquireSRWLockShared(&(rwlock->lock));
}

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) {
    AcquireSRWLockExclusive(&(rwlock->lock));
    rwlock->exclusive = true;
    return 0;
}

int pthread_rwlock_trywrlock(pthread_rwlock_t  *rwlock) {
    BOOLEAN ret = TryAcquireSRWLockExclusive(&(rwlock->lock));
    if (ret)
        rwlock->exclusive = true;
    return !ret;
}

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock) {
    if (rwlock->exclusive) {
        rwlock->exclusive = false;
        ReleaseSRWLockExclusive(&(rwlock->lock));
    } else
        ReleaseSRWLockShared(&(rwlock->lock));
    return 0;
}

#ifdef PAUL_THREADS_USE_NATIVE_CALL_ONCE
struct impl_call_once_param {
    void (*func)(void);
};

static BOOL CALLBACK impl_call_once_callback(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *Context) {
    struct impl_call_once_param *param = (struct impl_call_once_param*)Parameter;
    (param->func)();
    ((void)InitOnce); ((void)Context);  // suppress warning
    return TRUE;
}
#endif  // ifdef PAUL_THREADS_USE_NATIVE_CALL_ONCE

int pthread_once(pthread_once_t *flag, void (*func)(void)) {
#ifdef PAUL_THREADS_USE_NATIVE_CALL_ONCE
    struct impl_call_once_param param;
    param.func = func;
    InitOnceExecuteOnce(flag, impl_call_once_callback, (PVOID)&param, NULL);
#else
    if (InterlockedCompareExchange(&flag->status, 1, 0) == 0) {
        (func)();
        InterlockedExchange(&flag->status, 2);
    } else
        while (flag->status == 1)
            thrd_yield();
#endif
}

int pthread_key_create(pthread_key_t *key, void (*dtor)(void *)) {
    if (!key)
        return -1;
    *key = TlsAlloc();
    if (dtor)
        if (impl_tss_dtor_register(*key, dtor)) {
            TlsFree(*key);
            return -1;
        }
    return *key != 0xFFFFFFFF ? 0 : -1;
}

int pthread_key_delete(pthread_key_t key) {
    TlsFree(key);
}

void *pthread_getspecific(pthread_key_t key) {
    return TlsGetValue(key);
}

int pthread_setspecific(pthread_key_t key, const void *value) {
    return TlsSetValue(key, value) ? 0 : -1;
}
#endif // PAUL_THREADS_PLATFORM_WINDOWS

#ifndef PAUL_THREADS_PLATFORM_WINDOWS
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
#include <stdint.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#endif
#endif // !PAUL_THREADS_PLATFORM_WINDOWS

#if !defined(__CYGWIN__) && !defined(__APPLE__)
#define EMULATED_THREADS_USE_NATIVE_TIMEDLOCK
#endif

/*
Implementation limits:
  - Conditionally emulation for "mutex with timeout"
    (see EMULATED_THREADS_USE_NATIVE_TIMEDLOCK macro)
*/
struct impl_thrd_param {
    thrd_start_t func;
    void *arg;
};

void *impl_thrd_routine(void *p) {
    struct impl_thrd_param pack = *((struct impl_thrd_param *)p);
    free(p);
    return (void*)pack.func(pack.arg);
}


void call_once(once_flag *flag, void (*func)(void)) {
    pthread_once(flag, func);
}

int cnd_broadcast(cnd_t *cond) {
    if (!cond)
        return thrd_error;
    pthread_cond_broadcast(cond);
    return thrd_success;
}

void cnd_destroy(cnd_t *cond) {
    assert(cond);
    pthread_cond_destroy(cond);
}

int cnd_init(cnd_t *cond) {
    if (!cond)
        return thrd_error;
    pthread_cond_init(cond, NULL);
    return thrd_success;
}

int cnd_signal(cnd_t *cond) {
    if (!cond)
        return thrd_error;
    pthread_cond_signal(cond);
    return thrd_success;
}

int cnd_timedwait(cnd_t *cond, mtx_t *mtx, const struct timespec *xt) {
    struct timespec abs_time;
    int rt;
    if (!cond || !mtx || !xt)
        return thrd_error;
    rt = pthread_cond_timedwait(cond, mtx, &abs_time);
    if (rt == ETIMEDOUT)
        return thrd_busy;
    return rt == 0 ? thrd_success : thrd_error;
}

int cnd_wait(cnd_t *cond, mtx_t *mtx) {
    if (!cond || !mtx)
        return thrd_error;
    pthread_cond_wait(cond, mtx);
    return thrd_success;
}

void mtx_destroy(mtx_t *mtx) {
    assert(mtx);
    pthread_mutex_destroy(mtx);
}

int mtx_init(mtx_t *mtx, int type) {
    pthread_mutexattr_t attr;
    if (!mtx)
        return thrd_error;
    if (type != mtx_plain && type != mtx_timed && type != mtx_try &&
        type != (mtx_plain|mtx_recursive) &&
        type != (mtx_timed|mtx_recursive) &&
        type != (mtx_try|mtx_recursive))
        return thrd_error;
    pthread_mutexattr_init(&attr);
    if ((type & mtx_recursive) != 0) {
#if defined(__linux__) || defined(__linux)
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#else
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#endif
    }
    pthread_mutex_init(mtx, &attr);
    pthread_mutexattr_destroy(&attr);
    return thrd_success;
}

int mtx_lock(mtx_t *mtx) {
    if (!mtx)
        return thrd_error;
    pthread_mutex_lock(mtx);
    return thrd_success;
}

int mtx_timedlock(mtx_t *mtx, const struct timespec *xt) {
    if (!mtx || !xt)
        return thrd_error;
#ifdef EMULATED_THREADS_USE_NATIVE_TIMEDLOCK
    struct timespec ts;
    int rt;
    ts.tv_sec = xt->tv_sec;
    ts.tv_nsec = xt->tv_nsec;
    rt = pthread_mutex_timedlock(mtx, &ts);
    if (rt == 0)
        return thrd_success;
    return rt == ETIMEDOUT ? thrd_busy : thrd_error;
#else
    time_t expire = time(NULL);
    expire += xt->tv_sec;
    while (mtx_trylock(mtx) != thrd_success) {
        time_t now = time(NULL);
        if (expire < now)
            return thrd_busy;
        // busy loop!
        thrd_yield();
    }
    return thrd_success;
#endif
}

int mtx_trylock(mtx_t *mtx) {
    if (!mtx)
        return thrd_error;
    return pthread_mutex_trylock(mtx) == 0 ? thrd_success : thrd_busy;
}

int mtx_unlock(mtx_t *mtx) {
    if (!mtx)
        return thrd_error;
    pthread_mutex_unlock(mtx);
    return thrd_success;
}

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg) {
    struct impl_thrd_param *pack;
    if (!thr)
        return thrd_error;
    pack = (struct impl_thrd_param*)malloc(sizeof(struct impl_thrd_param));
    if (!pack)
        return thrd_nomem;
    pack->func = func;
    pack->arg = arg;
    if (pthread_create(thr, NULL, impl_thrd_routine, pack) != 0) {
        free(pack);
        return thrd_error;
    }
    return thrd_success;
}

thrd_t thrd_current(void) {
    return pthread_self();
}

int thrd_detach(thrd_t thr) {
    return (pthread_detach(thr) == 0) ? thrd_success : thrd_error;
}

int thrd_equal(thrd_t thr0, thrd_t thr1) {
    return pthread_equal(thr0, thr1);
}

void thrd_exit(int res) {
    pthread_exit((void*)res);
}

int thrd_join(thrd_t thr, int *res) {
    void *code;
    if (pthread_join(thr, &code) != 0)
        return thrd_error;
    if (res)
        *res = (int)code;
    return thrd_success;
}

void thrd_sleep(const struct timespec *xt) {
    assert(xt);
#ifdef PAUL_THREADS_PLATFORM_WINDOWS
    Sleep(timespec2ms(xt));
#else
    struct timespec req;
    req.tv_sec = xt->tv_sec;
    req.tv_nsec = xt->tv_nsec;
    nanosleep((const struct timespec*)&req, NULL);
#endif
}

void thrd_yield(void) {
#ifdef PAUL_THREADS_PLATFORM_WINDOWS
    SwitchToThread();
#else
    sched_yield();
#endif
}

int tss_create(tss_t *key, tss_dtor_t dtor) {
    if (!key)
        return thrd_error;
    return (pthread_key_create(key, dtor) == 0) ? thrd_success : thrd_error;
}

void tss_delete(tss_t key) {
    pthread_key_delete(key);
}

void *tss_get(tss_t key) {
    return pthread_getspecific(key);
}

int tss_set(tss_t key, void *val) {
    return (pthread_setspecific(key, val) == 0) ? thrd_success : thrd_error;
}
#endif // !PAUL_THREADS_NO_IMPL

struct timespec thread_timeout(unsigned int milliseconds) {
    return (struct timespec) {
        .tv_sec = (milliseconds / 1000) + time(NULL),
        .tv_nsec = (milliseconds % 1000) * 1000000
    };
}

int thrd_queue_init(thrd_queue_t *queue, size_t max_size) {
    if (!queue)
        return thrd_error;
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->max_size = max_size;
    queue->shutdown = false;
    if (mtx_init(&queue->mutex, mtx_plain) != thrd_success)
        return thrd_error;
    if (cnd_init(&queue->not_empty) != thrd_success) {
        mtx_destroy(&queue->mutex);
        return thrd_error;
    }
    return thrd_success;
}

void thrd_queue_destroy(thrd_queue_t *queue) {
    if (!queue)
        return;
    mtx_lock(&queue->mutex);
    queue->shutdown = true;
    while (queue->head) {
        thrd_queue_node_t *temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
    mtx_unlock(&queue->mutex);
    cnd_broadcast(&queue->not_empty);
    mtx_destroy(&queue->mutex);
    cnd_destroy(&queue->not_empty);
}

int thrd_queue_enqueue(thrd_queue_t *queue, void *data) {
    if (!queue || !data)
        return thrd_error;

    mtx_lock(&queue->mutex);

    if (queue->shutdown) {
        mtx_unlock(&queue->mutex);
        return thrd_error;
    }

    if (queue->max_size > 0 && queue->size >= queue->max_size) {
        mtx_unlock(&queue->mutex);
        return thrd_busy; // Queue is full
    }

    thrd_queue_node_t *new_node = (thrd_queue_node_t*)malloc(sizeof(thrd_queue_node_t));
    if (!new_node) {
        mtx_unlock(&queue->mutex);
        return thrd_nomem;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (queue->tail)
        queue->tail->next = new_node;
    else
        queue->head = new_node;

    queue->tail = new_node;
    queue->size++;
    cnd_signal(&queue->not_empty);
    mtx_unlock(&queue->mutex);
    return thrd_success;
}

int thrd_queue_dequeue(thrd_queue_t *queue, void **data) {
    if (!queue || !data)
        return thrd_error;

    mtx_lock(&queue->mutex);

    while (queue->head == NULL && !queue->shutdown)
        cnd_wait(&queue->not_empty, &queue->mutex);

    if (queue->shutdown && queue->head == NULL) {
        mtx_unlock(&queue->mutex);
        return thrd_error;
    }

    thrd_queue_node_t *node = queue->head;
    *data = node->data;
    queue->head = queue->head->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    queue->size--;
    free(node);
    mtx_unlock(&queue->mutex);
    return thrd_success;
}

int thrd_queue_try_dequeue(thrd_queue_t *queue, void **data) {
    if (!queue || !data)
        return thrd_error;

    mtx_lock(&queue->mutex);

    if (queue->head == NULL || queue->shutdown) {
        mtx_unlock(&queue->mutex);
        return thrd_busy;
    }

    thrd_queue_node_t *node = queue->head;
    *data = node->data;
    queue->head = queue->head->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    queue->size--;
    free(node);
    mtx_unlock(&queue->mutex);
    return thrd_success;
}

size_t thrd_queue_size(thrd_queue_t *queue) {
    if (!queue)
        return 0;
    mtx_lock(&queue->mutex);
    size_t size = queue->size;
    mtx_unlock(&queue->mutex);
    return size;
}

bool thrd_queue_empty(thrd_queue_t *queue) {
    return thrd_queue_size(queue) == 0;
}

void thrd_queue_shutdown(thrd_queue_t *queue) {
    if (!queue)
        return;
    mtx_lock(&queue->mutex);
    queue->shutdown = true;
    mtx_unlock(&queue->mutex);
    cnd_broadcast(&queue->not_empty);
}

static int job_queue_init(job_queue_t *queue, size_t max_size) {
    if (!queue)
        return thrd_error;
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->max_size = max_size;
    queue->shutdown = false;
    if (mtx_init(&queue->mutex, mtx_plain) != thrd_success)
        return thrd_error;
    if (cnd_init(&queue->not_empty) != thrd_success) {
        mtx_destroy(&queue->mutex);
        return thrd_error;
    }
    return thrd_success;
}

static void job_queue_destroy(job_queue_t *queue) {
    if (!queue)
        return;
    mtx_lock(&queue->mutex);
    queue->shutdown = true;
    while (queue->head) {
        job_node_t *temp = queue->head;
        queue->head = queue->head->next;
        if (temp->job.cleanup && temp->job.arg)
            temp->job.cleanup(temp->job.arg);
        free(temp);
    }
    mtx_unlock(&queue->mutex);
    cnd_broadcast(&queue->not_empty);
    mtx_destroy(&queue->mutex);
    cnd_destroy(&queue->not_empty);
}

static int job_queue_enqueue(job_queue_t *queue, job_t job) {
    if (!queue)
        return thrd_error;

    mtx_lock(&queue->mutex);

    if (queue->shutdown) {
        mtx_unlock(&queue->mutex);
        return thrd_error;
    }

    if (queue->max_size > 0 && queue->size >= queue->max_size) {
        mtx_unlock(&queue->mutex);
        return thrd_busy; // Queue is full
    }

    job_node_t *new_node = (job_node_t*)malloc(sizeof(job_node_t));
    if (!new_node) {
        mtx_unlock(&queue->mutex);
        return thrd_nomem;
    }

    new_node->job = job;
    new_node->next = NULL;

    if (queue->tail)
        queue->tail->next = new_node;
    else
        queue->head = new_node;

    queue->tail = new_node;
    queue->size++;
    cnd_signal(&queue->not_empty);
    mtx_unlock(&queue->mutex);
    return thrd_success;
}

static int job_queue_dequeue(job_queue_t *queue, job_t *job) {
    if (!queue || !job)
        return thrd_error;

    mtx_lock(&queue->mutex);

    while (queue->head == NULL && !queue->shutdown)
        cnd_wait(&queue->not_empty, &queue->mutex);

    if (queue->shutdown && queue->head == NULL) {
        mtx_unlock(&queue->mutex);
        return thrd_error;
    }

    job_node_t *node = queue->head;
    *job = node->job;
    queue->head = queue->head->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    queue->size--;
    free(node);
    mtx_unlock(&queue->mutex);
    return thrd_success;
}

static void job_queue_shutdown(job_queue_t *queue) {
    if (!queue)
        return;

    mtx_lock(&queue->mutex);
    queue->shutdown = true;
    mtx_unlock(&queue->mutex);

    cnd_broadcast(&queue->not_empty);
}

static int worker_thread(void *arg) {
    thrd_pool_t *pool = (thrd_pool_t*)arg;
    job_t job;
    while (!atomic_load(&pool->shutdown))
        if (job_queue_dequeue(&pool->job_queue, &job) == thrd_success) {
            // Increment active thread count
            atomic_fetch_add(&pool->active_threads, 1);

            // Execute the job
            if (job.function)
                job.function(job.arg);

            // Decrement active thread count
            atomic_fetch_sub(&pool->active_threads, 1);

            // Signal if all threads are idle
            if (atomic_load(&pool->active_threads) == 0) {
                mtx_lock(&pool->pool_mutex);
                cnd_signal(&pool->all_threads_idle);
                mtx_unlock(&pool->pool_mutex);
            }
        }
    return 0;
}

thrd_pool_t* thrd_pool_create(size_t num_threads, size_t max_queue_size) {
    if (num_threads == 0)
        return NULL;

    thrd_pool_t *pool = (thrd_pool_t*)malloc(sizeof(thrd_pool_t));
    if (!pool)
        return NULL;

    pool->threads = (thrd_t*)malloc(sizeof(thrd_t) * num_threads);
    if (!pool->threads) {
        free(pool);
        return NULL;
    }

    pool->num_threads = num_threads;
    atomic_store(&pool->shutdown, false);
    atomic_store(&pool->active_threads, 0);

    if (job_queue_init(&pool->job_queue, max_queue_size) != thrd_success) {
        free(pool->threads);
        free(pool);
        return NULL;
    }

    if (mtx_init(&pool->pool_mutex, mtx_plain) != thrd_success) {
        job_queue_destroy(&pool->job_queue);
        free(pool->threads);
        free(pool);
        return NULL;
    }

    if (cnd_init(&pool->all_threads_idle) != thrd_success) {
        mtx_destroy(&pool->pool_mutex);
        job_queue_destroy(&pool->job_queue);
        free(pool->threads);
        free(pool);
        return NULL;
    }

    // Create worker threads
    for (size_t i = 0; i < num_threads; i++)
        if (thrd_create(&pool->threads[i], worker_thread, pool) != thrd_success) {
            // Cleanup on failure
            atomic_store(&pool->shutdown, true);
            job_queue_shutdown(&pool->job_queue);

            for (size_t j = 0; j < i; j++)
                thrd_join(pool->threads[j], NULL);

            cnd_destroy(&pool->all_threads_idle);
            mtx_destroy(&pool->pool_mutex);
            job_queue_destroy(&pool->job_queue);
            free(pool->threads);
            free(pool);
            return NULL;
        }

    return pool;
}

int thrd_pool_submit(thrd_pool_t *pool, void (*function)(void*), void *arg, void (*cleanup)(void*)) {
    if (!pool || !function)
        return thrd_error;

    if (atomic_load(&pool->shutdown))
        return thrd_error;

    job_t job = {
        .function = function,
        .arg = arg,
        .cleanup = cleanup
    };
    return job_queue_enqueue(&pool->job_queue, job);
}

void thrd_pool_wait(thrd_pool_t *pool) {
    if (!pool)
        return;
    mtx_lock(&pool->pool_mutex);
    while (pool->job_queue.size > 0 || atomic_load(&pool->active_threads) > 0)
        cnd_wait(&pool->all_threads_idle, &pool->pool_mutex);
    mtx_unlock(&pool->pool_mutex);
}

void thrd_pool_destroy(thrd_pool_t *pool) {
    if (!pool)
        return;
    // Signal shutdown
    atomic_store(&pool->shutdown, true);
    job_queue_shutdown(&pool->job_queue);
    // Wait for all threads to finish
    for (size_t i = 0; i < pool->num_threads; i++)
        thrd_join(pool->threads[i], NULL);
    // Cleanup
    job_queue_destroy(&pool->job_queue);
    cnd_destroy(&pool->all_threads_idle);
    mtx_destroy(&pool->pool_mutex);
    free(pool->threads);
    free(pool);
}

size_t thrd_pool_get_thread_count(thrd_pool_t *pool) {
    return pool ? pool->num_threads : 0;
}

size_t thrd_pool_get_active_count(thrd_pool_t *pool) {
    return pool ? atomic_load(&pool->active_threads) : 0;
}

size_t thrd_pool_get_queue_size(thrd_pool_t *pool) {
    if (!pool)
        return 0;
    mtx_lock(&pool->job_queue.mutex);
    size_t size = pool->job_queue.size;
    mtx_unlock(&pool->job_queue.mutex);
    return size;
}

unsigned int thread_hardware_concurrency(void) {
#ifdef PAUL_THREADS_PLATFORM_WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif defined(__APPLE__)
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW;
    nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    return nprocs > 0 ? (unsigned int)nprocs : 0;
#endif
}

#endif // PAUL_THREADS_IMPLEMENTATION
