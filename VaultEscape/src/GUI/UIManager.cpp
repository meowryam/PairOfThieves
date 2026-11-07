
#include "GUI/UIManager.h"

namespace vh
{
    // Destructor
    UIManager::~UIManager()
    {
        delete m_currentScreen;
        delete m_pendingScreen;
    }


    // Set the AssetManager
    void UIManager::setAssetManager(AssetManager* assets)
    {
        m_assetManager = assets;
    }


    // Get the AssetManager
    AssetManager* UIManager::getAssetManager() const
    {
        return m_assetManager;
    }


    // Change the current screen
    void UIManager::setScreen(Screen* screen)
    {
        if (m_isCallingScreen)
        {
            delete m_pendingScreen;

            m_pendingScreen = screen;
            m_hasPendingScreen = true;
        }
        else
        {
            delete m_currentScreen;

            m_currentScreen = screen;
        }
    }


    // Apply the requested screen change
    void UIManager::applyPendingScreen()
    {
        if (m_hasPendingScreen)
        {
            delete m_currentScreen;

            m_currentScreen = m_pendingScreen;
            m_pendingScreen = nullptr;

            m_hasPendingScreen = false;
        }
    }


    // Handle events
    void UIManager::handleEvent(const sf::Event& event)
    {
        if (m_currentScreen)
        {
            m_isCallingScreen = true;

            m_currentScreen->handleEvent(event);

            m_isCallingScreen = false;

            applyPendingScreen();
        }
    }


    // Update screen
    void UIManager::update(float deltaTime)
    {
        if (m_currentScreen)
        {
            m_isCallingScreen = true;

            m_currentScreen->update(deltaTime);

            m_isCallingScreen = false;

            applyPendingScreen();
        }
    }


    // Render screen
    void UIManager::render(sf::RenderWindow& window)
    {
        if (m_currentScreen)
        {
            m_isCallingScreen = true;

            m_currentScreen->render(window);

            m_isCallingScreen = false;

            applyPendingScreen();
        }
    }


    // Check active screen
    bool UIManager::hasActiveScreen() const
    {
        return m_currentScreen != nullptr;
    }
}
