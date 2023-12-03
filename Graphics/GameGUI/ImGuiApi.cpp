// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ImGuiApi.h"

#include <imgui/imgui-SFML.h>
#include <imgui/imgui_stdlib.h>

#include "Audio/AudioMaster.h"

gamegui::ImGuiApi::ImGuiApi(const char* name, const char* title, const bool centerWindow, const bool allowScrolling)
    : m_name(name), m_title(title), m_centerWindow(centerWindow) {
    assert(name != nullptr);
    assert(title != nullptr);

    m_windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
    if (!allowScrolling) {
        m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
    }
}

gamegui::ImGuiApi::~ImGuiApi() {
    for (auto& dummy : m_dummies) {
        if (dummy) {
            delete dummy;
            dummy = nullptr;
        }
    }
}

void gamegui::ImGuiApi::init(utils::NoNullptr<Display> pDisplay) {
    m_pDisplay = pDisplay.get();

    ImGui::GetIO().FontGlobalScale = 2.f;
    m_pDisplay->update(); // So that the graphics can be enabled for ImGui mode
}

void gamegui::ImGuiApi::destroy() {
    m_pDisplay = nullptr;
}

bool gamegui::ImGuiApi::tryToBegin(sf::RenderWindow& window) {
    assert(!m_begun);
    assert(m_pDisplay != nullptr);

    ImGui::SFML::SetCurrentWindow(window);
    if (!m_pDisplay->isOpen()) {
        return false;
    }

    if (m_centerWindow) {
        ImGui::SetNextWindowPos({ window.getSize().x / 2.f, window.getSize().y / 2.f }, 0, { 0.5f, 0.5f });
    }

    ImGui::Begin(m_name, nullptr, m_windowFlags);
    setAlignment(Alignment::CENTERED);
    text(0.1f, m_title);
    newLine();

    m_dummyCounter = 0;
    m_begun = true;
    return true;
}

void gamegui::ImGuiApi::end() {
    assert(m_begun);

    ImGui::End();
    ImGui::EndFrame();
    m_pDisplay->clear(sf::Color::Black);

    m_begun = false;
}

void gamegui::ImGuiApi::text(const char* text) {
    assert(m_begun);

    if (m_alignment == Alignment::CENTERED || m_alignment == Alignment::CENTERED_BY_ELEMENTS) {
        const float windowWidth = ImGui::GetWindowSize().x;
        const float textWidth = ImGui::CalcTextSize(text).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    }

    ImGui::Text(text);
}

void gamegui::ImGuiApi::text(const float y, const char* text) {
    assert(m_begun); 
    
    if (m_alignment == Alignment::CENTERED || m_alignment == Alignment::CENTERED_BY_ELEMENTS) {
        const float windowWidth = ImGui::GetWindowSize().x;
        const float textWidth = ImGui::CalcTextSize(text).x;

        ImGui::SetCursorPos({ (windowWidth - textWidth) * 0.5f, m_pDisplay->getWindow().getSize().y * y });
    } else {
        ImGui::SetCursorPosY(y);
    }

    ImGui::Text(text);
}

bool gamegui::ImGuiApi::button(const char* label) {
    assert(m_begun);

    float textWidth = ImGui::CalcTextSize(label).x;
    if (m_commonButtonWidth > textWidth) {
        textWidth = m_commonButtonWidth;
    }

    if (m_alignment == Alignment::CENTERED || m_alignment == Alignment::CENTERED_BY_ELEMENTS) {
        const float windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    }

    if (ImGui::Button(label, { textWidth, 0 })) {
        audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);

        return true;
    }

    return false;
}

bool gamegui::ImGuiApi::button(const float x, const char* label) {
    assert(m_begun);

    float textWidth = ImGui::CalcTextSize(label).x;
    if (m_commonButtonWidth > textWidth) {
        textWidth = m_commonButtonWidth;
    }

    ImGui::SetCursorPosX(x);

    if (ImGui::Button(label, { textWidth, 0 })) {
        audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);

        return true;
    }

    return false;
}

