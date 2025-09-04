#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class AssetManager {
private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;

    AssetManager() = default; // Private constructor for singleton

public:
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    static AssetManager& GetInstance();

    // Texture management
    void LoadTexture(const std::string& key, const std::string& path);
    sf::Texture& GetTexture(const std::string& key);

    // Font management
    void LoadFont(const std::string& key, const std::string& path);
    sf::Font& GetFont(const std::string& key);

    // Sound management
    void LoadSound(const std::string& key, const std::string& path);
    sf::SoundBuffer& GetSound(const std::string& key);
};
