#include "core/AssetManager.h"

// Singleton accessor
AssetManager& AssetManager::GetInstance() {
    static AssetManager instance;
    return instance;
}

// -------------------------
// Texture
// -------------------------
void AssetManager::LoadTexture(const std::string& key, const std::string& path) {
    sf::Texture tex;
    if (tex.loadFromFile(path))
        m_textures[key] = tex;
    else
        std::cerr << "Failed to load texture: " << path << std::endl;
}

sf::Texture& AssetManager::GetTexture(const std::string& key) {
    return m_textures.at(key);
}

// -------------------------
// Font
// -------------------------
void AssetManager::LoadFont(const std::string& key, const std::string& path) {
    sf::Font font;
    if (font.loadFromFile(path))
        m_fonts[key] = font;
    else
        std::cerr << "Failed to load font: " << path << std::endl;
}

sf::Font& AssetManager::GetFont(const std::string& key) {
    return m_fonts.at(key);
}

// -------------------------
// Sound
// -------------------------
void AssetManager::LoadSound(const std::string& key, const std::string& path) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path))
        m_sounds[key] = buffer;
    else
        std::cerr << "Failed to load sound: " << path << std::endl;
}

sf::SoundBuffer& AssetManager::GetSound(const std::string& key) {
    return m_sounds.at(key);
}
