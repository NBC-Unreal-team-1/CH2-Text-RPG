#pragma once

#include "Recipe.h"

#include <vector>

class RecipeManager
{
public:
    RecipeManager();

public:
    const std::vector<Recipe>& GetRecipes() const;

private:
    std::vector<Recipe> Recipes;

    Recipe FinalBurger;
    Recipe Potato;
};