// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include "Vector.h"
#include "Rect.h"

namespace math {
	// Mapper allows to map 2D coordinates into 1D coordinates
	// Works with the center of field and with the top-left corner as the zero point
	template<bool IgnoreOutOfBounds = false>
	class Mapper final {
	public:
		constexpr inline static bool CENTER_COORDS = false; // Coords with zero at center
		constexpr inline static bool CORNER_COORDS = !CENTER_COORDS; // Coords with zero at corner

	private:
		math::Vector2i m_size;
		math::Vector2u m_actualSize;

	public:
		constexpr Mapper(const Mapper&) noexcept = default;
		constexpr Mapper(Mapper&&) noexcept = default;

		constexpr Mapper(const math::Vector2i& size = math::Vector2i{ }) noexcept : m_size(size) {
			assert(size.isToDownRightFrom({ 0, 0 }));

			m_actualSize = (m_size * 2 + 1).to<uint32_t>();
		}

		constexpr void setSize(const math::Vector2i& size) noexcept {
			assert(size.isToDownRightFrom({ 0, 0 }));

			m_size = size;
			m_actualSize = (m_size * 2 + 1).to<uint32_t>();
		}

		constexpr const math::Vector2i& getSize() const noexcept {
			return m_size;
		}

		constexpr const math::Vector2u& getActualSize() const noexcept {
			return m_actualSize;
		}

		constexpr Recti getRect() const noexcept {
			return Recti(-m_size, m_size);
		}

		constexpr Rectu getActualRect() const noexcept {
			return Rectu(math::Vector2u{ 0, 0 }, m_actualSize);
		}

		constexpr uint32_t getWidth() const noexcept {
			return m_actualSize.x();
		}

		constexpr uint32_t getHeight() const noexcept {
			return m_actualSize.y();
		}

		constexpr uint32_t getArea() const noexcept {
			return m_actualSize.area();
		}

		// Returns the center index in corner coordinates
		constexpr uint32_t getActualCenterIndex() const noexcept {
			return m_size.x() + m_size.y() * m_actualSize.x();
		}

		template<bool FromCoords = CENTER_COORDS>
		constexpr Vector2i remapCoords(const Vector2i& pos) const noexcept {
			if constexpr (FromCoords == CENTER_COORDS) { // to Corner coords
				return pos + m_size;
			} else { // from Corner coords to Center coords
				return pos - m_size;
			}
		}

		template<bool Coords = CENTER_COORDS>
		constexpr bool contains(const math::Vector2i& pos) const noexcept {
			if constexpr (Coords == CENTER_COORDS) {
				return pos.abs().isToUpLeftFrom(m_size);
			} else { // Corner coords
				return pos.isToDownRightFrom({ 0, 0 }) && pos.isToUpLeftFrom(m_actualSize.to<int32_t>());
			}
		}

		template<bool IndexCoords = CENTER_COORDS, bool PosCoords = CENTER_COORDS>
		constexpr int64_t getIndex(const math::Vector2i& pos) const noexcept {
			if constexpr (!IgnoreOutOfBounds) {
				assert(contains<PosCoords>(pos));
			}

			if constexpr (IndexCoords == PosCoords) {
				return pos.x() + pos.y() * int64_t(m_actualSize.x());
			} else if (IndexCoords == CENTER_COORDS) { // and PosCoords == CORNER_COORDS
				return pos.x() + pos.y() * int64_t(m_actualSize.x()) - getActualCenterIndex();
			} else { // IndexCoords == CORNER_COORDS and PosCoords == CENTER_COORDS
				return pos.x() + pos.y() * int64_t(m_actualSize.x()) + getActualCenterIndex();
			}
		}

		constexpr int64_t getCornerIndex(const math::Vector2i& pos) const noexcept {
			return getIndex<CORNER_COORDS, CORNER_COORDS>(pos);
		}
	};
}