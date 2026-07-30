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

void Player::SetExp(int Exp)
{
    this->Exp = Exp;
}

int Player::GetGold() const
{
    return Gold;
}

void Player::SetGold(int Gold)
{
    this->Gold = Gold;
}

void Player::AddGold(int Gold)
{
    if (Gold <= 0)
    {
        return;
    }
    this->Gold += Gold;
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
