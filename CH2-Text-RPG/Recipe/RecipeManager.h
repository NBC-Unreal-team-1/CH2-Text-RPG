#pragma once

#include "Recipe.h"

#include <string>
#include <vector>

class RecipeManager
{
public:
    RecipeManager();

public:
    const std::vector<Recipe>& GetRecipes() const;

    std::vector<const Recipe*> GetAllRecipes() const;

    const Recipe* FindRecipeByID(int RecipeID) const;

    std::vector<const Recipe*> SearchRecipe(
        const std::string& Keyword
    ) const;

private:
    std::vector<Recipe> Recipes;

    Recipe FinalBurger;
    Recipe Potato;
};