#include "Inventory.h"
#include "Item.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(std::unique_ptr<Item> Item)
{
    if (Item == nullptr)
    {
        return;
    }

    //유니크 포인터 소유권 이전(Item->Inventory)
    Items.push_back(std::move(Item));
}

void Inventory::RemoveItem(int ItemId)
{
    // TODO: Remove an item.
}

void Inventory::UseItem(Item& Item, Player& player)
{
    // TODO: Use an item.
}

const std::vector<std::unique_ptr<Item>>& Inventory::GetItems() const
{
    return Items;
}

Item* Inventory::FindItem(int ItemId) const
{
    return nullptr;
}
