#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    // TODO: Implement inventory destruction.
}

void Inventory::AddItem(Item* item)
{
    // TODO: Add an item.
}

void Inventory::RemoveItem(Item* item)
{
    // TODO: Remove an item.
}

void Inventory::UseItem(Item* item, Player& player)
{
    // TODO: Use an item.
}

const std::vector<Item*>& Inventory::GetItems() const
{
    // TODO: Return inventory items.
    return Items;
}
