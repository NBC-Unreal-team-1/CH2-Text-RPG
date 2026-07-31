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
bool Inventory::ReduceItem(int ItemId, int Count)
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

    // 보유 개수보다 많이 줄이려 하면 실패
    if (slot->Count - Count < 0)
    {
        return false;
    }

    // Count만큼 수량 감소
    slot->Count -= Count;

    if (slot->Count == 0)
    {
        return RemoveItem(ItemId);
    }

    return true;
}

//아이템 슬롯 제거
bool Inventory::RemoveItem(int ItemId)
{
    InventorySlot* slot = FindSlot(ItemId);
    if (slot == nullptr)
    {
        return false; // 없는 아이템
    }

    auto it = Items.begin() + (slot - Items.data());
    Items.erase(it); // 수량과 상관없이 슬롯 전체 제거

    return true;
}

bool Inventory::UseItem(int ItemId, Player& player)
{
    InventorySlot* slot = FindSlot(ItemId); //Id로 인벤토리에 있는 아이템 검색

    // 없는 아이템은 사용 불가
    if (slot == nullptr)
    {
        return false; 
    }

    //타입이 포션일 때만 수행 가능
    if (slot->ItemPtr->GetItemType() == ItemType::Potion)
    {
        slot->ItemPtr->Use(player); // 효과 적용

        ReduceItem(ItemId, 1);      // 사용한 만큼 수량 차감

        return true;
    }

    return false;
}


//모든 아이템들 반환
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
    //아이템이 존재하는지 찾기
    const InventorySlot* slot = FindSlot(ItemId);

    //아이템이 존재하면 Count 반환.
    return (slot != nullptr) ? slot->Count : 0;
}

//아이템이 존재하는지만 확인
bool Inventory::HasItem(int ItemId)
{
    InventorySlot* slot = FindSlot(ItemId); //Id로 인벤토리에 있는 아이템 검색

    if (slot == nullptr)
    { 
        return false; // 아이템이 없음
    }

    return true;
}