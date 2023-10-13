// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"

// Stores the data for game view
class Camera final {
private:
	math::Vector2f m_pos;

	math::Vector2f m_viewSize; // View for world objects, not the window view space
	math::Vector2f m_windowSize;
	math::Vector2f m_singularObjectSize; // The size of a world object 1x1 on the screen

	float m_aspectRatio; // width/height
	float m_scale; // min(width, height) / some constant

public:
    Camera();

	math::Vector2f viewTopLeft() const;
    math::Vector2f viewDownRight() const;
	bool isInView(const math::Vector2f& pos) const;

	void setPos(const math::Vector2f& pos);
    bool updateViewSize(const math::Vector2f& windowSize); // returns true on change

	// Returns the pos relatively to camera pos
	math::Vector2f getPosInView(math::Vector2f pos) const; // World position to screen position
	math::Vector2f getGuiPos(math::Vector2f pos) const; // Adapts screen position of GUI

	math::Vector2f getGuiTransform() const; // Returns the transformation for GUI's

	const math::Vector2f& getPos() const noexcept;
	const math::Vector2f& getViewSize() const noexcept;
	const math::Vector2f& getWindowSize() const noexcept;
	const math::Vector2f& getSingularObjectSize() const noexcept;

	float getAspectRatio() const noexcept;
	float getScale() const noexcept;
};
