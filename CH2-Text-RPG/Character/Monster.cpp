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

        DropIngredientId = 100;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Onion:
        SetName("양파");
        SetLevel(2);
        SetMaxHp(80);
        SetCurrentHp(80);
        SetPower(12);
        SetDefence(3);
        DropGold = 10;

        DropIngredientId = 101;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Pickle:
        SetName("피클");
        SetLevel(3);
        SetMaxHp(110);
        SetCurrentHp(110);
        SetPower(16);
        SetDefence(5);
        DropGold = 15;

        DropIngredientId = 102;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Tomato:
        SetName("토마토");
        SetLevel(4);
        SetMaxHp(150);
        SetCurrentHp(150);
        SetPower(20);
        SetDefence(8);
        DropGold = 20;

        DropIngredientId = 103;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Ketchup:
        SetName("케첩");
        SetLevel(5);
        SetMaxHp(195);
        SetCurrentHp(195);
        SetPower(24);
        SetDefence(12);
        DropGold = 25;

        DropIngredientId = 104;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Mayonnaise:
        SetName("마요네즈");
        SetLevel(6);
        SetMaxHp(245);
        SetCurrentHp(245);
        SetPower(28);
        SetDefence(16);
        DropGold = 30;

        DropIngredientId = 105;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Bacon:
        SetName("베이컨");
        SetLevel(7);
        SetMaxHp(300);
        SetCurrentHp(300);
        SetPower(32);
        SetDefence(20);
        DropGold = 35;

        DropIngredientId = 106;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Cheese:
        SetName("치즈");
        SetLevel(8);
        SetMaxHp(360);
        SetCurrentHp(360);
        SetPower(36);
        SetDefence(24);
        DropGold = 40;

        DropIngredientId = 107;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Bread:
        SetName("빵");
        SetLevel(9);
        SetMaxHp(425);
        SetCurrentHp(425);
        SetPower(40);
        SetDefence(28);
        DropGold = 45;

        DropIngredientId = 108;
        DropIngredientAmount = 1;
        break;

    case MonsterType::Patty:
        SetName("패티");
        SetLevel(10);
        SetMaxHp(500);
        SetCurrentHp(500);
        SetPower(45);
        SetDefence(32);
        DropGold = 50;

        DropIngredientId = 109;
        DropIngredientAmount = 1;
        break;

    case MonsterType::PotatoBoss:
        SetName("감자 대왕");
        SetLevel(11);
        SetMaxHp(700);
        SetCurrentHp(700);
        SetPower(55);
        SetDefence(35);
        DropGold = 100;
        DropIngredientId = 110;
        DropIngredientAmount = 1;
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

int Monster::GetDropIngredientId() const
{
    return DropIngredientId;
}

int Monster::GetDropIngredientAmount() const
{
    return DropIngredientAmount;
}
