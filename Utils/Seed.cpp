// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Seed.h"

#include <string>
#include <algorithm>
#include <charconv>

#include "IO/Logger/Logger.h"
#include "Random.h"

void utils::Seed::setSeed(size_t seed) {
    io::Logger::info("Seed: global seed set to " + std::to_string(seed));

    s_seed = seed;
    utils::Random<>::setStaticSeed(seed);
}

size_t utils::Seed::seed() {
    return s_seed;
}

size_t utils::Seed::fromString(std::string_view str) {
    size_t result = 0;

    if (std::all_of(str.begin(), str.end(), [](unsigned char ch) -> bool { return std::isdigit(ch); })) { // Straight-forward conversion
        std::from_chars(str.data(), str.data() + str.size(), result);
    } else { // str is not a number
        result = 0; // Just to be on the safer side
        for (size_t i = 0; i < str.size(); i += sizeof(size_t)) { // Xoring the string as bytes array in case of non-number
            size_t tmp = 0;
            std::string_view substr = str.substr(i, sizeof(size_t));

            memcpy(&tmp, substr.data(), substr.size());

            result ^= tmp;
        }
    }

    return result;
}
