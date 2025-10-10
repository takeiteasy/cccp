#include "cccp.h"
#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

typedef struct CCCP_Timer {
    double start_time;
    double paused_time;
    bool paused;
} CCCP_Timer;

static double CCCP_GetTime(void) {
#ifdef _WIN32
    static LARGE_INTEGER frequency = {0};
    if (frequency.QuadPart == 0)
        QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)frequency.QuadPart;
#elif defined(__APPLE__)
    static mach_timebase_info_data_t timebase_info = {0};
    if (timebase_info.denom == 0)
        mach_timebase_info(&timebase_info);
    uint64_t time = mach_absolute_time();
    return (double)time * (double)timebase_info.numer / (double)timebase_info.denom / 1000000000.0;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
#endif
}

void CCCP_Sleep(double seconds) {
#ifdef _WIN32
    Sleep((DWORD)(seconds * 1000.0));
#else
    struct timespec ts;
    ts.tv_sec = (time_t)seconds;
    ts.tv_nsec = (long)((seconds - (double)ts.tv_sec) * 1000000000.0);
    nanosleep(&ts, NULL);
#endif
}

CCCP_Timer* CCCP_NewTimer(void) {
    CCCP_Timer* timer = malloc(sizeof(CCCP_Timer));
    if (timer) {
        timer->start_time = 0.0;
        timer->paused_time = 0.0;
        timer->paused = false;
    }
    return timer;
}

void CCCP_DestroyTimer(CCCP_Timer* timer) {
    if (timer)
        free(timer);
}

void CCCP_StartTimer(CCCP_Timer* timer) {
    if (timer) {
        timer->start_time = CCCP_GetTime();
        timer->paused_time = 0.0;
        timer->paused = false;
    }
}

void CCCP_StopTimer(CCCP_Timer* timer) {
    if (timer) {
        timer->start_time = 0.0;
        timer->paused_time = 0.0;
        timer->paused = false;
    }
}

void CCCP_PauseTimer(CCCP_Timer* timer) {
    if (timer && !timer->paused) {
        timer->paused_time += CCCP_GetTime() - timer->start_time;
        timer->paused = true;
    }
}

void CCCP_ResumeTimer(CCCP_Timer* timer) {
    if (timer && timer->paused) {
        timer->start_time = CCCP_GetTime() - timer->paused_time;
        timer->paused = false;
    }
}

double CCCP_GetElapsedTime(CCCP_Timer* timer) {
    if (!timer)
        return 0.0;
    if (timer->paused)
        return timer->paused_time;
    else
        return CCCP_GetTime() - timer->start_time + timer->paused_time;
}