// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <GL/glew.h>

/*
*	GLObject.h contains a base class for all the opengl objects.
*
*	An object in opengl is actually an id for some internal representation.
*	A zero as an id represents object's absence.
* 
*	An object can be created, destroyed, be binded and unbinded.
*/

namespace gl {
	// The base class for all the objects in OpenGL
	// Abstract class
	class Object {
	protected:
		GLuint m_id; // All gl objects (in the way they are represented in the code) are GLuints by nature

	public:
		constexpr Object() noexcept : m_id(0) { }
		constexpr Object(Object&& other) noexcept : m_id(other.m_id) {
			other.m_id = 0;
		}

		constexpr virtual ~Object() {
			releaseIfNotEmpty();
		}

		constexpr Object& operator=(Object&& other) noexcept {
			releaseIfNotEmpty();

			m_id = other.m_id;
			other.m_id = 0;

			return *this;
		}

		constexpr void releaseIfNotEmpty() noexcept {
			if (m_id != 0) {
				this->release();
				m_id = 0;
			}
		}

		virtual void create() = 0;
		virtual void release() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		constexpr GLuint getId() const noexcept {
			return m_id;
		}

		constexpr bool isEmpty() const noexcept {
			return m_id == 0;
		}
	};
}