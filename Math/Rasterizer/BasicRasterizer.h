// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/Concepts.h"

/*
*	BasicRasterizer.h contains a base class for rasterizers.
*
*	A rasterizer is a class that allows to access all the points of some custom shape.
*	The iteration goes over the rows of the shape.
* 
*	Usage example:
*		BasicRasterizer* some_r = ...;
*		while (some_r->hasMore()) {
*			...
*			some_r->nextRow();
*		}
*/

namespace math {
	class SingleRasterizer;

	// Concept for SingleRasterizer's derived classes
	template<class T>
	concept SingleRasterizerConcept = std::derived_from<T, SingleRasterizer>;

	// Basic class for all rasterizers
	// Splits some shape into rows of X values
	// The X is guaranteed to be >= 0, but it can be out of image width, this should be handled outside
	class BasicRasterizer {
	protected:
		int32_t m_y = 0; // Current row
		int32_t m_endY = 0; // The last row

	public:
		virtual void nextRow() = 0;

		int32_t getY() const;
		int32_t getEndY() const;

		bool hasMore(); // Are there more rows in this shape
	};
}