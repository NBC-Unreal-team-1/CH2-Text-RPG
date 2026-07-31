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
#include "../Inventory/Item.h"
#include "../Recipe/RecipeManager.h"
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
    int PrintRecipes(const RecipeManager& recipes) const;
    void PrintBattleLog(
        const std::pair<BattleResult, std::vector<BattleInfo>>& Result
    ) const;

protected:
private:
    std::string border = "========================================";
    std::string emptyLine = " ";
};
