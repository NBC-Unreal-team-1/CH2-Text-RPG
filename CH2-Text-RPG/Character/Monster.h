#pragma once

#include "Character.h"

enum class MonsterType
{
    Lettuce,
    Onion,
    Pickle,
    Tomato,
    Ketchup,
    Mayonnaise,
    Bacon,
    Cheese,
    Bread,
    Patty
};

class Monster : public Character
{
public:
    Monster();
    Monster(MonsterType SelectedMonsterType);
    ~Monster() override;

    void GenerateStat();

    MonsterType GetMonsterId() const;
    int GetDropGold() const;

protected:
    
private:
    MonsterType MonsterId = MonsterType::Lettuce;
    int DropGold = 0;
};
