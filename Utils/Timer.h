// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <chrono>

/*
*	Timer(.h/.cpp) contains a class that implements a timer.
* 
*	It allows to measure time durations between some events.
*	Usage:
*		Timer timer;
*		while (...) {
*			float duration = timer.calculateDeltaTime();
*		}
*/

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