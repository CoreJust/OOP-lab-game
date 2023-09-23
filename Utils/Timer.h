#pragma once

#include <chrono>

namespace utils {
	class Timer final {
	public:
		using FloatSeconds = std::chrono::duration<float, std::ratio<1>>;
		using DoubleSeconds = std::chrono::duration<double, std::ratio<1>>;

	private:
		std::chrono::steady_clock::duration m_lastTime;

	public:
		Timer();

		std::chrono::steady_clock::duration systemNow() const;
		double now() const;

		float calculateDeltaTime();
	};
}