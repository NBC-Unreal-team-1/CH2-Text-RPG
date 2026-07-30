#pragma once

#include <vector>
#include<memory>

class Item;
class Player;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    // 아이템 추가
    void AddItem(std::unique_ptr<Item> item);

    // 아이템 제거
    void RemoveItem(int ItemId);

    // 아이템 사용
    void UseItem(Item& Item, Player& player);

    // 인벤토리 전체 Get
    const std::vector<std::unique_ptr<Item>>& GetItems() const;

    // Id로 아이템 찾기 (없으면 nullptr)
    Item* FindItem(int ItemId) const;

protected:
private:
    //유니크 포인터로 이중 해제 방지
    std::vector<std::unique_ptr<Item>> Items;
};
