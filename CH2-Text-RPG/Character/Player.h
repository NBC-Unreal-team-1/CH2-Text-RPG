#pragma once

#include "Character.h"
#include "../Inventory/Inventory.h"

class Player : public Character
{
public:
    Player();
    ~Player() override;

    int GetExp() const;
    void SetExp(int exp);
    int GetGold() const;
    void SetGold(int gold);
    Inventory& GetInventory();
    const Inventory& GetInventory() const;

protected:
private:
    int Exp = 0;
    int Gold = 0;
    Inventory PlayerInventory;
};
