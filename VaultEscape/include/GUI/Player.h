
#pragma once

#include <SFML/Graphics.hpp>

#include "GUI/AssetManager.h"

namespace vh
{
    class Player
    {
    private:

        // Sprite dimensions
        static const int FRAME_WIDTH = 16;
        static const int FRAME_HEIGHT = 32;
        static const int TOTAL_FRAMES = 8;

        sf::Sprite* m_sprite;

        sf::Vector2f m_position;
        sf::Vector2f m_targetPosition;

        float m_moveSpeed;

        float m_animationTimer;
        float m_frameDuration;

        int m_currentFrame;
        int m_animationRow;

        bool m_isMoving;

        void updateDirection();

        void updateFrame();


    public:

        // Constructor and destructor
        Player(AssetManager& assets);

        ~Player();

        // Position
        void setPosition(sf::Vector2f position);

        sf::Vector2f getPosition() const;

        // Movement
        void moveTo(sf::Vector2f target);

        void stop();

        bool isMoving() const;

        // Animation
        void setAnimationRow(int row);

        void update(float deltaTime);

        // Drawing
        void render(sf::RenderWindow& window);

        // Display size
        void setScale(float scale);

        // Check whether the player loaded correctly
        bool isReady() const;
    };
}
