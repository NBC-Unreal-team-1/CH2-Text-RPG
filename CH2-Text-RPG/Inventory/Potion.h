#pragma once

#include "Item.h"

class Potion : public Item
{
public:
    Potion();
    ~Potion() override;

    void Use(Player& player) override;

protected:
private:
};
