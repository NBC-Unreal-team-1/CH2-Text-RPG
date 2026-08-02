#include "RecipeManager.h"

#include <cstddef>

RecipeManager::RecipeManager()
{
    Recipes =
    {
        {
            1,
            "양상추 샐러드",
            {
                { 100, 1 } // 양상추
            },
            5,
            0,
            0,
            false,
            true,
            false
        },
        {
            2,
            "간단 채소 샐러드",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }  // 양파
            },
            0,
            0,
            1,
            false,
            false,
            false
        },
        {
            3,
            "새콤한 샐러드",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }, // 양파
                { 102, 1 }  // 피클
            },
            7,
            0,
            0,
            false,
            false,
            false
        },
        {
            4,
            "신선한 채소 샐러드",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }, // 양파
                { 102, 1 }, // 피클
                { 103, 1 }  // 토마토
            },
            10,
            0,
            0,
            false,
            false,
            false
        },
        {
            5,
            "새콤달콤 채소무침",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }, // 양파
                { 102, 1 }, // 피클
                { 103, 1 }, // 토마토
                { 104, 1 }  // 케첩
            },
            0,
            1,
            0,
            false,
            false,
            false
        },
        {
            6,
            "특제 마요 샐러드",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }, // 양파
                { 102, 1 }, // 피클
                { 103, 1 }, // 토마토
                { 104, 1 }, // 케첩
                { 105, 1 }  // 마요네즈
            },
            12,
            0,
            1,
            false,
            false,
            false
        },
        {
            7,
            "베이컨 샐러드",
            {
                { 100, 1 }, // 양상추
                { 101, 1 }, // 양파
                { 103, 1 }, // 토마토
                { 106, 1 }, // 베이컨
                { 105, 1 }  // 마요네즈
            },
            10,
            2,
            0,
            false,
            false,
            false
        },
        {
            8,
            "베이컨 치즈 샐러드",
            {
                { 100, 1 }, // 양상추
                { 103, 1 }, // 토마토
                { 106, 1 }, // 베이컨
                { 105, 1 }, // 마요네즈
                { 107, 1 }  // 치즈
            },
            10,
            1,
            2,
            false,
            false,
            false
        },
        {
            9,
            "특제 클럽 샌드위치",
            {
                { 108, 1 }, // 빵
                { 106, 1 }, // 베이컨
                { 107, 1 }, // 치즈
                { 101, 1 }, // 양파
                { 103, 1 }, // 토마토
                { 102, 1 }, // 피클
                { 104, 1 }, // 케첩
                { 105, 1 }  // 마요네즈
            },
            15,
            2,
            0,
            false,
            false,
            false
        },
        {
            10,
            "특제 미트 플레이트",
            {
                { 109, 1 }, // 패티
                { 106, 1 }, // 베이컨
                { 107, 1 }, // 치즈
                { 101, 1 }, // 양파
                { 103, 1 }, // 토마토
                { 102, 1 }, // 피클
                { 104, 1 }, // 케첩
                { 105, 1 }  // 마요네즈
            },
            10,
            5,
            3,
            false,
            false,
            false
        }
    };

    FinalBurger =
    {
        11,
        "궁극의 햄버거",
        {
            { 100, 1 }, // 양상추
            { 101, 1 }, // 양파
            { 102, 1 }, // 피클
            { 103, 1 }, // 토마토
            { 104, 1 }, // 케첩
            { 105, 1 }, // 마요네즈
            { 106, 1 }, // 베이컨
            { 107, 1 }, // 치즈
            { 108, 1 }, // 빵
            { 109, 1 }  // 패티
        },
        99,
        99,
        99,
        false,
        false,
        false
    };

    FrenchFrie =
    {
        12,
        "최종의 감자튀김",
        {
            { 110, 1 } // 감자
        },
        99,
        99,
        99,
        false,
        false,
        false
    };
}

const std::vector<Recipe>& RecipeManager::GetRecipes() const
{
    return Recipes;
}

std::vector<const Recipe*> RecipeManager::GetAllRecipes() const
{
    std::vector<const Recipe*> AllRecipes;

    for (const Recipe& CurrentRecipe : Recipes)
    {
        AllRecipes.push_back(&CurrentRecipe);
    }

    // 잠긴 궁극의 햄버거는 목록에서 제외
    if (FinalBurger.IsUnlocked)
    {
        AllRecipes.push_back(&FinalBurger);
    }

    // 잠긴 감자튀김은 목록에서 제외
    if (FrenchFrie.IsUnlocked)
    {
        AllRecipes.push_back(&FrenchFrie);
    }

    return AllRecipes;
}

const Recipe* RecipeManager::FindRecipeByID(
    int RecipeID
) const
{
    for (const Recipe& CurrentRecipe : Recipes)
    {
        if (CurrentRecipe.Id == RecipeID)
        {
            return &CurrentRecipe;
        }
    }

    // 잠긴 특수 레시피는 검색되지 않음
    if (
        FinalBurger.IsUnlocked &&
        FinalBurger.Id == RecipeID
        )
    {
        return &FinalBurger;
    }

    if (
        FrenchFrie.IsUnlocked &&
        FrenchFrie.Id == RecipeID
        )
    {
        return &FrenchFrie;
    }

    return nullptr;
}

