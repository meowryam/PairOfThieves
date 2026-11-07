
#pragma once

#include <SFML/Graphics.hpp>

namespace vh
{
    class Renderer
    {
    private:

        // Main interface font
        sf::Font m_font;

        // Decorative title font
        sf::Font m_titleFont;

        bool m_fontLoaded = false;
        bool m_titleFontLoaded = false;

    public:

        // Load fonts
        bool loadFont(const char* filePath);

        bool loadTitleFont(const char* filePath);


        // Draw basic shapes
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


        // Draw normal interface text
        void drawText(
            sf::RenderWindow& window,
            const char* message,
            sf::Vector2f position,
            unsigned int characterSize,
            sf::Color color
        );


        // Draw decorative title text
        void drawTitleText(
            sf::RenderWindow& window,
            const char* message,
            sf::Vector2f position,
            unsigned int characterSize,
            sf::Color color
        );


        // Draw tree nodes
        void drawNode(
            sf::RenderWindow& window,
            sf::Vector2f center,
            float radius,
            const char* label,
            sf::Color fillColor
        );
    };
}
