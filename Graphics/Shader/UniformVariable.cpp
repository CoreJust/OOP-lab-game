// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "UniformVariable.h"
#include "Graphics/GL/GLShader.h"

UniformVariable::UniformVariable(gl::Shader& shader, const Type type, const std::string& name) {
    initVariable(shader, type, name);
}

UniformVariable::UniformVariable(const UniformVariable& other) {
    if (this == &other) {
        return;
    }

    memcpy(this, &other, sizeof(*this));
}

UniformVariable& UniformVariable::operator=(const UniformVariable& other) {
    if (this == &other) {
        return *this;
    }

    memcpy(this, &other, sizeof(*this));
    return *this;
}

UniformVariable& UniformVariable::operator=(const bool value) {
    assert(m_type == Type::BOOL);

    m_asBool = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const GLint value) {
    assert(m_type == Type::INT);

    m_asInt = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const GLuint value) {
    assert(m_type == Type::UINT);

    m_asUint = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const GLfloat value) {
    assert(m_type == Type::FLOAT);

    m_asFloat = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const GLdouble value) {
    assert(m_type == Type::DOUBLE);

    m_asDouble = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const math::Vector2f& value) {
    assert(m_type == Type::VEC_2F);

    m_asVec2f = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const math::Vector2i& value) {
    assert(m_type == Type::VEC_2I);

    m_asVec2i = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const math::Vector2u& value) {
    assert(m_type == Type::VEC_2U);

    m_asVec2u = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const math::Vector2d& value) {
    assert(m_type == Type::VEC_2D);

    m_asVec2d = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const glm::vec2& value) {
    assert(m_type == Type::VEC_2F);

    m_asVec2f = { value.x, value.y };
    return *this;
}

UniformVariable& UniformVariable::operator=(const glm::vec3& value) {
    assert(m_type == Type::VEC_3F);

    m_asVec3 = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const glm::vec4& value) {
    assert(m_type == Type::VEC_4F);

    m_asVec4 = value;
    return *this;
}

UniformVariable& UniformVariable::operator=(const glm::mat4 value) {
    assert(m_type == Type::MATRIX_4F);

    m_asMat4 = value;
    return *this;
}

void UniformVariable::initVariable(gl::Shader& shader, Type type, const std::string& name) {
    m_type = type;
    m_id = shader.getVariableLocation((name.back() == '\0' ? name : name + "\0").c_str()).expect("Shader must contain a uniform variable " + toString() + " " + name);
}

void UniformVariable::loadToShader(gl::Shader& shader) {
    switch (m_type) {
        case UniformVariable::VOID: break;
        case UniformVariable::BOOL: shader.setVariable(m_id, m_asBool); break;
        case UniformVariable::INT: shader.setVariable(m_id, m_asInt); break;
        case UniformVariable::UINT: shader.setVariable(m_id, m_asUint); break;
        case UniformVariable::FLOAT: shader.setVariable(m_id, m_asFloat); break;
        case UniformVariable::DOUBLE: shader.setVariable(m_id, m_asDouble); break;
        case UniformVariable::VEC_2F: shader.setVariable(m_id, m_asVec2f); break;
        case UniformVariable::VEC_2I: shader.setVariable(m_id, m_asVec2i); break;
        case UniformVariable::VEC_2U: shader.setVariable(m_id, m_asVec2u); break;
        case UniformVariable::VEC_2D: shader.setVariable(m_id, m_asVec2d); break;
        case UniformVariable::VEC_3F: shader.setVariable(m_id, m_asVec3); break;
        case UniformVariable::VEC_4F: shader.setVariable(m_id, m_asVec4); break;
        case UniformVariable::MATRIX_4F: shader.setVariable(m_id, m_asMat4); break;
        case UniformVariable::NUMBER_TYPES: break;
    default: break;
    }
}

const std::string& UniformVariable::toString() const noexcept {
    const static std::string s_typeNames[] = {
        "void",
        "bool",
        "int",
        "uint",
        "float",
        "double",
        "vec2",
        "vec2i",
        "vec2u",
        "vec2d",
        "vec3",
        "vec4",
        "mat4"
    };

    assert(m_type < std::size(s_typeNames));

    return s_typeNames[m_type];
}
