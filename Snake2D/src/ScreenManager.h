#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include "BaseScreen.h"
#include "PopupBase.h"

class Game;

// Central manager for one active screen and (optionally) one active popup.
// All transitions are deferred to avoid destroying objects mid-frame.
class ScreenManager {
private:
    // Active
    std::unique_ptr<BaseScreen> m_currentScreen;
    std::unique_ptr<PopupBase>  m_activePopup;

    // Deferred (applied in ProcessTransitions)
    std::unique_ptr<BaseScreen> m_nextScreen;
    std::unique_ptr<PopupBase>  m_nextPopup;
    bool m_requestClosePopup = false;

    Game* m_game = nullptr;

    ScreenManager() = default;

    // Applies queued transitions safely (call once per frame)
    void ProcessTransitions();

public:
    static ScreenManager& GetInstance() {
        static ScreenManager instance;
        return instance;
    }

    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;

    // One-time init to keep a pointer back to the Game
    void Init(Game* game) { m_game = game; }

    // ----- Screen control (deferred) -----
    void SetScreen(std::unique_ptr<BaseScreen> screen); // queues screen switch

    template <typename TScreen, typename... Args>
    void SwitchToScreen(Args&&... args) {
        // Construct the next screen, but don't activate it yet
        m_nextScreen = std::make_unique<TScreen>(std::forward<Args>(args)...);
        // Closing any popup on screen change is usually desirable:
        m_requestClosePopup = true;
    }

    // Convenience (if you want explicit names; remove if unused)
    void SwitchToGameplay();
    void SwitchToMainMenu();
    void CloseGame();

    // ----- Popup control (deferred) -----
    void ShowPopup(std::unique_ptr<PopupBase> popup); // queues popup show

    template <typename TPopup, typename... Args>
    void ShowPopup(Args&&... args) {
        m_nextPopup = std::make_unique<TPopup>(std::forward<Args>(args)...);
    }

    void ClosePopup(); // queues popup close

    // ----- Main loop hooks -----
    void HandleInput(sf::Event& event, sf::RenderWindow& window);
    void Update(sf::Time dt);
    void Render(sf::RenderWindow& window);
};
