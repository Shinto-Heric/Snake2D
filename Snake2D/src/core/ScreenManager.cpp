#include "Game.h"
#include "core/ScreenManager.h"


void ScreenManager::ProcessTransitions() {
    // Close popup request first
    if (m_requestClosePopup) {
        m_activePopup.reset();
        m_requestClosePopup = false;
    }

    // Then apply next popup (if any)
    if (m_nextPopup) {
        m_activePopup = std::move(m_nextPopup);
    }

    // Finally apply next screen (if any). Usually a screen change should
    // also discard any popup (already handled by m_requestClosePopup above).
    if (m_nextScreen) {
        m_currentScreen = std::move(m_nextScreen);
    }
}

// -------------------- Public API --------------------

void ScreenManager::SetScreen(std::unique_ptr<BaseScreen> screen) {
    // Defer the switch to the end of the frame
    m_nextScreen = std::move(screen);
    // Close any active popup when screen changes
    m_requestClosePopup = true;
}

void ScreenManager::ShowPopup(std::unique_ptr<PopupBase> popup) {
    // Defer popup display to end of frame
    m_nextPopup = std::move(popup);
}

void ScreenManager::ClosePopup() {
    // Defer popup close to end of frame
    m_requestClosePopup = true;
}

void ScreenManager::CloseGame() {
    if (!m_game) return;
    m_game->CloseWindow();
}

// -------------------- Loop hooks --------------------

void ScreenManager::HandleInput(sf::Event& event, sf::RenderWindow& window) {
    // Route input to popup first (if shown), otherwise to screen
    if (m_activePopup) {
        m_activePopup->HandleInput(event, window);
    }
    else if (m_currentScreen) {
        m_currentScreen->HandleInput(event, window);
    }
    // Do NOT process transitions here; let Update do it once per frame
}

void ScreenManager::Update(sf::Time dt) {
    if (m_currentScreen)  m_currentScreen->Update(dt);
    if (m_activePopup)    m_activePopup->Update(dt);

    // Apply any queued changes at a single safe point
    ProcessTransitions();
}

void ScreenManager::Render(sf::RenderWindow& window) {
    if (m_currentScreen)  m_currentScreen->Render(window);
    if (m_activePopup)    m_activePopup->Render(window);
}
