// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <concepts>
#include <ostream>

/*
*	Concepts.h contains a number of diverse concepts used throughout 
*	the project.
*/

namespace utils {
	template<class T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template<class T>
	concept FloatingPoint = std::is_floating_point_v<T>;

	template<class T>
	concept ArrayLike = requires (T arr, size_t i) { arr[i]; };

	template<class T>
	concept Printable = requires(T x, std::ostream& out) { out << x; };

	template<class Distr, class T>
	concept DistributionConcept = requires(Distr dist, T t) { dist(t); };

	template<class T>
	concept RandomGeneratorConcept = requires(T t) { t.seed(size_t(0)); };

	template<class T, class Result, class... Args>
	concept Callable = requires(T func, Args... args) {
		{ func(args...) } -> std::convertible_to<Result>;
	};
}