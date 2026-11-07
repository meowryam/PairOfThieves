
#pragma once

#include <SFML/Graphics.hpp>

#include "GUI/Screen.h"

namespace vh
{
    // Forward declaration
    class AssetManager;

    class UIManager
    {
    private:

        Screen* m_currentScreen = nullptr;
        Screen* m_pendingScreen = nullptr;

        AssetManager* m_assetManager = nullptr;

        bool m_isCallingScreen = false;
        bool m_hasPendingScreen = false;

        void applyPendingScreen();

    public:

        UIManager() = default;

        ~UIManager();

        // Asset Manager
        void setAssetManager(AssetManager* assets);

        AssetManager* getAssetManager() const;

        // Screen management
        void setScreen(Screen* screen);

        void handleEvent(const sf::Event& event);

        void update(float deltaTime);

        void render(sf::RenderWindow& window);

        bool hasActiveScreen() const;
    };
}
