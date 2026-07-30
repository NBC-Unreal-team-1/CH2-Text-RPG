#include "GameManager.h"

#include "../Character/Monster.h"
#include "../Character/Player.h"

#include <iostream>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
    // TODO: Implement game manager destruction.
}

void GameManager::Run()
{
    GameLoop();
}

void GameManager::GameLoop()
{
    Player player;
    player.SetName("Player");
    player.SetMaxHp(30);
    player.SetCurrentHp(30);
    player.SetPower(7);

    Monster monster;
    monster.SetName("Training Monster");
    monster.SetMaxHp(20);
    monster.SetCurrentHp(20);
    monster.SetPower(4);

    Battle.ClearBattleInfos();

    std::cout << "=== Battle Start ===\n";
    std::cout << player.GetName() << " HP: "
              << player.GetCurrentHp() << '/' << player.GetMaxHp() << '\n';
    std::cout << monster.GetName() << " HP: "
              << monster.GetCurrentHp() << '/' << monster.GetMaxHp() << "\n\n";

    const auto [result, battleInfos] = Battle.StartBattle(player, monster);

    for (std::size_t index = 0; index < battleInfos.size(); ++index)
    {
        const BattleInfo& battleInfo = battleInfos[index];

        std::cout << "Turn " << index + 1 << '\n';
        std::cout << "  Player damage: " << battleInfo.AttackDamage << '\n';
        std::cout << "  Monster damage: " << battleInfo.GetDamage << '\n';
    }

    std::cout << '\n';
    std::cout << "Battle Result: "
              << (result == BattleResult::Win ? "Win" : "Lose")
              << '\n';
    std::cout << "Player Remaining HP: "
              << player.GetCurrentHp() << '\n';
}
