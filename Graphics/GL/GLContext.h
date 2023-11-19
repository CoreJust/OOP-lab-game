// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <exception>
#include <GL/glew.h>

/*
*	GLContext(.h/.cpp) contains a class that contains a set of OpenGL settings.
* 
*	It allows to conveniently use the settings in a bunch.
*	Note: if the stencil test is to be used, then this class is to be modified
*	- the test is not fully supported as of now.
* 
*	Usage:
*		gl::Context context;
*		context.enableXXX(...).enableXXX(...).setXXX(...);
* 
*		...
*		
*		context.clear();
*		context.use();
* 
*		// Some OpenGL code
* 
*		context.checkErrors();
*/

namespace gl {
	class Context final {
	private:
		bool m_enableDepth = false;
		bool m_enableMultisampling = false;
		bool m_enableCullFace = false;
		bool m_enableBlending = false;
		bool m_enableStencil = false;

		bool m_terminateUponError = false;

		GLenum m_blendEquation[2] { GL_FUNC_ADD, GL_FUNC_ADD };
		GLenum m_blendFunc[4] { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO };
		
		GLenum m_stencilFunc = GL_GEQUAL;
		GLint m_stencilRef = 0;
		GLuint m_stencilMask1 = 0xff;
		GLenum m_stencilOps[3] { GL_KEEP, GL_KEEP, GL_REPLACE };
		GLuint m_stencilMask2 = 0xff;

		// Currently unused
		GLboolean m_colorMasks[4] = { GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE };
		GLboolean m_depthMask = GL_FALSE;

	public:
		void use() const noexcept; // Applies the context
		void use(const Context& previous) const noexcept; // Applies the context while considering the previous one
		void checkErrors() const noexcept;

		constexpr GLbitfield getEnabledBuffers() const noexcept {
			GLbitfield buffers = GL_COLOR_BUFFER_BIT;

			if (m_enableDepth) {
				buffers |= GL_DEPTH_BUFFER_BIT;
			}

			if (m_enableStencil) {
				buffers |= GL_STENCIL_BUFFER_BIT;
			}

			return buffers;
		}

		constexpr Context& enableDepthTest(bool value = true) noexcept {
			m_enableDepth = value;

			return *this;
		}

		constexpr Context& enableMultisampling(bool value = true) noexcept {
			m_enableMultisampling = value;

			return *this;
		}

		constexpr Context& enableCullFace(bool value = true) noexcept {
			m_enableCullFace = value;

			return *this;
		}

		constexpr Context& enableBlending(bool value = true) noexcept {
			m_enableBlending = value;

			return *this;
		}

		constexpr Context& enableStencilTest(bool value = true) noexcept {
			m_enableStencil = value;

			return *this;
		}

		constexpr Context& enableTerminationUponErrors(bool value = true) noexcept {
			m_terminateUponError = value;

			return *this;
		}

		constexpr Context& setBlendEquation(GLenum modeRGB, GLenum modeAlpha) noexcept {
			assert(m_enableBlending);
			checkGLenumInRange(modeRGB, { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_SUBTRACT, GL_MIN, GL_MAX });
			checkGLenumInRange(modeAlpha, { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_SUBTRACT, GL_MIN, GL_MAX });

			m_blendEquation[0] = modeRGB;
			m_blendEquation[1] = modeAlpha;

			return *this;
		}

		constexpr Context& setBlendEquation(GLenum mode = GL_FUNC_ADD) noexcept {
			setBlendEquation(mode, mode);

			return *this;
		}

		constexpr Context& setBlendFunc(GLenum modeSrcRGB, GLenum modeDestRGB, GLenum modeSrcAlpha, GLenum modeDestAlpha) noexcept {
			assert(m_enableBlending);

			m_blendFunc[0] = modeSrcRGB;
			m_blendFunc[1] = modeDestRGB;
			m_blendFunc[2] = modeSrcAlpha;
			m_blendFunc[3] = modeDestAlpha;

			return *this;
		}

		constexpr Context& setBlendFunc(GLenum modeSrc, GLenum modeDest) noexcept {
			setBlendFunc(modeSrc, modeDest, modeSrc, modeDest);

			return *this;
		}

		constexpr Context& setBlendFunc() noexcept {
			setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

			return *this;
		}

		constexpr Context& setStencilFunc(GLenum func = GL_GEQUAL, GLint ref = 0, GLuint mask = 0xff) noexcept {
			assert(m_enableStencil);

			m_stencilFunc = func;
			m_stencilRef = ref;
			m_stencilMask1 = mask;

			return *this;
		}

		constexpr Context& setStencilOp(GLenum stencilFail = GL_KEEP, 
										GLenum depthFailStencilPass = GL_KEEP, 
										GLenum pass = GL_REPLACE
		) noexcept {
			assert(m_enableStencil);
			checkGLenumInRange(stencilFail, { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, GL_INVERT });
			checkGLenumInRange(depthFailStencilPass, { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, GL_INVERT });
			checkGLenumInRange(depthFailStencilPass, { GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, GL_INVERT });

			m_stencilOps[0] = stencilFail;
			m_stencilOps[1] = depthFailStencilPass;
			m_stencilOps[2] = pass;

			return *this;
		}

		constexpr Context& setStencilMask(GLuint mask = 0xff) noexcept {
			assert(m_enableStencil);

			m_stencilMask2 = mask;

			return *this;
		}

	private:
		template<size_t Size>
		constexpr void checkGLenumInRange(GLenum value, const GLenum(&arr)[Size]) const noexcept {
			for (auto& a : arr) {
				if (a == value) {
					return;
				}
			}

			assert(false && "value is not in range");
#ifdef NDEBUG
			std::terminate();
#endif
		}
	};
}