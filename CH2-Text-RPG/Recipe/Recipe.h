#pragma once

#include <string>
#include <vector>

// 레시피에서 요구하는 아이템 ID와 개수
struct RecipeIngredient
{
public:
    int ItemId = 0;
    int Count = 0;
};

struct Recipe
{
public:
    int Id = 0;

    std::string Name;
    std::vector<RecipeIngredient> Ingredients;

    int HpBonus = 0;
    int AttackBonus = 0;
    int DefenseBonus = 0;

    // 음식을 제작했는가
    bool IsCooked = false;

    // 레시피가 해금됐는가
    bool IsUnlocked = false;

    // 음식을 먹었는가
    bool IsEaten = false;
};