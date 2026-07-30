#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
    // TODO: Implement player destruction.
}

int Player::GetExp() const
{
    return Exp;
}

void Player::SetExp(int exp)
{
    Exp = exp;
}

int Player::GetGold() const
{
    return Gold;
}

void Player::SetGold(int gold)
{
    Gold = gold;
}

Inventory& Player::GetInventory()
{
    // TODO: Return the player inventory.
    return PlayerInventory;
}

const Inventory& Player::GetInventory() const
{
    // TODO: Return the player inventory.
    return PlayerInventory;
}
