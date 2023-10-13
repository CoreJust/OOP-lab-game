// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Camera.h"

#include "Math/Cmath.h"
#include "GlobalSettings.h"
#include "Texture/Texture.h"

constexpr float SCALE_FACTOR = 10.f * Texture::TEXTURE_SIZE;

Camera::Camera()
	: m_viewSize(0), m_windowSize(0), m_singularObjectSize(0), m_aspectRatio(0), m_scale(0) {

}

math::Vector2f Camera::viewTopLeft() const {
	return m_pos - m_viewSize;
}

math::Vector2f Camera::viewDownRight() const {
	return m_pos + m_viewSize;
}

bool Camera::isInView(const math::Vector2f& pos) const {
	return (pos - m_pos).abs().isToUpLeftFrom(m_viewSize);
}

void Camera::setPos(const math::Vector2f& pos) {
	m_pos = pos + math::Vector2f{ 0, 1 };
}

bool Camera::updateViewSize(const math::Vector2f& windowSize) {
	if (windowSize != m_windowSize) {
		m_aspectRatio = windowSize.x() / windowSize.y();
		m_scale = math::Cmath::min(windowSize.x(), windowSize.y()) / SCALE_FACTOR;
		m_singularObjectSize = 1.f / (m_scale * Texture::TEXTURE_SIZE);

		m_viewSize = windowSize / (2 * Texture::TEXTURE_SIZE) + math::Vector2f(1, 1);
		m_viewSize = m_viewSize.getMinByXY(math::Vector2f(GlobalSettings::get().getMaxRenderDistance()));

		m_windowSize = windowSize;
		return true;
	}

	return false;
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
