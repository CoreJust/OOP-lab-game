// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Concepts.h"

/*
*	CustomAssignment.h contains a class that allows to create
*	a class with some pre-defined action upon assignment to it.
*/

namespace utils {
	class CustomAssignment final {
	public:
		template<class Func, class T>
			requires utils::Callable<Func, void, T>
		class Implementation final {
		private:
			[[no_unique_address]] Func m_func;

		public:
			Implementation(Func func) : m_func(std::move(func)) { }

			Implementation& operator=(T value) {
				m_func(std::forward(value));
				return *this;
			}
		};

	public:
		template<class Func, class T>
		static Implementation<Func, T> make(Func func) {
			return Implementation<Func, T>(std::move(func));
		}
	};
}