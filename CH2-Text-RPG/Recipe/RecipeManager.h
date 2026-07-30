#pragma once

#include "Recipe.h"

#include <vector>

class RecipeManager
{
public:
    RecipeManager();

private:
    std::vector<Recipe> Recipes;

    Recipe FinalBurger;
    Recipe Potato;
};