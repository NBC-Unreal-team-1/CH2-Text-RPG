#pragma once

#include <string>
#include <utility>
#include <vector>

// first: 재료 이름
// second: 필요한 개수
using Ingredient = std::pair<std::string, int>;

struct Recipe
{
public:
    int Id = 0;

    std::string Name;
    std::vector<Ingredient> Ingredients;

    int HpBonus = 0;
    int AttackBonus = 0;
    int DefenseBonus = 0;

    bool IsCooked = false;
    bool IsUnlocked = false;
};