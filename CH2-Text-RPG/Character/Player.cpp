#include "Player.h"

Player::Player()
{
    Skills.emplace_back(
        1,
        "Ä®",
        50,
        10,
        SkillTriggerType::EveryNthTurn,
        2
    );

    Skills.emplace_back(
        2,
        "ÇÁ¶óÀÌÆÒ",
        70,
        15,
        SkillTriggerType::PlayerHpBelow,
        50
    );
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

const Skill* Player::GetSkillById(int Id) const
{
    for (const Skill& CurrentSkill : Skills)
    {
        if (CurrentSkill.GetId() == Id)
        {
            return &CurrentSkill;
        }
    }
    return nullptr;
}