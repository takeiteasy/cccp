#include "cccp.h"

CCCP_Shader CCCP_NewShader(CCCP_ShaderFunc func, int numThreads) {
    return (CCCP_Shader){
        .func = func,
        .pool = thrd_pool_create(numThreads ? numThreads : thread_hardware_concurrency(), 256)
    };
}

void CCCP_DestroyShader(CCCP_Shader shader) {
    thrd_pool_destroy(shader.pool);
    memset(&shader, 0, sizeof(CCCP_Shader));
}

void CCCP_ApplyShader(CCCP_Surface surface, CCCP_Shader shader, void* userdata) {
    // TODO: Implement shader application using the thread pool
    // Multi-threaded software renderer. Each pixel can be computed independently.
    // Divide the work into chunks and submit to the thread pool.
    // Join all threads before returning.
}