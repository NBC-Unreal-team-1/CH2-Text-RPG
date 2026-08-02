#pragma once

#include "Recipe.h"

#include <string>
#include <vector>

class RecipeManager
{
public:
    // 생성자
    RecipeManager();

public:
    // 일반 레시피 목록 반환
    const std::vector<Recipe>& GetRecipes() const;

    // 일반 레시피와 해금된 특수 레시피 반환
    std::vector<const Recipe*> GetAllRecipes() const;

    // 레시피 ID로 검색
    const Recipe* FindRecipeByID(int RecipeID) const;

    // 레시피 이름 일부로 검색
    std::vector<const Recipe*> SearchRecipes(
        const std::string& Keyword
    ) const;

    // 현재 보유 재료로 제작 가능한지 확인
    bool CanCompleteRecipe(
        int RecipeID,
        const std::vector<RecipeIngredient>& OwnedIngredients
    ) const;

    // 제작과 섭취를 한 번에 처리
    bool CompleteRecipe(int RecipeID);

    bool IsFinalRecipeCompleted() const;

private:
    // 일반 음식 10개를 모두 먹었는지 확인
    bool AreAllNormalRecipesEaten() const;

private:
    // 일반 레시피 10개
    std::vector<Recipe> Recipes;

    // 일반 음식 10개를 모두 먹으면 해금
    Recipe FinalBurger;

    // 궁극의 햄버거를 제작하면 해금
    Recipe FrenchFrie;
};
