
#pragma once

#include <SFML/Graphics.hpp>

#include "GUI/AssetManager.h"
#include "GUI/Player.h"

namespace vh
{
    class Renderer;

    class JungleScene
    {
    private:

        static const int MAX_PROPS = 12;

        AssetManager* m_assets;
        Renderer* m_renderer;

        Player m_player;

        // Background
        sf::RectangleShape m_background;

        sf::Sprite* m_groundTile;

        // Jungle paths
        sf::RectangleShape m_horizontalPath;
        sf::RectangleShape m_verticalPath;

        sf::CircleShape m_clearings[3];

        // Decorative objects
        sf::Sprite* m_props[MAX_PROPS];

        int m_propCount;

        // Player path selection
        sf::FloatRect m_leftPathArea;
        sf::FloatRect m_rightPathArea;

        const char* m_statusMessage;


        // Add an object to the jungle
        bool addProp(
            const char* textureName,
            sf::Vector2f position,
            float scale
        );

        // Draw the grass background
        void drawGround(sf::RenderWindow& window);


    public:

        JungleScene(
            AssetManager& assets,
            Renderer& renderer
        );

        ~JungleScene();

        // Handle trail selection
        void handleEvent(const sf::Event& event);

        // Update player movement
        void update(float deltaTime);

        // Draw the jungle
        void render(sf::RenderWindow& window);
    };
}