std::vector<const Recipe*> RecipeManager::SearchRecipes(
    const std::string& Keyword
) const
{
    std::vector<const Recipe*> SearchResults;

    for (const Recipe& CurrentRecipe : Recipes)
    {
        if (
            CurrentRecipe.Name.find(Keyword) !=
            std::string::npos
            )
        {
            SearchResults.push_back(&CurrentRecipe);
        }
    }

    // 잠긴 특수 레시피는 검색 결과에서 제외
    if (
        FinalBurger.IsUnlocked &&
        FinalBurger.Name.find(Keyword) != std::string::npos
        )
    {
        SearchResults.push_back(&FinalBurger);
    }

    if (
        FrenchFrie.IsUnlocked &&
        FrenchFrie.Name.find(Keyword) != std::string::npos
        )
    {
        SearchResults.push_back(&FrenchFrie);
    }

    return SearchResults;
}

bool RecipeManager::CanCompleteRecipe(
    int RecipeID,
    const std::vector<RecipeIngredient>& OwnedIngredients
) const
{
    const Recipe* TargetRecipe = FindRecipeByID(RecipeID);

    // 존재하지 않거나 잠긴 특수 레시피
    if (TargetRecipe == nullptr)
    {
        return false;
    }

    // 잠긴 일반 레시피
    if (!TargetRecipe->IsUnlocked)
    {
        return false;
    }

    // 이미 제작하거나 먹은 레시피
    if (TargetRecipe->IsCooked || TargetRecipe->IsEaten)
    {
        return false;
    }

    // 필요한 모든 재료 확인
    for (const RecipeIngredient& RequiredIngredient
        : TargetRecipe->Ingredients)
    {
        int OwnedCount = 0;

        // 같은 아이템 ID의 보유 수량을 모두 더함
        for (const RecipeIngredient& OwnedIngredient
            : OwnedIngredients)
        {
            if (
                OwnedIngredient.ItemId ==
                RequiredIngredient.ItemId
                )
            {
                OwnedCount += OwnedIngredient.Count;
            }
        }

        // 필요한 수량보다 적게 가지고 있음
        if (OwnedCount < RequiredIngredient.Count)
        {
            return false;
        }
    }

    // 모든 조건을 만족함
    return true;
}

bool RecipeManager::CompleteRecipe(int RecipeID)
{
    // 일반 레시피 처리
    for (std::size_t Index = 0; Index < Recipes.size(); ++Index)
    {
        Recipe& CurrentRecipe = Recipes[Index];

        if (CurrentRecipe.Id != RecipeID)
        {
            continue;
        }

        // 잠긴 레시피
        if (!CurrentRecipe.IsUnlocked)
        {
            return false;
        }

        // 이미 제작하거나 먹은 레시피
        if (CurrentRecipe.IsCooked || CurrentRecipe.IsEaten)
        {
            return false;
        }

        // 제작과 섭취를 한 번에 처리
        CurrentRecipe.IsCooked = true;
        CurrentRecipe.IsEaten = true;

        const std::size_t NextIndex = Index + 1;

        // 다음 일반 레시피 해금
        if (NextIndex < Recipes.size())
        {
            Recipes[NextIndex].IsUnlocked = true;
        }

        // 일반 음식 10개를 모두 먹으면 햄버거 해금
        if (AreAllNormalRecipesEaten())
        {
            FinalBurger.IsUnlocked = true;
        }

        return true;
    }

    // 궁극의 햄버거 처리
    if (FinalBurger.Id == RecipeID)
    {
        if (!FinalBurger.IsUnlocked)
        {
            return false;
        }

        if (FinalBurger.IsCooked || FinalBurger.IsEaten)
        {
            return false;
        }

        // 햄버거 제작과 섭취를 한 번에 처리
        FinalBurger.IsCooked = true;
        FinalBurger.IsEaten = true;

        // 햄버거를 완성하면 감자튀김 해금
        FrenchFrie.IsUnlocked = true;

        return true;
    }

    // 감자튀김 처리
    if (FrenchFrie.Id == RecipeID)
    {
        if (!FrenchFrie.IsUnlocked)
        {
            return false;
        }

        if (FrenchFrie.IsCooked || FrenchFrie.IsEaten)
        {
            return false;
        }

        // 감자튀김 제작과 섭취를 한 번에 처리
        FrenchFrie.IsCooked = true;
        FrenchFrie.IsEaten = true;

        return true;
    }

    // 해당 ID의 레시피가 존재하지 않음
    return false;
}

bool RecipeManager::IsFinalRecipeCompleted() const
{
    return FrenchFrie.IsCooked && FrenchFrie.IsEaten;
}

bool RecipeManager::AreAllNormalRecipesEaten() const
{
    for (const Recipe& CurrentRecipe : Recipes)
    {
        if (!CurrentRecipe.IsEaten)
        {
            return false;
        }
    }

    return true;
}
