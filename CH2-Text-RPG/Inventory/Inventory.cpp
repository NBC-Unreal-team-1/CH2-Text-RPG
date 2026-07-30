#include "Inventory.h"
#include "Item.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

//Id, Count로 인벤토리에 아이템 추가
void Inventory::AddItem(int ItemId, int Count)
{
    if (Count <= 0)
        return;

    if (InventorySlot* slot = FindSlot(ItemId))
    {
        slot->Count += Count; // 이미 있으면 수량만 증가
        return;
    }

    auto item = Item::CreateItem(ItemId); //아이템 생성

    if (item == nullptr)
    {
        return; // 존재하지 않는 id
    }

    Items.push_back({ std::move(item), Count }); //Inventory에 아이템 추가
}

void Inventory::RemoveItem(int ItemId, int Count)
{
    // TODO: Remove an item.
}

void Inventory::UseItem(int ItemId, Player& player)
{
    //TODO: 아이템 효과 적용, 수량 차감
}

const std::vector<InventorySlot>& Inventory::GetItems() const
{
    return Items;
}

InventorySlot* Inventory::FindSlot(int ItemId)
{
    //TODO: 반복문 돌면서 Id로 slot 찾기
    return  nullptr;
}

const InventorySlot* Inventory::FindSlot(int ItemId) const
{
    //TODO: 위 버젼의 const 버전.
    return  nullptr;
}

int Inventory::GetItemCount(int ItemId) const
{
    //TODO: 아이템 카운트 반환
}