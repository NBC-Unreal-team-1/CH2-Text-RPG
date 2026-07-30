#pragma once

#include "../Battle/BattleManager.h"
#include "../Character/Monster.h"
#include "../Character/Player.h"
#include "../Shop/ShopManager.h"
#include "../UI/UIManager.h"

#include <random>

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();

protected:
    void InitializePlayer();
    void RunTutorial();
    void GameLoop();

    Monster CreateRandomTutorialMonster();
    void ApplyBattleReward(const Monster& monster);

private:
    Player PlayerCharacter;
    BattleManager Battle;
    ShopManager Shop;
    UIManager UI;
    std::mt19937 RandomEngine;
};
