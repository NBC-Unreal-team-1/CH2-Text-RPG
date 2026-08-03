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
    Patty,
    PotatoBoss
};

class Monster : public Character
{
public:
    Monster();
    Monster(MonsterType SelectedMonsterType);
    ~Monster() override;

    void GenerateStat();

    int GetId() const;
    MonsterType GetMonsterId() const;
    int GetDropGold() const;

    int GetDropIngredientId() const;
    int GetDropIngredientAmount() const;

protected:
    
private:
    MonsterType MonsterId = MonsterType::Lettuce;
    int DropGold = 0;

    int DropIngredientId = 0;
    int DropIngredientAmount = 0;
};
