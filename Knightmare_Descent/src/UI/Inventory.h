#pragma once

#include <Azyris.h>

class Item
{
public:
    std::string name;
    int id;
    ImTextureID icon;  // Texture for ImGui rendering
    int stackSize;  // Optional: How many can stack in one slot
    // Constructor

    Item(std::string itemName, int itemId, ImTextureID itemIcon = 0, int stack = 1)
        : name(itemName), id(itemId), icon(itemIcon), stackSize(stack) {
    }

    // Render item in ImGui (optional)
    void Render(ImVec2 size = ImVec2(50, 50)) const {
        if (icon) {
            ImGui::Image(icon, size);
        }
        else {
            ImGui::Button(name.c_str(), size);
        }
    }
};

class InventorySlot
{
public:
    Item* item = nullptr;  // Pointer to an item (nullptr if empty)

    InventorySlot() : item(nullptr) {}

    void SetItem(Item* newItem) { item = newItem; }
    void Clear() { item = nullptr; }

    bool IsEmpty() const { return item == nullptr; }
};


class Inventory
{
public:

    Inventory() = default;

    std::vector<InventorySlot> m_Slots;
    int maxSlots;

    Inventory(int slots, const std::string& name) : maxSlots(slots) {
        SetInventoryProp(slots);
        SetName(name);
    }

    void SetInventoryProp(uint32_t slots, uint32_t columns = 8, float size = 100.0f, float padding = 10.0f);

    void SetSlotSize(float size);
    void SetPadding(float padding);
    void SetCollumns(uint32_t columns);

    void SetName(const std::string& name);

    bool AddItem(Item* item) {
        for (auto& slot : m_Slots) {
            if (slot.IsEmpty()) {
                slot.SetItem(item);
                return true;
            }
        }
        return false;  // Inventory full
    }

    void Render();

private:

    uint32_t m_Columns = 8;
    float m_SlotSize = 100.0f;
    float m_Padding = 10.0f;
    uint32_t m_Rows = 0;

    float m_InventoryWidth = 0;
    float m_InventoryHeight = 0;

    std::string m_Name = "Inventory";

};

