#pragma once

#include "../Battle/BattleManager.h"
#include "../Character/Monster.h"
#include "../Character/Player.h"
#include "../Recipe/RecipeManager.h"
#include "../Shop/ShopManager.h"
#include "../UI/UIManager.h"

#include <random>
#include <vector>

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();
    std::vector<const Recipe*> GetAvailableRecipes() const;

protected:
    void InitializePlayer();
    void RunTutorial();
    void GameLoop();

    void RunNextIngredientBattle();
    void RunBossBattle();
    void HandleRecipeMenu();
    void HandleShopMenu();
    bool CookRecipe(int RecipeId);
    const Skill* SelectBattleSkill(const Monster& monster);

    Monster CreateRandomTutorialMonster();
    const ::Recipe* FindNextRecipe() const;
    int FindMissingIngredientId(const ::Recipe& recipe) const;
    void ApplyBattleReward(const Monster& monster);
    void PrintBattleReward(const Monster& monster) const;

private:
    Player PlayerCharacter;
    BattleManager Battle;
    RecipeManager Recipe;
    ShopManager Shop;
    UIManager UI;
    std::mt19937 RandomEngine;
};