bool gamegui::ImGuiApi::inputText(std::string& contents, const char* label) {
    assert(m_begun);

    makeLabel(label);
    
    return ImGui::InputText(genUniqueDummy(), &contents);
}

bool gamegui::ImGuiApi::comboBox(const std::vector<const char*>& options, uint32_t& selected, const char* label) {
    assert(m_begun);

    makeLabel(label);

    bool result = false;
    if (ImGui::BeginCombo(genUniqueDummy(), options[selected])) {
        for (uint32_t i = 0; i < options.size(); i++) {
            const bool isSelected = i == selected;
            if (ImGui::Selectable(options[i], isSelected)) {
                selected = i;
                result = true;

                audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return result;
}

bool gamegui::ImGuiApi::checkBox(bool& value, const char* label) {
    assert(m_begun);

    makeLabel(label);

    if (ImGui::Checkbox(genUniqueDummy(), &value)) {
        audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);

        return true;
    }

    return false;
}

bool gamegui::ImGuiApi::sliderFloat(float& value, const float rangeMin, const float rangeMax, const char* label) {
    assert(m_begun);

    makeLabel(label);

    return ImGui::SliderFloat(genUniqueDummy(), &value, rangeMin, rangeMax, "%.1f", ImGuiSliderFlags_AlwaysClamp);
}

bool gamegui::ImGuiApi::sliderInt(int& value, const int rangeMin, const int rangeMax, const char* label) {
    assert(m_begun);

    makeLabel(label);

    return ImGui::SliderInt(genUniqueDummy(), &value, rangeMin, rangeMax, "%d", ImGuiSliderFlags_AlwaysClamp);
}

void gamegui::ImGuiApi::newLine() {
    assert(m_begun);

    ImGui::NewLine();
}

void gamegui::ImGuiApi::sameLine() {
    assert(m_begun);

    ImGui::SameLine();
}

void gamegui::ImGuiApi::separator() {
    assert(m_begun);

    ImGui::Separator();
}

void gamegui::ImGuiApi::textSeparator(const char* text) {
    assert(m_begun);

    ImGui::SeparatorText(text);
}

void gamegui::ImGuiApi::setCommonButtonWidth(const float width) {
    m_commonButtonWidth = width;
}

void gamegui::ImGuiApi::setCommonButtonWidthForText(const char* text) {
    setCommonButtonWidth(ImGui::CalcTextSize(text).x);
}

void gamegui::ImGuiApi::setAlignment(const Alignment value) {
    m_alignment = value;
}

void gamegui::ImGuiApi::makeLabel(const char* label) {
    const float labelSize = ImGui::CalcTextSize(label).x;
    float labelStartX = 0.f;

    switch (m_alignment) {
        case Alignment::LEFT: break;
        case Alignment::CENTERED:
            labelStartX = (ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth() - labelSize) / 2.f; 
            break;
        case Alignment::CENTERED_BY_ELEMENTS:
            labelStartX = (ImGui::GetWindowContentRegionMax().x / 2.f) - labelSize;
            break;
    default: break;
    }

    ImGui::SetCursorPosX(labelStartX);

    if (label[0]) {
        ImGui::Text(label);
        ImGui::SameLine();
    }
}

const char* gamegui::ImGuiApi::genUniqueDummy() {
    if (m_dummyCounter++ >= m_dummies.size()) {
        m_dummies.push_back(new char[10]);
        char* dummy = m_dummies.back();

        memset(dummy, 0, 10);
        dummy[0] = '#';
        dummy[1] = '#';

        uint32_t uniqueId = m_dummyCounter;
        uint32_t i = 2;
        while (uniqueId) {
            dummy[i++] = '0' + (uniqueId % 10);
            uniqueId /= 10;
        }
    }

    return m_dummies[m_dummyCounter - 1];
}
