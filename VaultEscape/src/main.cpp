
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }),
        "For W <3"
    );

    window.setFramerateLimit(60);

    sf::Clock clock;

    // Create W using lines
    sf::RectangleShape wLines[4];

    sf::Vector2f startPoints[4] =
    {
        { 280.f, 390.f },
        { 340.f, 490.f },
        { 400.f, 390.f },
        { 460.f, 490.f }
    };

    sf::Vector2f endPoints[4] =
    {
        { 340.f, 490.f },
        { 400.f, 390.f },
        { 460.f, 490.f },
        { 520.f, 390.f }
    };

    for (int i = 0; i < 4; i++)
    {
        float dx = endPoints[i].x - startPoints[i].x;
        float dy = endPoints[i].y - startPoints[i].y;

        float length = std::sqrt(dx * dx + dy * dy);
        float angle = std::atan2(dy, dx) * 180.f / 3.14159f;

        wLines[i].setSize({ length, 12.f });
        wLines[i].setOrigin({ 0.f, 6.f });
        wLines[i].setPosition(startPoints[i]);
        wLines[i].setRotation(sf::degrees(angle));
    }

    // Heart positions
    std::vector<sf::Vector2f> positions =
    {
        {350.f, 100.f},
        {430.f, 130.f},
        {270.f, 150.f},
        {380.f, 210.f},
        {490.f, 230.f},
        {290.f, 270.f},
        {420.f, 300.f}
    };

    while (window.isOpen())
    {
        // Handle events
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();

        window.clear(sf::Color(20, 10, 30));

        // Draw hearts
        for (int i = 0; i < static_cast<int>(positions.size()); i++)
        {
            float delay = i * 0.4f;

            if (time < delay)
                continue;

            float localTime = time - delay;

            // Heart pulsing
            float scale = 1.f + 0.10f * std::sin(localTime * 4.f);

            // Heart blinking
            float blink = (std::sin(localTime * 3.f) + 1.f) / 2.f;

            std::uint8_t alpha =
                static_cast<std::uint8_t>(130 + blink * 125);

            sf::Color pink(255, 65, 145, alpha);

            // Create actual heart shape
            sf::ConvexShape heart(12);

            heart.setPoint(0, { 30.f, 55.f });
            heart.setPoint(1, { 5.f, 32.f });
            heart.setPoint(2, { 0.f, 21.f });
            heart.setPoint(3, { 3.f, 10.f });
            heart.setPoint(4, { 13.f, 3.f });
            heart.setPoint(5, { 25.f, 5.f });
            heart.setPoint(6, { 30.f, 13.f });
            heart.setPoint(7, { 35.f, 5.f });
            heart.setPoint(8, { 47.f, 3.f });
            heart.setPoint(9, { 57.f, 10.f });
            heart.setPoint(10, { 60.f, 21.f });
            heart.setPoint(11, { 55.f, 32.f });

            heart.setFillColor(pink);

            heart.setOrigin({ 30.f, 30.f });

            heart.setPosition({
                positions[i].x + 30.f,
                positions[i].y + 30.f
                });

            heart.setScale({ scale, scale });

            window.draw(heart);
        }


        // W blinking
        float wAlpha = (std::sin(time * 2.f) + 1.f) / 2.f;

        sf::Color wPink(
            255,
            100,
            180,
            static_cast<std::uint8_t>(120 + wAlpha * 135)
        );

        for (int i = 0; i < 4; i++)
        {
            wLines[i].setFillColor(wPink);
            window.draw(wLines[i]);
        }

        window.display();
    }

    return 0;
}
