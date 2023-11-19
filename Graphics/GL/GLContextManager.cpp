// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLContextManager.h"

gl::Context& gl::ContextManager::addContext(ContextRef& ref) {
    ref = m_contexts.size();
    m_contexts.emplace_back();

    return m_contexts.back();
}

gl::Context& gl::ContextManager::getContext(ContextRef context) {
    assert(context < m_contexts.size());

    return m_contexts[context];
}

void gl::ContextManager::newFrame(ContextRef context) {
    assert(context < m_contexts.size() || context == NO_CONTEXT);
    assert(m_contextsStack.empty());
    assert(m_previousContext == NO_CONTEXT);

    m_clearedBuffers = GL_COLOR_BUFFER_BIT;
    for (auto& c : m_contexts) {
        m_clearedBuffers |= c.getEnabledBuffers();
    }

    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    glClear(m_clearedBuffers);

    if (context != NO_CONTEXT) {
        begin(context);
    }
}

void gl::ContextManager::endFrame() {
    if (m_contextsStack.size()) {
        getContext(m_contextsStack.back()).checkErrors();
        m_contextsStack.clear();
    }

    m_previousContext = NO_CONTEXT;
}

void gl::ContextManager::swapContexts(ContextRef context) {
    end();
    begin(context);
}

void gl::ContextManager::begin(ContextRef context) {
    assert(context < m_contexts.size());

    m_contextsStack.push_back(context);

    Context& c = getContext(context);
    if (m_previousContext != NO_CONTEXT) {
        c.use(getContext(m_previousContext));
    } else {
        c.use();
    }

    m_previousContext = context;
}

void gl::ContextManager::end() {
    assert(m_contextsStack.size());

    Context& c = getContext(m_contextsStack.back());
    m_contextsStack.pop_back();
    c.checkErrors();

    if (m_contextsStack.size()) {
        Context& restored = getContext(m_contextsStack.back());
        restored.use(c);
        m_previousContext = m_contextsStack.back();
    }
}
