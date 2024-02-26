#pragma once

namespace Nebel
{
    enum class AudioType
    {
        AudioSoundFX,
        AudioMusic,
    };
    struct Sound
    {
        AudioType type = AudioType::AudioMusic;
        const char* path;
        float volume;
    };
    struct AudioEngine // TODO: everything
    {
        void Init();
        void DeInit();
        void play(Sound &sound);
        void stop(Sound &sound);
    };
} // namespace Nebel
