
#pragma once

namespace vh
{
    class AnimationController
    {
    private:

        bool m_isPlaying;

        float m_speed;
        float m_timeSinceLastStep;
        float m_stepDuration;

        int m_currentStep;
        int m_totalSteps;

    public:

        AnimationController();

        // Set the number of animation steps
        void setTotalSteps(int totalSteps);

        // Playback controls
        void play();
        void pause();
        void togglePlayPause();

        void stepForward();

        void reset();
        void replay();

        // Control animation speed
        void setSpeed(float speed);

        // Update animation
        void update(float deltaTime);

        // Get current animation information
        bool isPlaying() const;
        int getCurrentStep() const;
        int getTotalSteps() const;
    };
}
