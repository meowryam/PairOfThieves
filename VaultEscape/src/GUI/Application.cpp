
#include "GUI/Application.h"

#include "GUI/Screens.h"
#include "GUI/Theme.h"

namespace vh
{
    // Constructor
    Application::Application()
        : m_window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Vault Heist | Jungle Adventures"
        )
    {
        m_window.setFramerateLimit(60);
       
        // Load the font
        m_renderer.loadFont("assets/fonts/PixelifySans-SemiBold.ttf");
        m_renderer.loadTitleFont("assets/fonts/PressStart2P-Regular.ttf");

        m_assetsLoaded = m_assetManager.loadJungleAssets();

        // Give UIManager access to the loaded assets
        m_uiManager.setAssetManager(&m_assetManager);

        // Start with the Main Menu
        m_uiManager.setScreen(
            new MainMenuScreen(m_uiManager, m_renderer)
        );
        
    }


    // Main application loop
    void Application::run()
    {
        while (m_window.isOpen())
        {
            processEvents();

            if (!m_window.isOpen())
                break;

            sf::Time frameTime = m_clock.restart();

            update(frameTime.asSeconds());

            render();
        }
    }


    // Handle window and screen events
    void Application::processEvents()
    {
        while (const auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                break;
            }

            if (const auto* keyPressed =
                event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    m_window.close();
                    break;
                }
            }

            if (m_uiManager.hasActiveScreen())
            {
                m_uiManager.handleEvent(*event);
            }
        }
    }


    // Update current screen
    void Application::update(float deltaTime)
    {
        if (m_uiManager.hasActiveScreen())
        {
            m_uiManager.update(deltaTime);
        }
    }


    // Render current screen
    void Application::render()
    {
        m_window.clear(Theme::DeepJungle);

        if (m_uiManager.hasActiveScreen())
        {
            m_uiManager.render(m_window);
        }

        m_window.display();
    }
}
