#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

constexpr auto GAME_CONFIG_NAME = "../assets/configs/gameConfig.json";

class GameConfigManager {
private:
    nlohmann::json configJson;

    // Private constructor for singleton
    GameConfigManager() {
        std::ifstream file(GAME_CONFIG_NAME);
        if (!file.is_open()) {
            std::cerr << "Failed to open config.json" << std::endl;
            return;
        }
        file >> configJson;
        file.close();
    }

public:
    // Delete copy constructor and assignment operator
    GameConfigManager(const GameConfigManager&) = delete;
    GameConfigManager& operator=(const GameConfigManager&) = delete;

    // Singleton accessor
    static GameConfigManager& GetInstance() {
        static GameConfigManager instance;
        return instance;
    }

    // -------------------------
    // Window Settings
    // -------------------------
    int GetWindowWidth() const { return configJson["window"]["width"]; }
    int GetWindowHeight() const { return configJson["window"]["height"]; }
    std::string GetWindowTitle() const { return configJson["window"]["title"]; }

    // -------------------------
    // Grid Settings
    // -------------------------
    int GetColumnSize() const { return configJson["grid"]["nCols"]; }
    int GetRowSize() const { return configJson["grid"]["nRows"]; }
    int GetCellSize() const { return configJson["grid"]["cellSize"]; }

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
};
