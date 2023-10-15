// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "BasicRasterizer.h"

int32_t math::BasicRasterizer::getY() const {
    return m_y;
}

int32_t math::BasicRasterizer::getEndY() const {
    return m_endY;
}

bool math::BasicRasterizer::hasMore() {
    return m_y <= m_endY;
}
