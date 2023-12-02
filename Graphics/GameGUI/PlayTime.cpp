// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PlayTime.h"

#include <format>
#include "Math/Cmath.h"

gamegui::PlayTime::PlayTime(const math::Vector2f& pos) 
	: Text("", math::Rectf(pos, pos + math::Vector2f(0.5f, 0.07f))) {
	m_timer.reset();
}

void gamegui::PlayTime::reset() {
	m_timer.reset();
}

void gamegui::PlayTime::update() {
	const float time = m_timer.elapsedTime();
	const uint32_t seconds = math::Cmath::wholeOf(time);
	const uint32_t minutes = seconds / 60;
	const uint32_t hours = minutes / 60;

	if (hours) {
		Text::setText(std::format("{0}:{1}:{2:.2f}", hours, minutes % 60, time - minutes * 60));
	} else {
		Text::setText(std::format("{0}:{1:.2f}", minutes % 60, time - minutes * 60));
	}
}
