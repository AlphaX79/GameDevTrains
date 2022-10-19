#pragma once

#include "game_modules/InventoryModule.h"

namespace ecs {
    struct InventoryComponent {
        std::vector<Gameplay::Item> Items;
    };
}// namespace ecs
