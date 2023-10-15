// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "LineRasterizer.h"
#include "RasterizationUtils.h"

math::LineRasterizer::LineRasterizer(Vector2f from, Vector2f to) {
	if (from.y() > to.y()) {
		std::swap(from, to);
	}

	m_y = from.y();
	m_x = from.x();
	m_endY = to.y();
	m_xOffset = RasterizationUtils::offsetXperY(from, to);
}

void math::LineRasterizer::nextRow() {
	m_x += m_xOffset;
	m_y++;
}

int32_t math::LineRasterizer::leftX() {
	return uint32_t(m_xOffset < 0 ? m_x + m_xOffset : m_x);
}

int32_t math::LineRasterizer::rightX() {
	return uint32_t(m_xOffset > 0 ? m_x + m_xOffset : m_x);
}

uint32_t math::LineRasterizer::rowLength() {
	return uint32_t(m_xOffset) + 1;
}
