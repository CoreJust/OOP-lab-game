#pragma once

namespace utils {
	class Timer final {
	private:
		float m_lastTime = 0;

	public:
		Timer();

		float now();
		float calculateDeltaTime();
	};
}