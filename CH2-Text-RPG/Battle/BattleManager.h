#pragma once

#include "BattleInfo.h"
#include "BattleResult.h"

#include <utility>
#include <vector>

class Player;
class Monster;
class Skill;

class BattleManager
{
public:
    BattleManager();
    ~BattleManager();
    std::pair<BattleResult, std::vector<BattleInfo>> StartBattle(
        Player& player,
        Monster& monster, Skill* selectedSkill = nullptr
    );
  

protected:
private:
    std::vector<BattleInfo> BattleInfos;
    void ClearBattleInfos();
};
