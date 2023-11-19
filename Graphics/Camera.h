// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <functional>
#include <glm/glm.hpp>

#include "Utils/NoNullptr.h"
#include "Math/Vector.h"
#include "IO/Input/VirtualInput.h"

/*
*	Camera(.h/.cpp) contains a class that is responsible for managing the game view.
* 
*	In general, the camera follows the player, thus allowing him to always be within the view.
*/

// Stores the data for game view
class Camera final {
public:
	using RotationCallback = std::function<void(const math::Vector2f&)>;

private:
	math::Vector2f m_pos; // the player pos
	math::Vector2f m_angle; // rotation around the player

	math::Vector2f m_viewSize; // View for world objects, not the window view space
	math::Vector2f m_windowSize;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_projViewMatrix;

	float m_aspectRatio; // width/height
	float m_FOV; // field of view

	std::vector<RotationCallback> m_rotationCallbacks; // Accepts new rotation

public:
    Camera();

	void update(utils::NoNullptr<io::VirtualInput> input);

	math::Vector2f viewTopLeft() const;
    math::Vector2f viewDownRight() const;

	void setPos(const math::Vector2f& pos);
    bool updateViewSize(const math::Vector2f& windowSize); // returns true on change
	void updateProjection();
	void setFOV(float degrees);

	void addRotationCallback(RotationCallback callback);

	// Returns the pos relatively to camera pos
	math::Vector2f getGuiPos(math::Vector2f pos) const; // Adapts screen position of GUI
	math::Vector2f getGuiTransform() const; // Returns the transformation for GUI's

	const glm::mat4& genProjViewMatrix() const; // The matrix for moving and object into the view

	const math::Vector2f& getPos() const noexcept;
	const math::Vector2f& getViewSize() const noexcept;
	const math::Vector2f& getWindowSize() const noexcept;
	float getAspectRatio() const noexcept;

private:
	void recomputeProjViewMatrix();

	void onRotation();
};
