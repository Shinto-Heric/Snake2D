#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {
public:
    static SoundManager& GetInstance();

    // Music
    bool LoadMusic(const std::string& filename);
    void PlayMusic();
    void StopMusic();
    void SetMusicVolume(float volume); // 0-100
    void SetMusicEnabled(bool enabled);
    bool IsMusicEnabled() const { return m_musicEnabled; }

    // Effects
    bool LoadEffect(const std::string& key, const std::string& filename);
    void PlayEffect(const std::string& key);
    void SetEffectsVolume(float volume); // 0-100
    void SetEffectsEnabled(bool enabled);
    bool AreEffectsEnabled() const { return m_effectsEnabled; }

private:
    SoundManager() = default;

    sf::Music m_music;
    float m_musicVolume = 100.f;
    bool m_musicEnabled = true;

    std::map<std::string, sf::SoundBuffer> m_buffers;
    std::map<std::string, sf::Sound> m_sounds;
    float m_effectsVolume = 100.f;
    bool m_effectsEnabled = true;
};
