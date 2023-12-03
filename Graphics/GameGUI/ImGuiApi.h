// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui/imgui.h>

#include "Utils/Concepts.h"
#include "Utils/NoNullptr.h"
#include "Graphics/Display.h"
#include "Alignment.h"

/*
*	ImGuiApi(.h/.cpp) contains a class that provides a convinient API
*	for ImGui functions.
* 
*	Usage:
*		ImGuiApi gui("name", "title");
*		gui.init(-display-);
*		...
*		// Somewhere in a cycle
*		if (gui.tryToBegin(-window-)) {
*			gui.setAlignment(Alignment::CENTERED);
*			gui.text("Text in the center");
* 
*			gui.setAlignment(Alignment::LEFT);
*			gui.newLine();
*			gui.separator();
* 
*			if (gui.button("exit")) {
*				gui.end();
*				return; // Or anything else to close it
*			}
* 
*			gui.end();
*		}
*/

namespace gamegui {
	class ImGuiApi final {
	private:
		Display* m_pDisplay = nullptr;
		const char* m_name;
		const char* m_title;
		ImGuiWindowFlags m_windowFlags;

		std::vector<char*> m_dummies;
		uint32_t m_dummyCounter = 0;

		float m_commonButtonWidth = 0.f;

		Alignment m_alignment = Alignment::LEFT;
		bool m_centerWindow;
		bool m_begun = false;

	public:
		ImGuiApi(const char* name, const char* title, const bool centerWindow = true, const bool allowScrolling = false);
		~ImGuiApi();

		void init(utils::NoNullptr<Display> pDisplay);
		void destroy();

		// Returns false if the menu was closed
		bool tryToBegin(sf::RenderWindow& window);
		void end();

		// GUIs
		void text(const char* text);
		void text(const float y, const char* text);
		bool button(const char* label = "##");
		bool button(const float x, const char* label = "##");
		bool inputText(std::string& contents, const char* label = ""); // Returns true upon change
		bool comboBox(const std::vector<const char*>& options, uint32_t& selected, const char* label = ""); // Returns true upon selection
		bool checkBox(bool& value, const char* label = "");
		bool sliderFloat(float& value, const float rangeMin, const float rangeMax, const char* label = "");
		bool sliderInt(int& value, const int rangeMin, const int rangeMax, const char* label = "");

		template<utils::Arithmetic T>
		bool slider(T& value, const T rangeMin, const T rangeMax, const char* label = "") {
			if constexpr (std::is_floating_point_v<T>) {
				float tmp = static_cast<float>(value);
				if (sliderFloat(tmp, static_cast<float>(rangeMin), static_cast<float>(rangeMax), label)) {
					value = tmp;
					return true;
				}

				return false;
			} else {
				static_assert(sizeof(T) <= sizeof(int));

				int tmp = static_cast<int>(value);
				if (sliderInt(tmp, static_cast<int>(rangeMin), static_cast<int>(rangeMax), label)) {
					value = tmp;
					return true;
				}

				return false;
			}
		}

		// Layout
		void newLine();
		void sameLine();
		void separator();
		void textSeparator(const char* text);

		void setCommonButtonWidth(const float width = 0.f);
		void setCommonButtonWidthForText(const char* text); // So that buttons can contain such text
		void setAlignment(const Alignment value);

	private:
		// Creates the label before an element
		// Makes the right offset, considering the centering
		void makeLabel(const char* label);

		// Note: it does not allocate any memory!
		const char* genUniqueDummy();
	};
}
