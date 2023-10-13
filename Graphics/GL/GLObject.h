// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <GL/glew.h>

namespace gl {
	// The base class for all the objects in OpenGL
	// Abstract class
	class Object {
	protected:
		GLuint m_id; // All gl objects (in the way they are represented in the code) are GLuints by nature
		bool m_isEmpty; // Was the object not created as a GL object? (Or else: was it initialized?)

	public:
		constexpr Object() noexcept : m_id(0), m_isEmpty(true) { }
		constexpr Object(Object&& other) noexcept : m_id(other.m_id), m_isEmpty(other.m_isEmpty) {
			other.m_isEmpty = true;
		}

		constexpr virtual ~Object() {
			this->releaseIfNotEmpty();
		}

		constexpr Object& operator=(Object&& other) noexcept {
			releaseIfNotEmpty();

			m_id = other.m_id;
			m_isEmpty = other.m_isEmpty;
			other.m_isEmpty = true;

			return *this;
		}

		constexpr void releaseIfNotEmpty() noexcept {
			if (!m_isEmpty) {
				this->release();
				m_isEmpty = true;
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
			return m_isEmpty;
		}
	};
}