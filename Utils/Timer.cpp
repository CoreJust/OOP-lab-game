#include "Timer.h"

#include <chrono>

namespace utils {
	Timer::Timer() {
		m_lastTime = now();
	}

	float Timer::now() {
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return std::chrono::duration<float, std::ratio<1>>(now).count(); // to seconds
	}

	float Timer::calculateDeltaTime() {
		float time = now();
		float result = time - m_lastTime;
		m_lastTime = time;

		return result;
	}
}
