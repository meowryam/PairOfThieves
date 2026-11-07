
#include "GUI/Player.h"

namespace vh
{
    // Constructor
    Player::Player(AssetManager& assets)
    {
        m_sprite = nullptr;

        m_position = { 640.f, 360.f };
        m_targetPosition = m_position;

        m_moveSpeed = 180.f;

        m_animationTimer = 0.f;
        m_frameDuration = 0.12f;

        m_currentFrame = 0;
        m_animationRow = 0;

        m_isMoving = false;

        // Get the explorer texture
        sf::Texture* heroTexture = assets.getTexture("hero");

        if (heroTexture != nullptr)
        {
            // Create the sprite using the loaded texture
            m_sprite = new sf::Sprite(*heroTexture);

            // Set the initial frame
            updateFrame();

            // Position from the bottom centre of the character
            m_sprite->setOrigin({ 8.f, 30.f });

            // Enlarge pixel art
            m_sprite->setScale({ 3.f, 3.f });

            m_sprite->setPosition(m_position);
        }
    }


    // Destructor
    Player::~Player()
    {
        delete m_sprite;

        m_sprite = nullptr;
    }


    // Set player position
    void Player::setPosition(sf::Vector2f position)
    {
        m_position = position;
        m_targetPosition = position;

        m_isMoving = false;

        m_currentFrame = 0;
        m_animationTimer = 0.f;

        updateFrame();

        if (m_sprite != nullptr)
        {
            m_sprite->setPosition(m_position);
        }
    }


    // Return player position
    sf::Vector2f Player::getPosition() const
    {
        return m_position;
    }


    // Choose walking direction
    void Player::updateDirection()
    {
        float dx = m_targetPosition.x - m_position.x;
        float dy = m_targetPosition.y - m_position.y;

        // Calculate absolute values
        if (dx < 0)
            dx = -dx;

        if (dy < 0)
            dy = -dy;

        if (dx > dy)
        {
            if (m_targetPosition.x < m_position.x)
                m_animationRow = 2;
            else
                m_animationRow = 3;
        }
        else
        {
            if (m_targetPosition.y < m_position.y)
                m_animationRow = 1;
            else
                m_animationRow = 0;
        }
    }


    // Move towards a destination
    void Player::moveTo(sf::Vector2f target)
    {
        if (m_sprite == nullptr)
            return;

        m_targetPosition = target;

        float dx = target.x - m_position.x;
        float dy = target.y - m_position.y;

        if (dx == 0.f && dy == 0.f)
            return;

        updateDirection();

        m_currentFrame = 0;
        m_animationTimer = 0.f;

        updateFrame();

        m_isMoving = true;
    }


    // Stop movement
    void Player::stop()
    {
        m_targetPosition = m_position;

        m_isMoving = false;

        m_currentFrame = 0;
        m_animationTimer = 0.f;

        updateFrame();
    }


    // Check movement
    bool Player::isMoving() const
    {
        return m_isMoving;
    }


    // Set animation row
    void Player::setAnimationRow(int row)
    {
        if (row < 0 || row >= 11)
            return;

        m_animationRow = row;

        m_currentFrame = 0;

        updateFrame();
    }


    // Update sprite frame
    void Player::updateFrame()
    {
        if (m_sprite == nullptr)
            return;

        sf::IntRect frame(
            { m_currentFrame * FRAME_WIDTH,
              m_animationRow * FRAME_HEIGHT },

            { FRAME_WIDTH, FRAME_HEIGHT }
        );

        m_sprite->setTextureRect(frame);
    }


    // Update player movement and animation
    void Player::update(float deltaTime)
    {
        if (!m_isMoving || m_sprite == nullptr)
            return;

        if (deltaTime <= 0.f)
            return;

        float dx = m_targetPosition.x - m_position.x;
        float dy = m_targetPosition.y - m_position.y;

        float absX = dx;
        float absY = dy;

        if (absX < 0)
            absX = -absX;

        if (absY < 0)
            absY = -absY;

        // Find the larger distance
        float distance = absX;

        if (absY > distance)
            distance = absY;

        // Calculate movement for this frame
        float movement = m_moveSpeed * deltaTime;

        if (distance <= movement)
        {
            // Destination reached
            m_position = m_targetPosition;

            m_isMoving = false;

            m_currentFrame = 0;
            m_animationTimer = 0.f;
        }
        else
        {
            // Move towards destination
            float ratio = movement / distance;

            m_position.x += dx * ratio;
            m_position.y += dy * ratio;

            // Update walking animation
            m_animationTimer += deltaTime;

            if (m_animationTimer >= m_frameDuration)
            {
                m_animationTimer -= m_frameDuration;

                m_currentFrame++;

                if (m_currentFrame >= TOTAL_FRAMES)
                    m_currentFrame = 0;

                updateFrame();
            }
        }

        m_sprite->setPosition(m_position);
    }


    // Draw player
    void Player::render(sf::RenderWindow& window)
    {
        if (m_sprite != nullptr)
        {
            window.draw(*m_sprite);
        }
    }


    // Change player display size
    void Player::setScale(float scale)
    {
        if (m_sprite != nullptr && scale > 0.f)
        {
            m_sprite->setScale({ scale, scale });
        }
    }


    // Check if sprite loaded correctly
    bool Player::isReady() const
    {
        return m_sprite != nullptr;
    }
}
