#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "../UI/ConsoleUtils.h"
#include "../Battle/BattleInfo.h"
#include "../Battle/BattleResult.h"
#include "../Character/Player.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();

    int GetInt() const;

    void PrintMessage(const std::string& message) const;
    void SetupPlayerInfo(Player& player);
    void PrintBattleLog(
        const std::pair<BattleResult, std::vector<BattleInfo>>& Result
    ) const;

protected:
private:
};
