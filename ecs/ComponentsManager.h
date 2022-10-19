#pragma once

#include "Entity.h"
#include "ecs/Components/HealthComponent.h"
#include "ecs/Components/InteractionComponent.h"
#include "ecs/Components/LinearMovementComponent.h"
#include "ecs/Components/LookingDirComponent.h"
#include "ecs/Components/PlayerAnimationComponent.h"
#include "ecs/Components/PlayerCustomizationComponent.h"
#include "ecs/Components/PositionComponent.h"
#include "ecs/Components/ShootingDirComponent.h"
#include "ecs/Components/CharacterCharismaComponent.h"
#include "ecs/Components/CharacterMechanicsComponent.h"
#include "ecs/Components/CharacterMedicineComponent.h"
#include "ecs/Components/CharacterPetsFriendlinessComponent.h"
#include "ecs/Components/CharacterStaminaComponent.h"
#include "ecs/Components/InventoryComponent.h"

namespace ecs {
    template <typename T>
    class ComponentArray {
    public:
        T& RegisterEntity(Entity entity) {
            Components.push_back(T());
           auto result = EntityToIndex.emplace(entity, Components.size() - 1);
           CHECK(result.second);
           auto it = result.first;
           return Components[(*it).second];
        }
        void RemoveEntity(Entity entity) {
            if (Components.size() > 1)
            {
                const size_t removedEntityIdx = EntityToIndex[entity];
                for(auto& e : EntityToIndex) {
                    if (e.second == Components.size() - 1) {
                        e.second = removedEntityIdx;
                    }
                }
                std::swap(Components[removedEntityIdx], Components.back());
            }
            Components.pop_back();
            std::remove(EntityToIndex.begin(), EntityToIndex.end(), entity);
        }
        T& GetEntity(Entity entity) {
            auto found = EntityToIndex.find(entity);
            if(found != EntityToIndex.end()) {
                return Components[EntityToIndex[entity]];
            }
            DEAD_PATH();
            return NullObj;
        }
    private:
        inline static T NullObj;
        std::vector<T> Components;
        std::unordered_map<Entity, size_t> EntityToIndex;
    };

#define IMPL_ENTITY_ARRAY(Type)                         \
    public:                                             \
    Type& CONCAT(Register, Type)(Entity e) {             \
        return CONCAT(Type, Container).RegisterEntity(e);      \
    }                                                   \
    Type& CONCAT(Get, Type)(Entity e) {                 \
        return CONCAT(Type, Container).GetEntity(e);    \
    }                                                   \
    private:                                            \
    ComponentArray<Type> CONCAT(Type, Container);       \

    class ComponentsManager {
        IMPL_ENTITY_ARRAY(LinearMovementComponent);
        IMPL_ENTITY_ARRAY(PositionComponent);
        IMPL_ENTITY_ARRAY(LookingDirComponent);
        IMPL_ENTITY_ARRAY(ShootingDirComponent);
        IMPL_ENTITY_ARRAY(PlayerAnimationComponent);
        IMPL_ENTITY_ARRAY(PlayerCustomizationComponent);
        IMPL_ENTITY_ARRAY(HealthComponent);
        IMPL_ENTITY_ARRAY(InteractionComponent);
        IMPL_ENTITY_ARRAY(CharacterCharismaComponent);
        IMPL_ENTITY_ARRAY(CharacterMechanicsComponent);
        IMPL_ENTITY_ARRAY(CharacterMedicineComponent);
        IMPL_ENTITY_ARRAY(CharacterPetFriendlinessComponent);
        IMPL_ENTITY_ARRAY(CharacterStaminaComponent);
        IMPL_ENTITY_ARRAY(InventoryComponent);
    };
}