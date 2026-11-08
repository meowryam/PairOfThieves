#pragma once
// Shared basic types. Everything under src/model is pure C++: NO SFML includes allowed.

namespace vh {

using NodeId = int;                    // unique within one tree; GUI tracks nodes by this id
constexpr NodeId INVALID_ID = -1;

enum class Side { NONE, LEFT, RIGHT };
enum class RotationType { NONE, LL, RR, LR, RL };
enum class TreeKind { BINARY, BST, AVL, MAX_HEAP };

} // namespace vh
