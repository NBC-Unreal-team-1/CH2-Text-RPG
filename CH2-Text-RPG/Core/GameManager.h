#pragma once

#include "../Battle/BattleManager.h"
#include "../Log/LogManager.h"
#include "../Shop/ShopManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();

protected:
    void GameLoop();

private:
    BattleManager Battle;
    ShopManager Shop;
    LogManager Log;
};
