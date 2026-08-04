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
#include "../Shop/ShopManager.h"
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
    int PrintShop(const ShopManager& shop);
    int PrintSelectedShopItem(const ShopItem& shopItem);
    int PrintBattleLog(
        const std::pair<BattleResult, std::vector<BattleInfo>>& Result
    ) const;
    int PrintBattleResult(const Player& player, const Monster& monster) const;
    
protected:
private:
    std::string border = "========================================";
    std::string emptyLine = " ";
};
