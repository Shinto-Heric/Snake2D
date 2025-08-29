#pragma once
#include "Button.h"

class ToggleButton : public Button {
private:
    bool m_enabled = true;
    sf::Texture* m_enabledTexture = nullptr;
    sf::Texture* m_disabledTexture = nullptr;

    void ApplyTexture();

public:
    ToggleButton();

    void SetTextures(sf::Texture* enabledTex, sf::Texture* disabledTex);

    void SetEnabled(bool enabled);
    bool IsEnabled() const;

    void Toggle();

    void Render(sf::RenderWindow& window) override;

    void SetToggleCallback(std::function<void(bool)> callback);
};
