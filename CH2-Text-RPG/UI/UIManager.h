#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include "../UI/ConsoleUtils.h"
#include "../Battle/BattleInfo.h"
#include "../Battle/BattleResult.h"
#include "../Character/Player.h"
#include "../Character/Monster.h"
#include "../Inventory/Item.h"
#include "../Recipe/RecipeManager.h"
#include "../Shop/ShopItem.h"
#include "../UI/ScreenData.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();

    int GetInput(ScreenData& screen, int min, int max) const;
    void SetupPlayerInfo(Player& player);
    int PrintMenu() const;
    int PrintInventory(const Inventory& inventory) const;
    int PrintRecipes(const RecipeManager& recipes, const Inventory& inventory) const;
    int PrintSelectedRecipe(const Recipe* recipe, const Inventory& inventory) const;
    void PrintInsufficientIngredients() const;
    void PrintRecipeSuccess(
        const std::string& RecipeName,
        int HpBonus,
        int AttackBonus,
        int DefenseBonus,
        const Player& player,
        bool IsNextStageUnlocked
    ) const;
    int PrintShop(const std::vector<ShopItem>& shopItems);
    int PrintSelectedShopItem(const ShopItem& shopItem);
    void PrintShopPurchaseResult(bool IsPurchased, const Player& player) const;
    int PrintSkillSelection(
        const Player& player,
        const Monster& monster
    ) const;
    void PrintBossIntroStory(const Monster& boss) const;
    void PrintEndingStory() const;
    int PrintBattleLog(
        const std::pair<BattleResult, std::vector<BattleInfo>>& Result
    ) const;
    int PrintBattleResult(const Player& player, const Monster& monster) const;
    
protected:
private:
    std::string border = "========================================";
    std::string emptyLine = " ";
};
