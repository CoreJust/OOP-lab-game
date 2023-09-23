#include "Timer.h"

namespace utils {
	Timer::Timer() {
		m_lastTime = systemNow();
	}

	std::chrono::steady_clock::duration Timer::systemNow() const {
		return std::chrono::high_resolution_clock::now().time_since_epoch();
	}

	double Timer::now() const {
		return DoubleSeconds(systemNow()).count(); // to seconds
	}

	float Timer::calculateDeltaTime() {
		auto time = systemNow();
		FloatSeconds result = time - m_lastTime;
		m_lastTime = time;

		return result.count();
	}
}
