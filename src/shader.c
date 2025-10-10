/*
 CCCP - The C Create Coding Project

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
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "cccp.h"

#define CHUNK_WIDTH 64
#define CHUNK_HEIGHT 64

typedef struct {
    int x, y, w, h;
    void *userdata;
    CCCP_ShaderFunc func;
    CCCP_Surface surface;
} ShaderJob;

CCCP_Shader CCCP_NewShader(CCCP_ShaderFunc func, int numThreads) {
    return (CCCP_Shader){
        .func = func,
        .thread_count = numThreads <= 0 ? thread_hardware_concurrency() : numThreads
    };
}

void CCCP_DestroyShader(CCCP_Shader *shader) {
    memset(shader, 0, sizeof(CCCP_Shader));
}

static void CCCP_ShaderWorker(void *arg) {
    ShaderJob *job = (ShaderJob*)arg;
    int w = CCCP_SurfaceWidth(job->surface);
    int h = CCCP_SurfaceHeight(job->surface);
    for (int y = job->y; y < job->y + job->h && y < h; ++y)
        for (int x = job->x; x < job->x + job->w && x < w; ++x) {
            vec2 fragcoord = { (float)x + 0.5f, (float)y + 0.5f };
            vec2 resolution = { (float)w, (float)h };
            vec4 color = job->func(fragcoord, resolution, 0.f, job->userdata);
            // Convert normalized float color to uint8_t color
            color_t final = rgbaf_to_rgba((color_rgbaf_t){color[0], color[1], color[2], color[3]});
            CCCP_SetPixel(job->surface, x, y, final);
        }
    free(job);
}

bool CCCP_ApplyShader(CCCP_Surface surface, CCCP_Shader *shader, void* userdata) {
    thrd_pool_t *pool = thrd_pool_create(shader->thread_count <= 0 ? thread_hardware_concurrency() : shader->thread_count, 0);
    int w = CCCP_SurfaceWidth(surface);
    int h = CCCP_SurfaceHeight(surface);
    int nx = (w + CHUNK_WIDTH - 1) / CHUNK_WIDTH;
    int ny = (h + CHUNK_HEIGHT - 1) / CHUNK_HEIGHT;
    bool result = false;
    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            ShaderJob *job = malloc(sizeof(ShaderJob));
            if (!job)
                goto BAIL;
            job->x = i * CHUNK_WIDTH;
            job->y = j * CHUNK_HEIGHT;
            job->w = job->x + CHUNK_WIDTH > w ? w - job->x : CHUNK_WIDTH;
            job->h = job->y + CHUNK_HEIGHT > h ? h - job->y : CHUNK_HEIGHT;
            job->userdata = userdata;
            job->func = shader->func;
            job->surface = surface;
            thrd_pool_submit(pool, CCCP_ShaderWorker, job, NULL);
        }
    }
    result = true;
BAIL:
    thrd_pool_wait(pool);
    thrd_pool_destroy(pool);
    return result;
}