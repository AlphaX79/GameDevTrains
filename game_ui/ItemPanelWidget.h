#pragma once

#include "ui/Box.h"
//#include "ui/Text.h"
#include "game_modules/InventoryModule.h"

namespace UI {
    struct ItemPanelWidget : UI::UIItem {
        
        ItemPanelWidget(Math::Vec3f const &position, Math::Vec2f const &Size)
            : UI::UIItem(position, Size) {
            ItemSlots[2] = new UI::Box(position, SingleSlotSize, Math::LinearColor::White);//First because it is in a center and others positions are dependent on this one size
            
            ItemSlots[1] = new UI::Box({position.X - (offset+SingleSlotSize.X), position.Y, position.Z}, SingleSlotSize, Math::LinearColor::White);
            ItemSlots[0] = new UI::Box({ItemSlots[1]->Position.X - (offset + SingleSlotSize.X), position.Y, position.Z}, SingleSlotSize, Math::LinearColor::White);
                    
            ItemSlots[3] = new UI::Box({position.X + (offset + SingleSlotSize.X), position.Y, position.Z}, SingleSlotSize, Math::LinearColor::White);
            ItemSlots[4] = new UI::Box({ItemSlots[3]->Position.X + (offset + SingleSlotSize.X), position.Y, position.Z}, SingleSlotSize, Math::LinearColor::White);
            
            for (i8 i = 0; i < MAX_SLOT_AMMOUNT; ++i) {
                ItemNames[i] = new UI::Text(TEXT(""), {ItemSlots[i]->Position.X, ItemSlots[i]->Position.Y + textoffset, ItemSlots[i]->Position.Z}, UI::HorizontalAlignment::Center);  
            }
         
        };

        void AssociateInventory(Gameplay::Inventory* inventory) {
            AssociatedInventory = inventory;
        }

        void UpdateItemPanel(const i8 player_index) {
            //Drawing item texture
            for (i8 i = 0; i < AssociatedInventory->GetItemsCount();++i) {
                ItemSlots[i]->Material.Color = AssociatedInventory->GetItemAt(i)->ItemImage;
            }

            for (auto& slots : ItemSlots) {
                slots->Size = SizeOriginal;
                slots->Recreate = true;
            }
            ItemSlots[SelectedItem]->Size = SizeBoosted;
            ItemSlots[SelectedItem]->Recreate = true;

            for (i8 i = 0; i < MAX_SLOT_AMMOUNT; ++i) {
                if (AssociatedInventory->GetItemAt(i)) {
                    ItemNames[i]->SetText(AssociatedInventory->GetItemAt(i)->ItemName);
                }
               
            }      
        }

        void RequestLeftItem() {
            SelectedItem = (SelectedItem - 1) % MAX_SLOT_AMMOUNT;
            if (SelectedItem < 0) {
                SelectedItem = MAX_SLOT_AMMOUNT - 1;
            }
        }

        void RequestRightItem() {
            SelectedItem = (SelectedItem + 1) % MAX_SLOT_AMMOUNT;
        }
        i32 GetRequestedItemIndex() const {
            return SelectedItem;
        }

        virtual void Draw(DrawContext &context) {
            for (auto& slot : ItemSlots) {
                slot->Draw(context);
            }
            for (auto& name : ItemNames) {
                name->Draw(context);
            }
        }

    private:
        static inline constexpr u8 MAX_SLOT_AMMOUNT = 5;
        float offset =  0.025f;
        Math::Vec2f SingleSlotSize = {(Size.X - ((MAX_SLOT_AMMOUNT - 1) * offset)) / MAX_SLOT_AMMOUNT, Size.Y};
        Math::Vec2f SizeBoosted = {SingleSlotSize.X + 0.02f, SingleSlotSize.Y + 0.02f};
        Math::Vec2f SizeOriginal = {SingleSlotSize.X, SingleSlotSize.Y};
        float textoffset = SingleSlotSize.Y / 2 + 0.015f;
        darray<Gameplay::Inventory> Inventories;
        Gameplay::Inventory* AssociatedInventory = nullptr;
        i32 SelectedItem = 0;
        std::array<Memory::UniquePtr<UI::Box>, MAX_SLOT_AMMOUNT> ItemSlots;
        std::array<Memory::UniquePtr<UI::Text>, MAX_SLOT_AMMOUNT> ItemNames;
    };
}
