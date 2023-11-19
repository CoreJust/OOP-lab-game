// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLContext.h"
#include "IO/Logger.h"


using GLStateFunc = decltype(glEnable)*;


void gl::Context::use() const noexcept {
	GLStateFunc enable[2] = { glDisable, glEnable };

	enable[m_enableDepth](GL_DEPTH_TEST);
	enable[m_enableMultisampling](GL_MULTISAMPLE);
	enable[m_enableCullFace](GL_CULL_FACE);

	enable[m_enableBlending](GL_BLEND);
	if (m_enableBlending) {
		glBlendEquationSeparate(m_blendEquation[0], m_blendEquation[1]);
		glBlendFuncSeparate(m_blendFunc[0], m_blendFunc[1], m_blendFunc[2], m_blendFunc[3]);
	}

	enable[m_enableStencil](GL_STENCIL_TEST);
	if (m_enableStencil) {
		glStencilFunc(m_stencilFunc, m_stencilRef, m_stencilMask1);
		glStencilOp(m_stencilOps[0], m_stencilOps[1], m_stencilOps[2]);
		glStencilMask(m_stencilMask2);
	}
}

void gl::Context::use(const Context& previous) const noexcept {
	GLStateFunc enable[2] = { glDisable, glEnable };

	if (m_enableDepth != previous.m_enableDepth) {
		enable[m_enableDepth](GL_DEPTH_TEST);
	}

	if (m_enableMultisampling != previous.m_enableMultisampling) {
		enable[m_enableMultisampling](GL_MULTISAMPLE);
	}

	if (m_enableCullFace != previous.m_enableCullFace) {
		enable[m_enableCullFace](GL_CULL_FACE);
	}

	if (m_enableBlending != previous.m_enableBlending) {
		enable[m_enableBlending](GL_BLEND);
	}

	if (m_enableBlending) {
		if (m_blendEquation[0] != previous.m_blendEquation[0] || m_blendEquation[1] != previous.m_blendEquation[1]) {
			glBlendEquationSeparate(m_blendEquation[0], m_blendEquation[1]);
		}

		if (m_blendFunc[0] != previous.m_blendFunc[0] || m_blendFunc[1] != previous.m_blendFunc[1]
			|| m_blendFunc[2] != previous.m_blendFunc[2] || m_blendFunc[3] != previous.m_blendFunc[3]) {
			glBlendFuncSeparate(m_blendFunc[0], m_blendFunc[1], m_blendFunc[2], m_blendFunc[3]);
		}
	}

	if (m_enableStencil != previous.m_enableStencil) {
		enable[m_enableStencil](GL_STENCIL_TEST);
	}

	if (m_enableStencil) {
		if (m_stencilFunc != previous.m_stencilFunc 
			|| m_stencilRef != previous.m_stencilRef 
			|| m_stencilMask1 != previous.m_stencilMask1) {
			glStencilFunc(m_stencilFunc, m_stencilRef, m_stencilMask1);
		}

		if (m_stencilOps[0] != previous.m_stencilOps[0]
			|| m_stencilOps[1] != previous.m_stencilOps[1]
			|| m_stencilOps[2] != previous.m_stencilOps[2]) {
			glStencilOp(m_stencilOps[0], m_stencilOps[1], m_stencilOps[2]);
		}

		if (m_stencilMask2 != previous.m_stencilMask2) {
			glStencilMask(m_stencilMask2);
		}
	}
}

void gl::Context::checkErrors() const noexcept {
	if (GLenum err = glGetError(); err != GL_NO_ERROR) {
		switch (err) {
			case GL_INVALID_ENUM: io::Logger::logError("OpenGL error: invalid enum parameter"); break;
			case GL_INVALID_VALUE: io::Logger::logError("OpenGL error: invalid parameter value"); break;
			case GL_INVALID_OPERATION: io::Logger::logError("OpenGL error: invalid operation"); break;
			case GL_STACK_OVERFLOW: io::Logger::logError("OpenGL error: stack overflow"); break;
			case GL_STACK_UNDERFLOW: io::Logger::logError("OpenGL error: stack underflow"); break;
			case GL_OUT_OF_MEMORY: io::Logger::logError("OpenGL error: out of memory"); break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: io::Logger::logError("OpenGL error: invalid framebuffer operation"); break;
		default: break;
		}

		if (m_terminateUponError) {
			std::terminate();
		}
	}
}
