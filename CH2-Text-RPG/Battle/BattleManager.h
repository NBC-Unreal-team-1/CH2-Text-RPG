#pragma once

#include "BattleResult.h"

class Player;

class BattleManager
{
public:
    BattleManager();
    ~BattleManager();

    BattleResult StartBattle(Player& player);

protected:
private:
};
