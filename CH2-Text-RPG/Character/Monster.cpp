#include "Monster.h"

Monster::Monster()
    : Monster(MonsterType::Lettuce)
{
}

Monster::Monster(MonsterType SelectedMonsterType)
    : MonsterId(SelectedMonsterType)
{
    GenerateStat();
}

Monster::~Monster()
{
}
void Monster::GenerateStat()
{
    switch (MonsterId)
    {
    case MonsterType::Lettuce:
        SetName("양상추");
        SetLevel(1);
        SetMaxHp(50);
        SetCurrentHp(50);
        SetPower(8);
        SetDefence(0);
        DropGold = 5;
        break;

    case MonsterType::Onion:
        SetName("양파");
        SetLevel(2);
        SetMaxHp(80);
        SetCurrentHp(80);
        SetPower(12);
        SetDefence(3);
        DropGold = 10;
        break;

    case MonsterType::Pickle:
        SetName("피클");
        SetLevel(3);
        SetMaxHp(110);
        SetCurrentHp(110);
        SetPower(16);
        SetDefence(5);
        DropGold = 15;
        break;

    default:
        break;
    }
}

MonsterType Monster::GetMonsterId() const
{
    return MonsterId;
}

int Monster::GetDropGold() const
{
    return DropGold;
}