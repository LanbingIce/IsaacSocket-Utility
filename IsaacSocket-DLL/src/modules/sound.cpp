#include "module.hpp"
#include "state.hpp"
#include <mmsystem.h>
#undef PlaySound
#ifdef _MSC_VER
#pragma comment(lib, "Winmm.lib")
#endif

namespace sound {

static int StopPlayingSound(lua_State* L) {
    DWORD fuSound = SND_ASYNC | SND_MEMORY;
    ::PlaySoundA(nullptr, nullptr, fuSound);
    return 0;
}

static int PlaySoundFromMemory(lua_State* L) {
    ARG(1, stdstring, std::string, data);
    DWORD fuSound = SND_ASYNC | SND_MEMORY;
    ::PlaySoundA(data.data(), nullptr, fuSound);
    return 0;
}

static int PlaySoundFromFile(lua_State* L) {
    ARG(1, stdstring, std::string, filename);
    DWORD fuSound = SND_ASYNC | SND_FILENAME;
    ::PlaySoundW(utils::U8ToU16(filename).c_str(), nullptr, fuSound);
    return 0;
}

static int PlaySoundOfSystem(lua_State* L) {
    ARG(1, stdstring, std::string, name);
    DWORD fuSound = SND_ASYNC | SND_SYSTEM;
    ::PlaySoundA(name.c_str(), nullptr, fuSound);
    return 0;
}

static int PcmToWav(lua_State* L) {
    ARG(1, stdstring, std::string, pcmData);
    ARG(2, integer, int, sampleRate);
    ARG_DEF(3, integer, int, bits, 16);
    ARG_DEF(4, integer, short, channels, 1);
    std::string wavData;
    wavData.resize(pcmData.size() + 44);
    memcpy(&wavData[0], "RIFF", 4);
    int riffLen = pcmData.size() + 36;
    memcpy(&wavData[4], &riffLen, 4);
    memcpy(&wavData[8], "WAVEfmt ", 8);
    memcpy(&wavData[16], "\x10\0\0\0\x01\0\x01\0", 6);
    memcpy(&wavData[22], &channels, 2);
    memcpy(&wavData[24], &sampleRate, 4);
    int bytesPerSec = sampleRate * channels * bits / 8;
    memcpy(&wavData[28], &bytesPerSec, 4); // nAvgBytesPerSec
    short align = (short)channels * (short)bits / 8;
    memcpy(&wavData[32], &align, 2);
    memcpy(&wavData[34], &bits, 2);
    memcpy(&wavData[36], "data", 4);
    int bytes = pcmData.size();
    memcpy(&wavData[40], &bytes, 4);
    memcpy(&wavData[44], pcmData.data(), pcmData.size());
    RET(stdstring, wavData);
    return 1;
}

static int FloatArrayToPcm(lua_State* L) {
    ARG(1, vectorfloat<std::vector<float>>, std::vector<float>, data);
    ARG_DEF(2, integer, int, bits, 16);
    ARG_DEF(3, integer, int, channels, 1);
    std::string pcmData;
    pcmData.resize(data.size() * channels * bits / 8, '\0');
    if (bits == 16) {
        auto ptr = (short*)pcmData.data();
        for (size_t i = 0; i < data.size(); ++i) {
            *ptr++ = (short)(data[i] * 32767);
        }
    } else if (bits == 8) {
        auto ptr = (char*)pcmData.data();
        for (size_t i = 0; i < data.size(); ++i) {
            *ptr++ = (char)(data[i] * 127);
        }
    }
    RET(stdstring, pcmData);
    return 1;
}

static int PcmToFloatArray(lua_State* L) {
    ARG(1, stdstring, std::string, pcmData);
    ARG_DEF(2, integer, int, bits, 16);
    ARG_DEF(3, integer, int, channels, 1);
    std::vector<float> data;
    size_t count = pcmData.size() / ((8 > bits ? 8 : bits) / 8);
    data.resize(count);
    if (bits == 16) {
        auto ptr = (short const*)pcmData.data();
        for (size_t i = 0; i < count; ++i) {
            data[i] = *ptr++ * (1.0f / 32767.0f);
        }
    } else if (bits == 8) {
        auto ptr = (char const*)pcmData.data();
        for (size_t i = 0; i < count; ++i) {
            data[i] = *ptr++ * (1.0f / 127.0f);
        }
    }
    RET(vectorfloat<std::vector<float>>, data);
    return 1;
}

static RegisterModule InitModules = [] {
    MODULE_BEGIN(Sound);
    MODULE_FUNC(StopPlayingSound);
    MODULE_FUNC(PlaySoundFromMemory);
    MODULE_FUNC(PlaySoundFromFile);
    MODULE_FUNC(PlaySoundOfSystem);
    MODULE_FUNC(PcmToWav);
    MODULE_FUNC(FloatArrayToPcm);
    MODULE_FUNC(PcmToFloatArray);
    MODULE_END();
};

}
