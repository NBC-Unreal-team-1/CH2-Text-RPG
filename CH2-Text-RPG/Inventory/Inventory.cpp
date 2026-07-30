#include "Inventory.h"
#include "Item.h"
#include <algorithm>

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

//Id로 Count 감소. Count가 0이하가 되면 erase.
bool Inventory::RemoveItem(int ItemId, int Count)
{
    if (Count <= 0)
    {
        return false;
    }

    InventorySlot* slot = FindSlot(ItemId);

    if (slot == nullptr)
    {
        return false; // 없는 아이템
    }

    slot->Count -= Count;

    if (slot->Count <= 0)
    {
        // 포인터 slot을 iterator로 변환. (인벤토리 아이템의 실제 주소 - Items의 첫 번째 원소의 실제 메모리 주소)로 Items 안에서의 로컬 주소 알아냄.
        auto it = Items.begin() + (slot - Items.data());

        Items.erase(it); // 수량 0 이하가 되면 슬롯 자체 제거 (Item 객체도 유니크 포인터이기에 자동 소멸)
    }

    return true;
}

void Inventory::UseItem(int ItemId, Player& player)
{
    //TODO: 아이템 효과 적용, 수량 차감
}

const std::vector<InventorySlot>& Inventory::GetItems() const
{
    return Items;
}

//아이템을 담고 있는 InventorySlot의 실제 메모리 주소 반환
InventorySlot* Inventory::FindSlot(int ItemId)
{
    //it는 인벤토리 아이템들 중 ItemId와 일치하는 아이템의 위치
    auto it = std::find_if(Items.begin(), Items.end(),
        [ItemId](const InventorySlot& slot)
        {
            return slot.ItemPtr->GetId() == ItemId;//조건(Id가 일치하면)이 참이면 곧바로 true 반환
        });

    return (it != Items.end()) ? &(*it) : nullptr; //찾았으면 주소 반환, 못찾았으면 nullptr 반환
}

//const버전의 FindSlot()
const InventorySlot* Inventory::FindSlot(int ItemId) const
{
    auto it = std::find_if(Items.begin(), Items.end(),
        [ItemId](const InventorySlot& slot)
        {
            return slot.ItemPtr->GetId() == ItemId; 
        });

    return (it != Items.end()) ? &(*it) : nullptr; 
}

int Inventory::GetItemCount(int ItemId) const
{
    //TODO: 아이템 카운트 반환
    return 0;
}