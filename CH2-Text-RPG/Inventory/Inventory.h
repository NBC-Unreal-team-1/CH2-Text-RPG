#pragma once

#include <vector>
#include<memory>
class Item;
class Player;

struct InventorySlot
{
    std::unique_ptr<Item> ItemPtr;
    int Count;
};

class Inventory
{
public:
    Inventory();
    ~Inventory();

    // 아이템 추가
    void AddItem(int ItemId, int Count = 1);

    // 아이템 제거
    bool RemoveItem(int ItemId, int Count = 1);

    // 아이템 사용
    void UseItem(int ItemId, Player& player);

    // 인벤토리 전체 Get
    const std::vector<InventorySlot>& GetItems() const;

    // Id로 아이템 찾기 (없으면 nullptr)
    InventorySlot* FindSlot(int ItemId);
    const InventorySlot* FindSlot(int ItemId) const;

    //특정 아이템의 보유 개수 반환
    int GetItemCount(int ItemId) const;

protected:
private:
    //유니크 포인터로 이중 해제 방지
    std::vector<InventorySlot> Items;
};
