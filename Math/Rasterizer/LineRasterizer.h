// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"
#include "SingleRasterizer.h"

/*
*	LineRasterizer.h contains a class for the line rasterization.
*
*	Allows to calculate all the points that make up a line.
*/

namespace math {
	// Allows to get the pairs of the first and last points in a row for each row
	// For a line with width of 1 pixel
	class LineRasterizer final : public SingleRasterizer {
	private:
		double m_x; // Current X
		double m_xOffset; // dx/dy

	public:
		LineRasterizer(Vector2f from, Vector2f to);

		void nextRow() override;

		int32_t leftX() override; // Current row's left-most X
		int32_t rightX() override; // Current row's right-most X
		uint32_t rowLength() override; // Current row's width
	};
}