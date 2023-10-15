// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "BasicRasterizer.h"

namespace math {
	// For those shapes that have a single piece in each row
	// Splits some shape into a pair of left-most and right-most X for each row
	// Usage example:
	//		SingleRasterizer* some_r = ...;
	//		while (some_r->hasMore()) {
	//			some_func(some_r->leftX(), some_r->rightX());
	//			some_r->nextRow();
	//		}
	class SingleRasterizer : public BasicRasterizer {
	public:
		virtual int32_t leftX() = 0; // Current row's left-most X
		virtual int32_t rightX() = 0; // Current row's right-most X
		virtual uint32_t rowLength() = 0; // Current row's width
	};
}
