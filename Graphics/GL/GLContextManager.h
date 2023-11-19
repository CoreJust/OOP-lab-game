// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "GLContext.h"
#include "Utils/Concepts.h"

/*
*	GLContextManager(.h/.cpp) contains a class that allows convenient usage of several
*	OpenGL contexts.
* 
*	Usage:
*		gl::ContextManager manager;
*		gl::ContextManager::ContextRef context;
* 
*		manager.addContext(context).<some functions of the gl::Context for setting up>;
* 
*		...
*		
*		manager.newFrame();
* 
*		manager.forContext(context, []() {
*			// Some code using the context
*		});
* 
*		...
* 
*		manager.endFrame();
* 
* 
*		or in linear mode:
*		
*		manager.newFrame(context1);
*		...
*		manager.swapContexts(context2);
*		...
* 
*		manager.endFrame();
*/

namespace gl {
	class ContextManager final {
	public:
		using ContextRef = size_t; // Required for using the created context

	private:
		constexpr inline static ContextRef NO_CONTEXT = std::numeric_limits<ContextRef>::max();

	private:
		std::vector<Context> m_contexts;
		std::vector<ContextRef> m_contextsStack; // The stack of currently used contexts
		ContextRef m_previousContext = NO_CONTEXT;

		GLclampf m_clearColor[4] { 0.f, 0.f, 0.f, 1.f };
		GLbitfield m_clearedBuffers = GL_COLOR_BUFFER_BIT;

	public:
		Context& addContext(ContextRef& ref); // Stores the reference to the new Context to the ref
		Context& getContext(ContextRef context);

		// Clears the buffers and resets the states
		// If a context is passed, then begins it
		void newFrame(ContextRef context = NO_CONTEXT); 
		void endFrame();

		void swapContexts(ContextRef context); // Ends the previous context and starts a new one
		void begin(ContextRef context);
		void end();

		template<utils::Callable<void> Func>
		void forContext(ContextRef context, Func func) {
			begin(context);
			func();
			end();
		}

		constexpr void setClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a = 1.f) noexcept {
			assert(r >= 0.f && r <= 1.f);
			assert(g >= 0.f && g <= 1.f);
			assert(b >= 0.f && b <= 1.f);
			assert(a >= 0.f && a <= 1.f);

			m_clearColor[0] = r;
			m_clearColor[1] = g;
			m_clearColor[2] = b;
			m_clearColor[3] = a;
		}
	};
}
