#pragma once

#include <vector>

class Item;
class Player;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void AddItem(Item* item);
    void RemoveItem(Item* item);
    void UseItem(Item* item, Player& player);
    const std::vector<Item*>& GetItems() const;

protected:
private:
    std::vector<Item*> Items;
};
