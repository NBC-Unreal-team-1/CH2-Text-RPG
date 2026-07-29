#pragma once

#include "Item.h"

class AttackPotion : public Item
{
public:
    AttackPotion();
    ~AttackPotion() override;

    void Use(Player& player) override;

protected:
private:
};
