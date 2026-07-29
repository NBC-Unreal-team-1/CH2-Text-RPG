#include "Potion.h"

Potion::Potion(int Id, PotionType Type, int Amount)
    : Item(Id), Type(Type), Amount(Amount) {}

Potion::~Potion()
{
    // TODO: Implement potion destruction.
}

void Potion::Use(Player& player)
{
    // TODO: Use the potion.
}

PotionType Potion::GetType() const
{
    return this->Type;
}

int Potion::GetAmount() const
{
    return this->Amount;
}
