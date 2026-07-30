#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

const std::string& Character::GetName() const
{
    return Name;
}

void Character::SetName(const std::string& name)
{
    Name = name;
}

int Character::GetLevel() const
{
    return Level;
}

void Character::SetLevel(int level)
{
    Level = level;
}

int Character::GetMaxHp() const
{
    return MaxHp;
}

void Character::SetMaxHp(int maxHp)
{
    MaxHp = maxHp;
}

int Character::GetCurrentHp() const
{
    return CurrentHp;
}

void Character::SetCurrentHp(int currentHp)
{
    if (currentHp < 0)
    {
        CurrentHp = 0;
        return;
    }

    CurrentHp = currentHp;
}

int Character::GetMaxMp() const
{
    return MaxMp;
}

void Character::SetMaxMp(int maxMp)
{
    MaxMp = maxMp;
}

int Character::GetCurrentMp() const
{
    return CurrentMp;
}

void Character::SetCurrentMp(int currentMp)
{
    CurrentMp = currentMp;
}

int Character::GetPower() const
{
    return Power;
}

void Character::SetPower(int power)
{
    Power = power;
}

int Character::GetDefence() const
{
    return Defence;
}

void Character::SetDefence(int defence)
{
    Defence = defence;
}

void Character::TakeDamage(int damage)
{
    if (damage < 0)
    {
        return;
    }

    SetCurrentHp(CurrentHp - damage);
}

bool Character::IsAlive() const
{
    return CurrentHp > 0;
}