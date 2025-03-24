#include <Inventory.h>
#include <utils/Helpers.h>
#include <Renderer/Renderer.h>


void Inventory::SetInventoryProp(uint32_t slots, uint32_t columns, float size, float padding)
{
    m_Slots.resize(slots);
    m_Columns = columns;
    m_SlotSize = size;
    m_Padding = padding;

    m_Rows = (m_Slots.size() + columns - 1) / columns;

    m_InventoryWidth = (columns * size) + ((columns - 1) * padding) + 20;
    m_InventoryHeight = (m_Rows * m_SlotSize) + ((m_Rows - 1) * m_Padding) + 40;
}

void Inventory::SetSlotSize(float size)
{
    m_SlotSize = size;

    m_InventoryWidth = (m_Columns * size) + ((m_Columns - 1) * m_Padding) + 20;
    m_InventoryHeight = (m_Rows * m_SlotSize) + ((m_Rows - 1) * m_Padding) + 40;
}

void Inventory::SetPadding(float padding)
{
    m_Padding = padding;

    m_InventoryWidth = (m_Columns * m_SlotSize) + ((m_Columns - 1) * m_Padding) + 20;
    m_InventoryHeight = (m_Rows * m_SlotSize) + ((m_Rows - 1) * m_Padding) + 40;
}

void Inventory::SetCollumns(uint32_t columns)
{
    m_Columns = columns;

    m_Rows = (m_Slots.size() + columns - 1) / columns;

    m_InventoryWidth = (m_Columns * m_SlotSize) + ((m_Columns - 1) * m_Padding) + 20;
    m_InventoryHeight = (m_Rows * m_SlotSize) + ((m_Rows - 1) * m_Padding) + 40;
}

void Inventory::SetName(const std::string& name)
{
    m_Name = name;
}

void Inventory::Render()
{
    AZ_Assert(Az::Renderer::batchRunning() != true, "Batcher is running!!");
    AZ_Assert(Az::ImGuiLayer::ReadyToDraw() != false, "ImGUI is not initialized!!");

    ImGui::SetNextWindowSize(ImVec2(m_InventoryWidth, m_InventoryHeight));
    ImGui::Begin(m_Name.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);

    // Draw inventory grid
    for (int i = 0; i < m_Slots.size(); i++) {
        InventorySlot& slot = m_Slots[i];

        // Get current cursor position
        ImVec2 cursorPos = ImGui::GetCursorPos();

        // Render slot (empty or with an item)
        if (slot.IsEmpty()) {
            std::string name = "Slot: " + std::to_string(i);
            ImGui::Button(name.c_str(), ImVec2(m_SlotSize, m_SlotSize));
        }
        else {
            ImGui::Image(slot.item->icon, ImVec2(m_SlotSize, m_SlotSize));

            // Handle item click
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                slot.Clear();
            }
        }

        // Manually set position for next slot to control spacing
        if ((i + 1) % m_Columns != 0) {
            ImGui::SetCursorPos(ImVec2(cursorPos.x + m_SlotSize + m_Padding, cursorPos.y));
        }
        else {
            ImGui::SetCursorPos(ImVec2(10, cursorPos.y + m_SlotSize + m_Padding));  // New row
        }
    }

    ImGui::End();
}


    