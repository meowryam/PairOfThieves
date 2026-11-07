
#pragma once

#include <SFML/Graphics.hpp>

namespace vh
{
    class Renderer
    {
    private:

        sf::Font m_font;
        bool m_fontLoaded = false;

    public:

        bool loadFont(const char* filePath);

        void drawRectangle(
            sf::RenderWindow& window,
            sf::Vector2f position,
            sf::Vector2f size,
            sf::Color fillColor
        );

        void drawCircle(
            sf::RenderWindow& window,
            sf::Vector2f center,
            float radius,
            sf::Color fillColor,
            sf::Color outlineColor
        );

        void drawLine(
            sf::RenderWindow& window,
            sf::Vector2f start,
            sf::Vector2f end,
            sf::Color color
        );

        void drawText(
            sf::RenderWindow& window,
            const char* message,
            sf::Vector2f position,
            unsigned int characterSize,
            sf::Color color
        );

        void drawNode(
            sf::RenderWindow& window,
            sf::Vector2f center,
            float radius,
            const char* label,
            sf::Color fillColor
        );
    };
}
