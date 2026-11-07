
#include "GUI/AnimationController.h"

namespace vh
{
    // Constructor
    AnimationController::AnimationController()
    {
        m_isPlaying = false;

        m_speed = 1.0f;
        m_timeSinceLastStep = 0.f;
        m_stepDuration = 0.5f;

        m_currentStep = 0;
        m_totalSteps = 0;
    }


    // Set total animation steps
    void AnimationController::setTotalSteps(int totalSteps)
    {
        if (totalSteps < 0)
            totalSteps = 0;

        m_totalSteps = totalSteps;

        if (m_currentStep > m_totalSteps)
            m_currentStep = m_totalSteps;

        if (m_currentStep >= m_totalSteps)
            pause();
    }


    // Start playing
    void AnimationController::play()
    {
        if (m_currentStep < m_totalSteps)
        {
            m_isPlaying = true;
        }
    }


    // Pause animation
    void AnimationController::pause()
    {
        m_isPlaying = false;
        m_timeSinceLastStep = 0.f;
    }


    // Toggle between play and pause
    void AnimationController::togglePlayPause()
    {
        if (m_isPlaying)
            pause();
        else
            play();
    }


    // Move forward by one step
    void AnimationController::stepForward()
    {
        pause();

        if (m_currentStep < m_totalSteps)
        {
            m_currentStep++;
        }
    }


    // Reset animation
    void AnimationController::reset()
    {
        pause();

        m_currentStep = 0;
    }


    // Replay from the beginning
    void AnimationController::replay()
    {
        reset();

        play();
    }


    // Set playback speed
    void AnimationController::setSpeed(float speed)
    {
        if (speed < 0.25f)
            speed = 0.25f;

        if (speed > 4.0f)
            speed = 4.0f;

        m_speed = speed;
    }


    // Update animation timing
    void AnimationController::update(float deltaTime)
    {
        if (!m_isPlaying)
            return;

        if (m_totalSteps <= 0)
        {
            pause();
            return;
        }

        m_timeSinceLastStep += deltaTime;

        float requiredTime = m_stepDuration / m_speed;

        while (m_timeSinceLastStep >= requiredTime && m_isPlaying)
        {
            m_timeSinceLastStep -= requiredTime;

            if (m_currentStep < m_totalSteps)
            {
                m_currentStep++;
            }

            if (m_currentStep >= m_totalSteps)
            {
                pause();
            }
        }
    }


    // Check playback status
    bool AnimationController::isPlaying() const
    {
        return m_isPlaying;
    }


    // Get current step
    int AnimationController::getCurrentStep() const
    {
        return m_currentStep;
    }


    // Get total steps
    int AnimationController::getTotalSteps() const
    {
        return m_totalSteps;
    }
}
