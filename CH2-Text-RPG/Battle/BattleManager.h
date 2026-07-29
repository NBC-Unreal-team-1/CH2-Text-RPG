#pragma once
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

    void StartBattle(Player& player,Monster monster);

    int PlayerTurn();
    //턴 시작

    bool SelectAction(int index);
    //플레이어의 행동 판별(행동시 턴 넘김)


    void MonsterState();
    //몬스터 정보 호출(비행동)


    void PlayerState();
    //플레이어 정보 호출(비행동)


    bool Attack();
    //공격(행동)


    bool Skill();
    //스킬로 공격(행동,마나부족시 행동 X)


    bool UseItem();
    //아이템사용(행동,아이템 미 사용시 행동 X)
    

    bool IsBattleEnd();
    //전투 종료

    BattleResult WinLose(bool IsBattleEnd);
    //승패판정


protected:


private:



};
