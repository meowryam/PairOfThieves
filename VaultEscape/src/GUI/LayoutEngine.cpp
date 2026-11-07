
#include "GUI/LayoutEngine.h"

namespace vh
{
    sf::Vector2f LayoutEngine::calculateTreePosition(
        int depth,
        int positionInLevel,
        float windowWidth) const
    {
        if (depth < 0 || positionInLevel < 0)
            return sf::Vector2f(0.f, 0.f);

        int totalSlots = 1;

        for (int i = 0; i < depth; i++)
        {
            totalSlots = totalSlots * 2;
        }

        if (positionInLevel >= totalSlots || windowWidth <= 0)
            return sf::Vector2f(0.f, 0.f);

        float spacing = windowWidth / (totalSlots + 1);

        float x = spacing * (positionInLevel + 1);

        float y = 100.f + (depth * 110.f);

        return sf::Vector2f(x, y);
    }


    sf::Vector2f LayoutEngine::calculateArrayCellPosition(
        int index,
        float startX,
        float startY,
        float cellWidth,
        float gap
    ) const
    {
        if (index < 0 || cellWidth <= 0)
            return sf::Vector2f(0.f, 0.f);

        float x = startX + index * (cellWidth + gap);

        float y = startY;

        return sf::Vector2f(x, y);
    }
}
