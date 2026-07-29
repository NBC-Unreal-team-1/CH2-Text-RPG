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
    void RemoveItem(int itemId);

    // 아이템 사용
    void UseItem(Item& item, Player& player);

    // 읽기 전용 접근
    const std::vector<std::unique_ptr<Item>>& GetItems() const;

    // id로 아이템 찾기 (없으면 nullptr)
    Item* FindItem(int itemId) const;

protected:
private:
    //유니크 포인터로 이중 해제 방지
    std::vector<std::unique_ptr<Item>> Items;
};
