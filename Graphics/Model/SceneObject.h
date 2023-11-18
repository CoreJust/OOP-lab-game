// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

/*
*	SceneObject.h contains a struct that represents an object within the scene.
* 
*	An object has 2 characteristics: the position and the rotation.
*	This struct is expected to be used via aggregation, not inheritance or something alike.
*/

namespace model {
	struct SceneObject {
		glm::vec3 pos = { 0, 0, 0 };
		glm::vec3 rot = { 0, 0, 0 };

		inline glm::mat4 genMatrix() const noexcept {
			glm::mat4 result(1.f);

			result = glm::translate(result, pos);

			result = glm::rotate(result, rot.x, { 1, 0, 0 });
			result = glm::rotate(result, rot.y, { 0, 1, 0 });
			result = glm::rotate(result, rot.z, { 0, 0, 1 });

			return result;
		}

		constexpr SceneObject& move(const glm::vec3& shift) noexcept {
			pos += shift;
			return *this;
		}

		// Rotation around the center of the object
		constexpr SceneObject& rotate(const glm::vec3& angles) noexcept {
			rot += angles;
			return *this;
		}

		constexpr SceneObject combinedWith(const SceneObject& other) noexcept {
			return SceneObject { 
				.pos = pos + other.pos,
				.rot = rot + other.rot
			};
		}

		// Rotates the position, but own rotation remains unchanged
		inline SceneObject& rotatePos(const glm::vec3& center, const glm::vec3& angles) noexcept {
			pos -= center; // So that the center is (0, 0, 0)

			glm::rotateX(pos, angles.x);
			glm::rotateY(pos, angles.y);
			glm::rotateZ(pos, angles.z);

			pos += center; // Translate back

			return *this;
		}

		// Rotates the object around the center
		inline SceneObject& rotateAround(const glm::vec3& center, const glm::vec3& angles) noexcept {
			rotatePos(center, angles);
			rotate(angles);

			return *this;
		}

		// Moves the object to/from the center according to the factor
		// (the distance to the center is multiplied by the factor)
		constexpr SceneObject& scaleTo(const glm::vec3& center, const float factor) noexcept {
			// For how much should we shift the object so that it gets to the center
			const glm::vec3 fullShift = center - pos;
			move(fullShift * (1.f - factor));

			return *this;
		}
	};
}