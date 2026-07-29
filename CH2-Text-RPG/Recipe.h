#pragma once

#include <string>
#include <utility>
#include <vector>

using Ingredient = std::pair<std::string, int>;

struct Recipe
{
public:
    int Id = 0;
    int RequiredLevel = 1;

    std::string Name;
    std::vector<Ingredient> Ingredients;

    int HpBonus = 0;
    int AttackBonus = 0;
    int DefenseBonus = 0;

    bool IsCooked = false;
};