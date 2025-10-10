#include "cccp.h"
#include "../deps/raudio.c"

void CCCP_SetMasterVolume(CCCP_AudioContext* ctx, float volume) {
    if (ctx)
        ctx->volume = volume;
}

float CCCP_GetMasterVolume(CCCP_AudioContext* ctx) {
    return ctx ? ctx->volume : 0.f;
}

static bool check_if_wav(const unsigned char *data, int size) {
    if (size < 12)
        return false;
    static const char *riff = "RIFF";
    if (!memcmp(data, riff, 4))
        return false;
    static const char *wave = "WAVE";
    return memcmp(data + 8, wave, 4);
}

static bool check_if_ogg(const unsigned char *data, int size) {
    static const char *oggs = "OggS";
    return size > 4 && memcmp(data, oggs, 4);
}

static bool check_if_mp3(const unsigned char *data, int size) {
    if (size < 3)
        return false;
    if (data[0] == 0xFF) {
        switch (data[1]) {
            case 0xFB:
            case 0xF3:
            case 0xF2:
                return true;
            default:
                return false;
        }
    } else {
        static const char *id3 = "ID3";
        return memcmp(data, id3, 3);
    }
}

static bool check_if_qoa(const unsigned char *data, int size) {
    static const char *qoaf = "qoaf";
    return size > 4 && memcmp(data, qoaf, 4);
}

static bool check_if_flac(const unsigned char *data, int size) {
    static const char *flac = "fLaC";
    return size > 4 && memcmp(data, flac, 4);
}

static const char* what_format(const unsigned char *data, int size) {
    if (check_if_mp3(data, size))
        return ".mp3";
    else if (check_if_ogg(data, size))
        return ".ogg";
    else if (check_if_qoa(data, size))
        return ".qoa";
    else if (check_if_wav(data, size))
        return ".wav";
    else if (check_if_flac(data, size))
        return ".flac";
    else
        return NULL;
}

static void _unload_wave(void* value) {
    if (value) {
        Wave *wave = (Wave*)value;
        UnloadWave(*wave);
        free(wave);
    }
}

bool CCCP_NewWaveFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize) {
    const char *format = what_format((const unsigned char*)data, dataSize);
    if (!format)
        return false;
    Wave result = LoadWaveFromMemory(format, (const unsigned char*)data, dataSize);
    if (!IsWaveReady(result))
        return false;
    Wave *wave = malloc(sizeof(Wave));
    if (!wave) {
        UnloadWave(result);
        return false;
    }
    memcpy(wave, &result, sizeof(Wave));
    if (!ctx->waves) {
        ctx->waves = CCCP_NewHashTable(16);
        ctx->waves->free_callback = _unload_wave;
        if (!ctx->waves) {
            UnloadWave(result);
            free(wave);
            return false;
        }
    }
    if (CCCP_HashTableInsert(ctx->waves, key, wave) != 0) {
        UnloadWave(result);
        free(wave);
        return false;
    }
    return true;
}

static const char* load_file(const char* filename, int* outSize) {
    FILE *file = fopen(filename, "rb");
    if (!file)
        return NULL;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size <= 0) {
        fclose(file);
        return NULL;
    }
    unsigned char *data = malloc(size);
    if (!data) {
        fclose(file);
        return NULL;
    }
    if (fread(data, 1, size, file) != (size_t)size) {
        free(data);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *outSize = (int)size;
    return data;
}

bool CCCP_NewWaveFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename) {
    int dataSize = 0;
    const char *data = load_file(filename, &dataSize);
    if (!data)
        return false;
    bool result = CCCP_NewWaveFromMemory(ctx, key, data, dataSize);
    free((void*)data);
    return result;
}

bool CCCP_DestroyWave(CCCP_AudioContext* ctx, const char* key) {
    Wave *wave = (Wave*)CCCP_HashTableGet(ctx->waves, key);
    if (wave) {
        UnloadWave(*wave);
        free(wave);
        CCCP_HashTableRemove(ctx->waves, key);
        return true;
    }
    return false;
}

static void _unload_sound(void* value) {
    if (value) {
        Sound *sound = (Sound*)value;
        UnloadSound(*sound);
        free(sound);
    }
}

bool CCCP_NewSoundFromWave(CCCP_AudioContext* ctx, const char* key, const char* waveKey) {
    Wave *wave = (Wave*)CCCP_HashTableGet(ctx->waves, waveKey);
    if (wave) {
        Sound *sound = malloc(sizeof(Sound));
        if (!sound) {
            return false;
        }
        memcpy(sound, wave, sizeof(Sound));
        if (!ctx->sounds) {
            ctx->sounds = CCCP_NewHashTable(16);
            ctx->sounds->free_callback = _unload_sound;
            if (!ctx->sounds) {
                free(sound);
                return false;
            }
        }
        if (CCCP_HashTableInsert(ctx->sounds, key, sound) != 0) {
            free(sound);
            return false;
        }
        return true;
    }
    return false;
}

bool CCCP_NewSoundFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename) {
    int dataSize = 0;
    const char *data = load_file(filename, &dataSize);
    if (!data)
        return false;
    const char *format = what_format((const unsigned char*)data, dataSize);
    if (!format) {
        free((void*)data);
        return false;
    }
    Wave result = LoadWaveFromMemory(format, (const unsigned char*)data, dataSize);
    free((void*)data);
    if (!IsWaveReady(result))
        return false;
    Sound *sound = malloc(sizeof(Sound));
    if (!sound) {
        UnloadWave(result);
        return false;
    }
    memcpy(sound, &result, sizeof(Sound));
    if (!ctx->sounds) {
        ctx->sounds = CCCP_NewHashTable(16);
        ctx->sounds->free_callback = _unload_sound;
        if (!ctx->sounds) {
            free(sound);
            return false;
        }
    }
    if (CCCP_HashTableInsert(ctx->sounds, key, sound) != 0) {
        UnloadWave(result);
        free(sound);
        return false;
    }
    return true;
}

