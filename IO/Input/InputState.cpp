// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "InputState.h"

#include "Math/Cmath.h"
#include "KeysStringMap.h"

/*
*   The string representation of the input state: <bits for keys><bits for mouse><mouse pos><wheel delta><frame delta time>
*/

std::string io::InputState::toString() const {
    std::string result;
    result.resize(STRING_REPRESENTATION_SIZE, 0);

    unsigned char* data = (unsigned char*)&result[0];

    auto writeBitset = [&data]<size_t N>(const std::bitset<N>& bs) {
        size_t NBytes = math::Cmath::ceil(N / 8.f);
        for (size_t b = 0; b < NBytes; b++) {
            size_t from = b * 8;
            size_t to = math::Cmath::min(from + 8, N);

            unsigned char ch = 0;
            for (size_t i = from; i < to; i++) {
                ch |= bs.test(i);

                if (i % 8 != 7) {
                    ch <<= 1;
                }
            }

            *(data++) = ch;
        }
    };

    writeBitset(keysState);
    writeBitset(miceState);

    *(math::Vector2f*)data = mousePos;
    data += sizeof(math::Vector2f);

    *(float*)data = mouseWheelDelta;
    data += sizeof(float);

    *(float*)data = deltaTime;

    return result;
}

bool io::InputState::loadFromString(std::string_view str) {
    if (str.size() < STRING_REPRESENTATION_SIZE) {
        return false;
    }

    unsigned char* data = (unsigned char*)&str[0];

    auto loadBitset = [&data]<size_t N>(std::bitset<N>& bs) {
        size_t NBytes = math::Cmath::ceil(N / 8.f);
        for (size_t b = 0; b < NBytes; b++) {
            size_t from = b * 8;
            size_t to = math::Cmath::min(from + 8, N);

            unsigned char ch = *(data++);
            for (size_t i = from; i < to; i++) {
                bs.set(i, ch & 0x80);
                ch <<= 1;
            }
        }
    };

    loadBitset(keysState);
    loadBitset(miceState);

    mousePos = *(math::Vector2f*)data;
    data += sizeof(math::Vector2f);

    mouseWheelDelta = *(float*)data;
    data += sizeof(float);

    deltaTime = *(float*)data;

    return true;
}
