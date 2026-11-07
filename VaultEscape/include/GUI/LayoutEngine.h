
#pragma once

#include <SFML/Graphics.hpp>

namespace vh
{
    class LayoutEngine
    {
    public:

        sf::Vector2f calculateTreePosition(
            int depth,
            int positionInLevel,
            float windowWidth
        ) const;


        sf::Vector2f calculateArrayCellPosition(
            int index,
            float startX,
            float startY,
            float cellWidth,
            float gap
        ) const;
    };
}
