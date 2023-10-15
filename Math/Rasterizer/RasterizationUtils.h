// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"

namespace math {
	// Some auxiliary functions used in rasterizers
	class RasterizationUtils final {
	public:
		// Bit masks for Cohen-Sutherland algorythm
		enum CohenSutherland : uint8_t {
			NONE = 0,
			LEFT = 1,
			RIGHT = 2,
			BOTTOM = 4,
			TOP = 8
		};

	public:
		// Returns upper of 2 normals to the vector
		constexpr static Vector2f getUpperNormalToVec(Vector2f vec) {
			vec = vec.normalize();
			if (vec.x() <= 0) {
				return vec.mirrorByY();
			} else {
				return vec.mirrorByX();
			}
		}

		// Returns a point advanced from pos in the chosen direction for advanceFor
		// direction must be a normalized vector
		constexpr static Vector2f advanceInDirectionFor(const Vector2f& pos, Vector2f direction, const float advanceFor) {
			direction *= advanceFor;
			return (pos + direction + 0.5f).roundFloor();
		}

		// Returns for how much X changes if Y changes for +1
		constexpr static double offsetXperY(Vector2f from, Vector2f to) {
			int32_t modifier = to.y() < from.y() ? -1 : 1;
			return double(to.x() - from.x()) / (to.y() - from.y() + modifier);
		}

		// Clips the line so that it lies within rect(0, 0, width, height)
		// Returns false if the line is out of rect
		// On returning false, the passed arguments are not modified
		constexpr static bool clipLine(Vector2f& from, Vector2f& to, uint32_t width, uint32_t height) {
            uint8_t cs1 = getCohenSutherlandCode(from, width, height);
            uint8_t cs2 = getCohenSutherlandCode(to, width, height);

            // Both ends are on the same side from the rect and the line is out of the rect
            if (cs1 & cs2) {
                return false;
            }

            // Both ends are within the rect, nothing to clip
            if (cs1 == 0 && cs2 == 0) {
                return true;
            }

            double fromX = from.x();
            double fromY = from.y();
            double toX = to.x();
            double toY = to.y();

            uint8_t cs_chosen = 0;
            double* chosenX = nullptr;
            double* chosenY = nullptr;

            while (cs1 | cs2) {
                if (cs1 & cs2) { // Line is out of the rect
                    return false;
                }

                // Choosing the end to clip
                if (cs1) {
                    cs_chosen = cs1;
                    chosenX = &fromX;
                    chosenY = &fromY;
                } else {
                    cs_chosen = cs2;
                    chosenX = &toX;
                    chosenY = &toY;
                }

                // Clipping the chosen end
                if (cs_chosen & CohenSutherland::LEFT) {
                    *chosenY += (fromY - toY) * (-*chosenX) / (fromX - toX);
                    chosenX = 0;
                } else if (cs_chosen & CohenSutherland::RIGHT) {
                    *chosenY += (fromY - toY) * (width - 1 - *chosenX) / (fromX - toX);
                    *chosenX = width - 1;
                } else if (cs_chosen & CohenSutherland::BOTTOM) {
                    *chosenX += (fromX - toX) * (-*chosenY) / (fromY - toY);
                    *chosenY = 0;
                } else if (cs_chosen & CohenSutherland::TOP) {
                    *chosenX += (fromX - toX) * (height - 1 - *chosenY) / (fromY - toY);
                    *chosenY = height - 1;
                }

                // Update the codes
                if (cs_chosen == cs1) {
                    cs1 = getCohenSutherlandCode(Vector2f(fromX, fromY), width, height);
                } else { // The second one was modified
                    cs2 = getCohenSutherlandCode(Vector2f(toX, toY), width, height);
                }
            }

            from.x() = fromX + 0.5f;
            from.y() = fromY + 0.5f;
            to.x() = toX + 0.5f;
            to.y()  = toY + 0.5f;

            return true;
		}

		// Returns true if the line lies completely out of rect (0, 0, width, height) and false otherwise
		constexpr static bool isLineOutOfRect(Vector2f from, Vector2f to, uint32_t width, uint32_t height) {
            return !clipLine(from, to, width, height);
		}

		// Returns the code of pos in rect (0, 0, width, height) according to Cohen-Sutherland algorythm
		constexpr static uint8_t getCohenSutherlandCode(Vector2f pos, uint32_t width, uint32_t height) {
            return (pos.x() < 0 ? CohenSutherland::LEFT : 0) |
                (pos.x() >= width ? CohenSutherland::RIGHT : 0) |
                (pos.y() < 0 ? CohenSutherland::BOTTOM : 0) |
                (pos.y() >= height ? CohenSutherland::TOP : 0);
		}
	};
}