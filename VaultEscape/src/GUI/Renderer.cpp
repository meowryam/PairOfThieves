
#include "GUI/Renderer.h"



namespace vh
{
    bool Renderer::loadFont(const char* filePath)
    {
        m_fontLoaded = m_font.openFromFile(filePath);

        return m_fontLoaded;
    }


    void Renderer::drawRectangle(
        sf::RenderWindow& window,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color fillColor)
    {
        sf::RectangleShape rectangle(size);

        rectangle.setPosition(position);
        rectangle.setFillColor(fillColor);

        window.draw(rectangle);
    }


    void Renderer::drawCircle(
        sf::RenderWindow& window,
        sf::Vector2f center,
        float radius,
        sf::Color fillColor,
        sf::Color outlineColor)
    {
        sf::CircleShape circle(radius);

        circle.setOrigin({ radius, radius });
        circle.setPosition(center);

        circle.setFillColor(fillColor);
        circle.setOutlineColor(outlineColor);
        circle.setOutlineThickness(3.f);

        window.draw(circle);
    }


    void Renderer::drawLine(
        sf::RenderWindow& window,
        sf::Vector2f start,
        sf::Vector2f end,
        sf::Color color)
    {
        sf::Vertex line[2];

        line[0].position = start;
        line[0].color = color;

        line[1].position = end;
        line[1].color = color;

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }


    void Renderer::drawText(
        sf::RenderWindow& window,
        const char* message,
        sf::Vector2f position,
        unsigned int characterSize,
        sf::Color color)
    {
        if (!m_fontLoaded)
            return;

        sf::Text text(m_font, message, characterSize);

        text.setPosition(position);
        text.setFillColor(color);

        window.draw(text);
    }


    void Renderer::drawNode(
        sf::RenderWindow& window,
        sf::Vector2f center,
        float radius,
        const char* label,
        sf::Color fillColor)
    {
        sf::CircleShape node(radius);

        node.setOrigin({ radius, radius });
        node.setPosition(center);

        node.setFillColor(fillColor);
        node.setOutlineColor(sf::Color(244, 197, 66));
        node.setOutlineThickness(3.f);

        window.draw(node);

        if (m_fontLoaded)
        {
            sf::Text text(m_font, label, 20);

            sf::FloatRect bounds = text.getLocalBounds();

            text.setOrigin(bounds.getCenter());
            text.setPosition(center);

            text.setFillColor(sf::Color(255, 240, 203));

            window.draw(text);
        }
    }
}
