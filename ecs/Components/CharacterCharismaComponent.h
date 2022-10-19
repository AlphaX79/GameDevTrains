#pragma once

#include "BasicTypes.h"

namespace ecs {
    struct CharacterCharismaComponent {
        i8 Charisma;
        i8 CharismaBoostDuration;
        i8 MagazineSize;
        f32 FireRateModifier;
    };
}// namespace ecs
