#pragma once
#include "Utils/BasicId.h"

// Basic id class for resources - textures, animations, audio, etc
class BasicResourceId : public BasicId {
public:
	constexpr BasicResourceId(id_t id) noexcept : BasicId(id) { }

	virtual std::string getResourceLocation() const = 0;
};