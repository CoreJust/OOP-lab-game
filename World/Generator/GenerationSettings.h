// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>
#include <cassert>
#include <memory>
#include "Utils/BasicId.h"

/*
*	GenerationSettings(.h/.cpp) contains a class of the settings that define a generation stage.
*
*	Each setting consists of a flag which represents the generator (the class) and its work mode
*	(or algorithm used) and a generator-specific set of sub-settings.
* 
*	Other than that, each setting has a seed (a generator is completely deterministic based on the seed
*	- so with the same seed you would have the same generated output for some settings set).
*/

struct GenerationSettings {
	enum GenerationFlags : uint8_t {
		// Absolutely random generation, initial only
		RANDOM_WHITE_NOISE = 0,

		// Noise generation
		NOISE_PERLIN_BASIC,

		// Maze generation
		// Used information from: https://www.astrolog.org/labyrnth/algrithm.htm
		MAZE_PERFECT, // no loops/inaccessible areas - always one way from a point to another one
		MAZE_BRAID, // No dead ends (but with loops)
		MAZE_UNICURSAL, // Single way - no junctions
		MAZE_SPARSE, // A lot of unused space - a number of rooms and areas without passages

		// Cellular automatons
		CA_CUSTOM,
		CA_ARCHIPELAGO,

		// Post-generators (to fix something in the generated world
		POSTGEN_PASSAGE_CREATOR,

		// Generates the world not based on the procedural generation but on some fixed template
		TEMPLATE_GENERATOR,

		NUMBER_GENERATION_FLAGS
	};


	///  Subtypes for certain generators  ///

	struct RandomGenerationSettings {

	};

	struct NoiseGenerationSettings {
		uint8_t octaves; // the number of sequential noises being summed
		float frequency; // the noise scale
		float persistance; // the reduction of impact of each next octave
	};

	struct MazeGenerationSettings {

	};

	struct CellularAutomatonGenerationSettings {
		uint32_t steps;
	};

	struct PostGenerationSettings {

	};

	struct TemplateGenerationSettings {
		id_t id;
		int64_t data; // Some additional data for the specific ids
	};


	///  Fields  ///

	size_t seed;
	GenerationFlags flags;

	union {
		RandomGenerationSettings randomSets;
		NoiseGenerationSettings noiseSets;
		MazeGenerationSettings mazeSets;
		CellularAutomatonGenerationSettings cellASets;
		PostGenerationSettings postGenSets;
		TemplateGenerationSettings templateSets;
	};


	///  Methods  ///

	constexpr GenerationSettings(GenerationSettings&& other) noexcept
		: seed(other.seed), flags(other.flags) {
		if (other.isRandom()) {
			randomSets = std::move(other.randomSets);
		} else if (other.isNoise()) {
			noiseSets = std::move(other.noiseSets);
		} else if (other.isMaze()) {
			mazeSets = std::move(other.mazeSets);
		} else if (other.isCellularAutomaton()) {
			cellASets = std::move(other.cellASets);
		} else if (other.isPostGen()) {
			postGenSets = std::move(other.postGenSets);
		} else if (other.isTemplateGen()) {
			templateSets = std::move(other.templateSets);
		}
	}

	constexpr GenerationSettings(const GenerationSettings& other) noexcept
		: seed(other.seed), flags(other.flags) {
		if (other.isRandom()) {
			randomSets = other.randomSets;
		} else if (other.isNoise()) {
			noiseSets = other.noiseSets;
		} else if (other.isMaze()) {
			mazeSets = other.mazeSets;
		} else if (other.isCellularAutomaton()) {
			cellASets = other.cellASets;
		} else if (other.isPostGen()) {
			postGenSets = other.postGenSets;
		} else if (other.isTemplateGen()) {
			templateSets = other.templateSets;
		}
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, RandomGenerationSettings sets)
		: seed(seed), flags(flags), randomSets(std::move(sets)) {
		assert(isRandom());
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, NoiseGenerationSettings sets)
		: seed(seed), flags(flags), noiseSets(std::move(sets)) {
		assert(isNoise());
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, MazeGenerationSettings sets)
		: seed(seed), flags(flags), mazeSets(std::move(sets)) {
		assert(isMaze());
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, CellularAutomatonGenerationSettings sets)
		: seed(seed), flags(flags), cellASets(std::move(sets)) {
		assert(isCellularAutomaton());
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, PostGenerationSettings sets)
		: seed(seed), flags(flags), postGenSets(std::move(sets)) {
		assert(isPostGen());
	}

	constexpr GenerationSettings(size_t seed, GenerationFlags flags, TemplateGenerationSettings sets)
		: seed(seed), flags(flags), templateSets(std::move(sets)) {
		assert(isTemplateGen());
	}

	constexpr bool isRandom() const noexcept {
		return flags < NOISE_PERLIN_BASIC;
	}

	constexpr bool isNoise() const noexcept {
		return flags >= NOISE_PERLIN_BASIC && flags < MAZE_PERFECT;
	}

	constexpr bool isMaze() const noexcept {
		return flags >= MAZE_PERFECT && flags < CA_CUSTOM;
	}

	constexpr bool isCellularAutomaton() const noexcept {
		return flags >= CA_ARCHIPELAGO && flags < POSTGEN_PASSAGE_CREATOR;
	}

	constexpr bool isPostGen() const noexcept {
		return flags >= POSTGEN_PASSAGE_CREATOR && flags < TEMPLATE_GENERATOR;
	}

	constexpr bool isTemplateGen() const noexcept {
		return flags == TEMPLATE_GENERATOR;
	}

	constexpr bool canBeInitial() const noexcept {
		return isRandom() || isNoise() || isMaze() || isTemplateGen();
	}

	constexpr bool canBeConsecutive() const noexcept {
		return isMaze() || isCellularAutomaton() || isPostGen();
	}
};