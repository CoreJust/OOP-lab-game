// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "BasicRasterizer.h"

/*
*	SingleRasterizer.h contains a base class for the rasterizers of
*	"single" shapes.
*
*	A single shape is a shape that for each row has single 1D area.
*	For example, it is a line, rect, circle, tetters C, E, F, I, J, L, T, etc.
*	But letters X, Y, or B are not.
* 
*	Usage example:
*		SingleRasterizer* some_r = ...;
*		while (some_r->hasMore()) {
*			some_func(some_r->leftX(), some_r->rightX()); // The difference from the BasicRasterizer
*			some_r->nextRow();
*		}
*/

namespace math {
	class SingleRasterizer : public BasicRasterizer {
	public:
		virtual int32_t leftX() = 0; // Current row's left-most X
		virtual int32_t rightX() = 0; // Current row's right-most X
		virtual uint32_t rowLength() = 0; // Current row's width
	};
}