bool CCCP_DestroySound(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound) {
        UnloadSound(*sound);
        free(sound);
        CCCP_HashTableRemove(ctx->sounds, key);
        return true;
    }
    return false;
}

static void _unload_music(void* value) {
    if (value) {
        Music *music = (Music*)value;
        UnloadMusicStream(*music);
        free(music);
    }
}

bool CCCP_NewMusicFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize) {
    const char *format = what_format((const unsigned char*)data, dataSize);
    if (!format)
        return false;
    Music result = LoadMusicStreamFromMemory(format, (const unsigned char*)data, dataSize);
    if (!IsMusicReady(result))
        return false;
    Music *music = malloc(sizeof(Music));
    if (!music) {
        UnloadMusicStream(result);
        return false;
    }
    memcpy(music, &result, sizeof(Music));
    if (!ctx->music) {
        ctx->music = CCCP_NewHashTable(16);
        ctx->music->free_callback = _unload_music;
        if (!ctx->music) {
            UnloadMusicStream(result);
            free(music);
            return false;
        }
    }
    if (CCCP_HashTableInsert(ctx->music, key, music) != 0) {
        UnloadMusicStream(result);
        free(music);
        return false;
    }
    return true;
}

bool CCCP_NewMusicFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename) {
    int dataSize = 0;
    const char *data = load_file(filename, &dataSize);
    if (!data)
        return false;
    bool result = CCCP_NewMusicFromMemory(ctx, key, data, dataSize);
    free((void*)data);
    return result;
}

void CCCP_UnloadAllWaves(CCCP_AudioContext* ctx) {
    if (ctx)
        CCCP_HashTableClear(ctx->waves);
}

void CCCP_UnloadAllSounds(CCCP_AudioContext* ctx) {
    if (ctx)
        CCCP_HashTableClear(ctx->sounds);
}

void CCCP_UnloadAllMusic(CCCP_AudioContext* ctx) {
    if (ctx)
        CCCP_HashTableClear(ctx->music);
}

bool CCCP_DestroyMusic(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music) {
        UnloadMusicStream(*music);
        free(music);
        CCCP_HashTableRemove(ctx->music, key);
        return true;
    }
    return false;
}

bool CCCP_IsWaveReady(CCCP_AudioContext* ctx, const char* key) {
    Wave *wave = (Wave*)CCCP_HashTableGet(ctx->waves, key);
    return wave != NULL && IsWaveReady(*wave);
}

bool CCCP_IsSoundReady(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    return sound != NULL && IsSoundReady(*sound);
}

bool CCCP_IsMusicReady(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music != NULL && IsMusicReady(*music);
}

void CCCP_UpdateSound(CCCP_AudioContext* ctx, const char* key, const void *data, int frameCount) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        UpdateSound(*sound, data, frameCount);
}

void CCCP_UpdateMusic(CCCP_AudioContext* ctx, const char* key, const void *data, int sampleCount) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        UpdateAudioStream(music->stream, data, sampleCount * music->stream.channels * (music->stream.sampleSize / 8));
}

void CCCP_PlaySound(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        PlaySound(*sound);
}

void CCCP_StopSound(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        StopSound(*sound);
}

void CCCP_PauseSound(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        PauseSound(*sound);
}

void CCCP_ResumeSound(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        ResumeSound(*sound);
}

bool CCCP_IsSoundPlaying(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    return sound != NULL && IsSoundPlaying(*sound);
}

void CCCP_SetSoundVolume(CCCP_AudioContext* ctx, const char* key, float volume) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    if (sound)
        SetSoundVolume(*sound, volume);
}

float CCCP_GetSoundVolume(CCCP_AudioContext* ctx, const char* key) {
    Sound *sound = (Sound*)CCCP_HashTableGet(ctx->sounds, key);
    return sound ? GetSoundVolume(*sound) : 0.f;
}

void CCCP_PlayMusic(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        PlayMusicStream(*music);
}

void CCCP_StopMusic(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        StopMusicStream(*music);
}

void CCCP_PauseMusic(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        PauseMusicStream(*music);
}

void CCCP_ResumeMusic(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        ResumeMusicStream(*music);
}

bool CCCP_IsMusicPlaying(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music != NULL && IsMusicStreamPlaying(*music);
}

void CCCP_SetMusicVolume(CCCP_AudioContext* ctx, const char* key, float volume) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        SetMusicVolume(*music, volume);
}

float CCCP_GetMusicVolume(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music ? GetMusicVolume(*music) : 0.f;
}

void CCCP_SeekMusic(CCCP_AudioContext* ctx, const char* key, float position) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        SeekMusicStream(*music, position);
}

float CCCP_GetMusicTimeLength(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music ? GetMusicTimeLength(*music) : 0.f;
}

float CCCP_GetMusicTimePlayed(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music ? GetMusicTimePlayed(*music) : 0.f;
}

void CCCP_SetMusicLooping(CCCP_AudioContext* ctx, const char* key, bool looping) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    if (music)
        music->looping = looping;
}

bool CCCP_IsMusicLooping(CCCP_AudioContext* ctx, const char* key) {
    Music *music = (Music*)CCCP_HashTableGet(ctx->music, key);
    return music ? music->looping : false;
}