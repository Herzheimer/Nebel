#include "audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace Nebel
{
    ma_engine maEngine;
    void AudioEngine::Init()
    {
        ma_result result;

        result = ma_engine_init(NULL, &maEngine);
        if (result != MA_SUCCESS) {
            printf("nope");
            return;
        }
    }
    void AudioEngine::DeInit()
    {
        ma_engine_uninit(&maEngine);
    }
    void AudioEngine::play(Sound &sound)
    {
        ma_engine_play_sound(&maEngine, sound.path, NULL);
    }
}