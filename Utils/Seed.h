// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string_view>

/*
*	Seed(.h/.cpp) contains a class that contains the global seed info.
* 
*	A seed must be availble from everywhere, so its way more convenient
*	to define it as a static interface.
*/

namespace utils {
	class Seed final {
	private:
		inline static size_t s_seed = 0;

	public:
		static void setSeed(size_t seed);
		static size_t seed();

		static size_t fromString(std::string_view str);
	};
}