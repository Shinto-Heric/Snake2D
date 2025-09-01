#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::GetInstance() {
    static SoundManager instance;
    return instance;
}

// ------------------- MUSIC -------------------
bool SoundManager::LoadMusic(const std::string& filename) {
    if (!m_music.openFromFile(filename)) {
        std::cerr << "Failed to load music: " << filename << "\n";
        return false;
    }
    m_music.setLoop(true);
    m_music.setVolume(m_musicVolume);
    return true;
}

void SoundManager::PlayMusic() {
    if (m_musicEnabled) {
        m_music.play();
    }
}

void SoundManager::StopMusic() {
    m_music.stop();
}

void SoundManager::SetMusicVolume(float volume) {
    m_musicVolume = volume;
    m_music.setVolume(m_musicVolume);
}

void SoundManager::SetMusicEnabled(bool enabled) {
    m_musicEnabled = enabled;
    if (!m_musicEnabled) {
        m_music.stop();
    }
    else {
        m_music.play();
    }
}

// ------------------- EFFECTS -------------------
bool SoundManager::LoadEffect(const std::string& key, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load effect: " << filename << "\n";
        return false;
    }

    // insert keeps buffer alive
    m_buffers[key] = buffer;
    sf::Sound sound;
    sound.setBuffer(m_buffers[key]);
    sound.setVolume(m_effectsVolume);
    m_sounds[key] = sound;

    return true;
}

void SoundManager::PlayEffect(const std::string& key) {
    if (!m_effectsEnabled) return;

    auto it = m_sounds.find(key);
    if (it != m_sounds.end()) {
        it->second.stop(); // restart from beginning
        it->second.play();
    }
}

void SoundManager::SetEffectsVolume(float volume) {
    m_effectsVolume = volume;
    for (auto& pair : m_sounds) {
        pair.second.setVolume(m_effectsVolume);
    }
}

void SoundManager::SetEffectsEnabled(bool enabled) {
    m_effectsEnabled = enabled;
}
