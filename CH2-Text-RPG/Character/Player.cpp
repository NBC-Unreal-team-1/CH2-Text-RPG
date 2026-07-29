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
    // TODO: Return player experience.
    return {};
}

void Player::SetExp(int exp)
{
    // TODO: Set player experience.
}

int Player::GetGold() const
{
    // TODO: Return player gold.
    return {};
}

void Player::SetGold(int gold)
{
    // TODO: Set player gold.
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
