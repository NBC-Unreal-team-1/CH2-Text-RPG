#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "BattleResult.h"
class Player;
class Monster;
class BattleManager
{
public:
    BattleManager();
    ~BattleManager();

    std::pair<BattleResult,std::vector<BattleInfo>> StartBattle(Player& player,Monster monster);



    void Attack();
    //공격(행동)


    void Skill();
    //스킬로 공격(행동,마나부족시 행동 X)

    

    bool IsBattleEnd();
    //전투 종료



protected:


private:

    std::vector<BattleInfo> BattleInfos;

};
