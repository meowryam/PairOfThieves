
#pragma once

#include <SFML/Graphics.hpp>

#include "GUI/AssetManager.h"
#include "GUI/Renderer.h"
#include "GUI/UIManager.h"

namespace vh
{
    class Application
    {
    private:

        static constexpr unsigned int WINDOW_WIDTH = 1280;
        static constexpr unsigned int WINDOW_HEIGHT = 720;

        sf::RenderWindow m_window;
        sf::Clock m_clock;

        AssetManager m_assetManager;

        Renderer m_renderer;
        UIManager m_uiManager;

        bool m_assetsLoaded = false;

        void processEvents();

        void update(float deltaTime);

        void render();

    public:

        Application();

        void run();
    };
}
