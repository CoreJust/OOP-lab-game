#pragma once
#include "Utils/Vector.h"

// Stores the data for game view
class Camera final {
private:
	utils::Vector2f m_pos;
	utils::Vector2f m_viewSize;

public:
    Camera(const utils::Vector2f& viewSize = {0, 0});

	utils::Vector2f viewTopLeft() const;
    utils::Vector2f viewDownRight() const;
	bool isInView(const utils::Vector2f& pos) const;

	void setPos(const utils::Vector2f& pos);
    void updateViewSize(const utils::Vector2f& windowSize);

	// Returns the pos relatively to camera pos
	utils::Vector2f getPosInView(const utils::Vector2f& pos) const;

	const utils::Vector2f& getPos() const;
	const utils::Vector2f& getViewSize() const;
};
