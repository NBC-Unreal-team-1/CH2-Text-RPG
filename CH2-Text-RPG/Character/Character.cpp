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

void Character::SetName(const std::string& Name)
{
    this->Name = Name;
}

int Character::GetLevel() const
{
    return Level;
}

void Character::SetLevel(int Level)
{
    this->Level = Level;
}

int Character::GetMaxHp() const
{
    return MaxHp;
}

void Character::SetMaxHp(int MaxHp)
{
    this->MaxHp = MaxHp;
}

int Character::GetCurrentHp() const
{
    return CurrentHp;
}

void Character::SetCurrentHp(int CurrentHp)
{
    if (CurrentHp < 0)
    {
        this->CurrentHp = 0;
        return;
    }

    this->CurrentHp = CurrentHp;
}

int Character::GetMaxMp() const
{
    return MaxMp;
}

void Character::SetMaxMp(int MaxMp)
{
    this->MaxMp = MaxMp;
}

int Character::GetCurrentMp() const
{
    return CurrentMp;
}

void Character::SetCurrentMp(int CurrentMp)
{
    this->CurrentMp = CurrentMp;
}

int Character::GetPower() const
{
    return Power;
}

void Character::SetPower(int Power)
{
    this->Power = Power;
}

int Character::GetDefence() const
{
    return Defence;
}

void Character::SetDefence(int Defence)
{
    this->Defence = Defence;
}

void Character::TakeDamage(int Damage)
{
    if (Damage < 0)
    {
        return;
    }

    SetCurrentHp(CurrentHp - Damage);
}

bool Character::IsAlive() const
{
    return CurrentHp > 0;
}