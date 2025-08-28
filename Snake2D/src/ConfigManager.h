#pragma once
#include <SFML/Graphics.hpp>
//#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

class ConfigManager {
private:
    nlohmann::json configJson;

    // Private constructor for singleton
    ConfigManager() {
        std::ifstream file("../src/gameConfig.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open config.json" << std::endl;
            return;
        }
        file >> configJson;
        file.close();
    }

public:
    // Delete copy constructor and assignment operator
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    // Singleton accessor
    static ConfigManager& GetInstance() {
        static ConfigManager instance;
        return instance;
    }

    // -------------------------
    // Window Settings
    // -------------------------
    int GetWindowWidth() const { return configJson["window"]["width"]; }
    int GetWindowHeight() const { return configJson["window"]["height"]; }
    std::string GetWindowTitle() const { return configJson["window"]["title"]; }

    // -------------------------
    // Textures
    // -------------------------
    std::string GetTexturePath(const std::string& key) const {
        return configJson["textures"][key]; }

    // -------------------------
    // Fonts
    // -------------------------
    std::string GetFontPath(const std::string& key) const { return configJson["fonts"][key]; }

    // -------------------------
    // Sounds
    // -------------------------
    std::string GetSoundPath(const std::string& key) const { return configJson["sounds"][key]; }

    // -------------------------
    // Button Texts
    // -------------------------
    std::string GetButtonText(const std::string& screen, const std::string& button) const {
        return configJson["buttons"][screen][button];
    }

    // -------------------------
    // Instructions
    // -------------------------
    std::vector<std::string> GetInstructions() const {
        std::vector<std::string> result;
        for (auto& instr : configJson["instructions"])
            result.push_back(instr);
        return result;
    }

    // -------------------------
    // Game Texts (Game Over, Score, etc.)
    // -------------------------
    std::string GetGameText(const std::string& key) const { return configJson["game_texts"][key]; }

    // -------------------------
    // Default Values
    // -------------------------
    template <typename T>
    T GetDefaultValue(const std::string& key) const {
        return configJson["default_values"][key].get<T>();
    }
};
