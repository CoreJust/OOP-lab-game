// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"

// Basic id class for resources - textures, animations, audio, etc
class BasicResourceId : public BasicId {
public:
	constexpr BasicResourceId(const id_t id) noexcept : BasicId(id) { }

	virtual std::string getResourceLocation() const = 0;
};