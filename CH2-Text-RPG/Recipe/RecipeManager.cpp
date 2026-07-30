#include "RecipeManager.h"

RecipeManager::RecipeManager()
{
    Recipes =
    {
        {
            1,
            "양상추 샐러드",
            {
                { "양상추", 1 }
            },
        //체력
            5,
        //공격력
            0,
        //방어력
            0,
            false,
            true
        },
        {
            2,
            "간단 채소 샐러드",
            {
                { "양상추", 1 },
                { "양파", 1 }
            },
            0,
            0,
            1,
            false,
            false
        },
        {
            3,
            "새콤한 샐러드",
            {
                { "양상추", 1 },
                { "양파", 1 },
                { "피클", 1 }
            },
            7,
            0,
            0,
            false,
            false
        },
        {
            4,
            "신선한 채소 샐러드",
            {
                { "양상추", 1 },
                { "양파", 1 },
                { "피클", 1 },
                { "토마토", 1 }
            },
            10,
            0,
            0,
            false,
            false
        },
        {
            5,
            "새콤달콤 채소무침",
            {
                { "양상추", 1 },
                { "양파", 1 },
                { "피클", 1 },
                { "토마토", 1 },
                { "케첩", 1 }
            },
            0,
            1,
            0,
            false,
            false
        },
        {
            6,
            "특제 마요 샐러드",
            {
                { "양상추", 1 },
                { "양파", 1 },
                { "피클", 1 },
                { "토마토", 1 },
                { "케첩", 1 },
                { "마요네즈", 1 }
            },
            12,
            0,
            1,
            false,
            false
        },
        {
            7,
            "베이컨 샐러드",
            {
                { "양상추", 1 },
                { "양파", 1 },
                { "토마토", 1 },
                { "베이컨", 1 },
                { "마요네즈", 1 }
            },
            10,
            2,
            0,
            false,
            false
        },
        {
            8,
            "베이컨 치즈 샐러드",
            {
                { "양상추", 1 },
                { "토마토", 1 },
                { "베이컨", 1 },
                { "마요네즈", 1 },
                {"치즈",1}
            },
            10,
            1,
            2,
            false,
            false
        },
        {
            9,
            "특제 클럽 샌드위치",
            {
                { "빵", 1 },
                { "베이컨", 1 },
                { "치즈",1},
                { "양파", 1 },
                { "토마토", 1 },
                { "피클",1},
                { "케첩",1},
                { "마요네즈", 1 }
            },
            15,
            2,
            0,
            false,
            false
        },
        {
            10,
            "특제 미트 플레이트",
            {
                { "패티", 1 },
                { "베이컨",1},
                { "치즈", 1 },
                { "양파", 1 },
                { "토마토",1},
                { "피클",1},
                { "케첩", 1 },
                { "마요네즈",1}
            },
            10,
            5,
            3,
            false,
            false
        }
    };

    FinalBurger =
    {
        11,
        "궁극의 햄버거",
        {
            { "양상추", 1 },
            { "양파", 1 },
            { "피클", 1 },
            { "토마토", 1 },
            { "케첩", 1 },
            { "마요네즈", 1 },
            { "베이컨", 1 },
            { "치즈", 1 },
            { "빵", 1 },
            { "패티", 1 }
        },
        99,
        99,
        99,
        false,
        false
    };

    Potato =
    {
        12,
        "최종의 감자튀김",
        {
            { "감자", 1 }
        },
        99,
        99,
        99,
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

    AllRecipes.push_back(&FinalBurger);
    AllRecipes.push_back(&Potato);

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

    if (FinalBurger.Id == RecipeID)
    {
        return &FinalBurger;
    }

    if (Potato.Id == RecipeID)
    {
        return &Potato;
    }

    return nullptr;
}

std::vector<const Recipe*> RecipeManager::SearchRecipe(
    const std::string& Keyword
) const
{
    std::vector<const Recipe*> SearchResults;

    for (const Recipe& CurrentRecipe : Recipes)
    {
        if (CurrentRecipe.Name.find(Keyword) != std::string::npos)
        {
            SearchResults.push_back(&CurrentRecipe);
        }
    }

    if (FinalBurger.Name.find(Keyword) != std::string::npos)
    {
        SearchResults.push_back(&FinalBurger);
    }

    if (Potato.Name.find(Keyword) != std::string::npos)
    {
        SearchResults.push_back(&Potato);
    }

    return SearchResults;
}