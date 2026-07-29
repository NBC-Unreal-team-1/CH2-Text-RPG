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

    // 아이템 추가 (소유권을 Inventory로 이전)
    void AddItem(std::unique_ptr<Item> item);

    // 아이템 제거 (id로 찾아서 벡터에서 제거 + 자동 소멸)
    void RemoveItem(int itemId);

    // 아이템 사용 (소유권 없이 참조만 사용)
    void UseItem(Item& item, Player& player);

    // 읽기 전용 접근 (raw pointer로 노출, 소유권은 여전히 Inventory)
    const std::vector<std::unique_ptr<Item>>& GetItems() const;

    // id로 아이템 찾기 (없으면 nullptr)
    Item* FindItem(int itemId) const;

protected:
private:
    //유니크 포인터로 이중 해제 방지
    std::vector<std::unique_ptr<Item>> Items;
};
