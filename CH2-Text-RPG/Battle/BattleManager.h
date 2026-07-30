#pragma once

#include "BattleInfo.h"
#include "BattleResult.h"

#include <utility>
#include <vector>

class Player;
class Monster;

class BattleManager
{
public:
    BattleManager();
    ~BattleManager();
    std::pair<BattleResult, std::vector<BattleInfo>> StartBattle(
        Player& player,
        Monster monster
    );
    void CearBattleInfos();
  

protected:
private:
    std::vector<BattleInfo> BattleInfos;
   
};
