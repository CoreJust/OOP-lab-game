// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Math/Cmath.h"
#include "Math/MathUtils.h"
#include "GlobalSettings.h"
#include "Texture/Texture.h"

constexpr float SCALE_FACTOR = 10.f * Texture::TEXTURE_SIZE;

constexpr float Z_PROJ_NEAR = 0.002f;
constexpr float Z_PROJ_FAR = 100.f;

constexpr glm::vec3 CAMERA_OFFSET = glm::vec3(0.8f, 3.5f, 2.6f);

constexpr float MOUSE_SENSIBILITY = 0.0032f;

Camera::Camera()
	: m_viewSize(0), 
	m_windowSize(0), 
	m_singularObjectSize(0), 
	m_aspectRatio(0), 
	m_scale(0), 
	m_angle(0.f, 0.f),
	m_FOV(90.f),
	m_projectionMatrix(glm::perspective(glm::radians<float>(90), 1.f, Z_PROJ_NEAR, Z_PROJ_FAR)) {

}

void Camera::update(utils::NoNullptr<io::VirtualInput> input) {
	static math::Vector2f s_lastMousePos = input->getMousePosition();
	math::Vector2f mouseOffset = input->getMousePosition() - s_lastMousePos;

	constexpr float PI = std::numbers::pi_v<float>;

	// Computing the camera rotation
	const float dx = math::MathUtils::clampInRange<float, 30.f>(mouseOffset.x()); // For freezes
	m_angle.x() -= dx * MOUSE_SENSIBILITY;
	m_angle.x() = math::MathUtils::encycleInRange<float, PI>(m_angle.x());

	if (GlobalSettings::get().isEnableVerticalViewMoving()) {
		const float dy = math::MathUtils::clampInRange<float, 30.f>(mouseOffset.y()); // For freezes
		m_angle.y() -= dy * MOUSE_SENSIBILITY * 0.4f;
		m_angle.y() = math::MathUtils::clamp<float, PI * -0.15f, PI * 0.2f>(m_angle.y());

		if (dx || dy) {
			onRotation();
		}
	} else if (dx) {
		onRotation();
	}

	// Centering the mouse
	sf::Mouse::setPosition((m_windowSize.roundFloor() / 2).roundFloor().to<int32_t>().toSfml());
	s_lastMousePos = (m_windowSize / 2).roundFloor();
}

math::Vector2f Camera::viewTopLeft() const {
	return m_pos - m_viewSize;
}

math::Vector2f Camera::viewDownRight() const {
	return m_pos + m_viewSize;
}

void Camera::setPos(const math::Vector2f& pos) {
	m_pos = pos + math::Vector2f{ 0, 1 };
	recomputeProjViewMatrix();
}

bool Camera::updateViewSize(const math::Vector2f& windowSize) {
	if (windowSize != m_windowSize) {
		m_aspectRatio = windowSize.x() / windowSize.y();
		m_scale = math::Cmath::min(windowSize.x(), windowSize.y()) / SCALE_FACTOR;
		m_singularObjectSize = 1.f / (m_scale * Texture::TEXTURE_SIZE);

		m_viewSize = math::Vector2f(GlobalSettings::get().getMaxRenderDistance());
		m_windowSize = windowSize;

		updateProjection();
		return true;
	}

	return false;
}

void Camera::updateProjection() {
	m_projectionMatrix = glm::perspective(m_FOV, m_aspectRatio, Z_PROJ_NEAR, Z_PROJ_FAR);
	recomputeProjViewMatrix();
}

void Camera::setFOV(float degrees) {
	m_FOV = glm::radians(degrees);
	updateProjection();
}

void Camera::addRotationCallback(RotationCallback callback) {
	m_rotationCallbacks.push_back(std::move(callback));
}

math::Vector2f Camera::getPosInView(math::Vector2f pos) const {
	pos -= m_pos;
	return pos / m_scale;
}

math::Vector2f Camera::getGuiPos(math::Vector2f pos) const {
	if (m_aspectRatio >= 1.f) {
		pos.x() *= m_aspectRatio;
	} else {
		pos.y() /= m_aspectRatio;
	}

	return pos;
}

math::Vector2f Camera::getGuiTransform() const {
	math::Vector2f pos { 1.f };

	if (m_aspectRatio >= 1.f) {
		pos.x() *= m_aspectRatio;
	} else {
		pos.y() /= m_aspectRatio;
	}

	return pos;
}

const glm::mat4& Camera::genProjViewMatrix() const {
	return m_projViewMatrix;
}

const math::Vector2f& Camera::getPos() const noexcept {
	return m_pos;
}

const math::Vector2f& Camera::getViewSize() const noexcept {
	return m_viewSize;
}

const math::Vector2f& Camera::getWindowSize() const noexcept {
	return m_windowSize;
}

const math::Vector2f& Camera::getSingularObjectSize() const noexcept {
	return m_singularObjectSize;
}

float Camera::getAspectRatio() const noexcept {
	return m_aspectRatio;
}

float Camera::getScale() const noexcept {
	return m_scale;
}

void Camera::recomputeProjViewMatrix() {
	glm::vec3 lookAtCenter { m_pos.x(), 0.5f, m_pos.y() };
	glm::vec3 cameraPos = glm::rotateX(CAMERA_OFFSET, m_angle.y());
	cameraPos = glm::rotateY(cameraPos, m_angle.x()) + lookAtCenter;

	m_projViewMatrix = m_projectionMatrix * glm::lookAt(cameraPos, lookAtCenter, { 0.f, 1.f, 0.f });
}

void Camera::onRotation() {
	recomputeProjViewMatrix();

	for (auto& fun : m_rotationCallbacks) {
		fun(m_angle);
	}
}
