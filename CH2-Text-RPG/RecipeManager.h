#pragma once

#include "Recipe.h"

#include <string>
#include <vector>

class RecipeManager
{
public:
    RecipeManager();

public:
    void SearchRecipes(
        const std::string& Keyword,
        int PlayerLevel
    ) const;

private:
    void PrintRecipe(
        const Recipe& TargetRecipe
    ) const;

private:
    std::vector<Recipe> Recipes;
    Recipe FinalBurger;
};