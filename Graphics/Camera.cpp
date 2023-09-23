#include "Camera.h"

#include "Texture/Texture.h"

Camera::Camera(const utils::Vector2f& viewSize)
	: m_viewSize(viewSize) {

}

utils::Vector2f Camera::viewTopLeft() const {
	return m_pos - m_viewSize;
}

utils::Vector2f Camera::viewDownRight() const {
	return m_pos + m_viewSize;
}

bool Camera::isInView(const utils::Vector2f& pos) const {
	return (pos - m_pos).abs().isToLeftUpFrom(m_viewSize);
}

void Camera::setPos(const utils::Vector2f& pos) {
	m_pos = pos;
}

void Camera::updateViewSize(const utils::Vector2f& windowSize) {
	m_viewSize = windowSize / (2 * Texture::TEXTURE_SIZE) + utils::Vector2f(1, 1);
}

utils::Vector2f Camera::getPosInView(const utils::Vector2f& pos) const {
	return pos - m_pos;
}

const utils::Vector2f& Camera::getPos() const {
	return m_pos;
}

const utils::Vector2f& Camera::getViewSize() const {
	return m_viewSize;
}
