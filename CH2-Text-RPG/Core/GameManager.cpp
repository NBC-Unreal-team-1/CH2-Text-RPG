#include "GameManager.h"

#include <iostream>

GameManager::GameManager()
    : RandomEngine(std::random_device{}())
{
}

GameManager::~GameManager()
{
    // TODO: Implement game manager destruction.
}

void GameManager::Run()
{
    InitializePlayer();
    RunTutorial();
    GameLoop();
}

void GameManager::InitializePlayer()
{
    UI.SetupPlayerInfo(PlayerCharacter);
    PlayerCharacter.SetLevel(1);
    PlayerCharacter.SetMaxHp(100);
    PlayerCharacter.SetCurrentHp(100);
    PlayerCharacter.SetPower(30);
    PlayerCharacter.SetDefence(0);
    PlayerCharacter.SetGold(0);
}

void GameManager::RunTutorial()
{
    UI.PrintMenu();

    

    std::uniform_int_distribution<int> BattleCountDistribution(3, 4);
    const int BattleCount = BattleCountDistribution(RandomEngine);

    std::cout << "\n=== Tutorial Start ===\n";
    std::cout << "Tutorial Battles: " << BattleCount << "\n\n";

    for (int BattleIndex = 0; BattleIndex < BattleCount; ++BattleIndex)
    {
        Monster CurrentMonster = CreateRandomTutorialMonster();

        std::cout << "=== Battle "
                  << BattleIndex + 1 << " / " << BattleCount
                  << " ===\n";
        std::cout << PlayerCharacter.GetName() << " HP: "
                  << PlayerCharacter.GetCurrentHp() << '/'
                  << PlayerCharacter.GetMaxHp() << '\n';
        std::cout << CurrentMonster.GetName() << " HP: "
                  << CurrentMonster.GetCurrentHp() << '/'
                  << CurrentMonster.GetMaxHp() << "\n\n";

        const auto BattleResultData =
            Battle.StartBattle(PlayerCharacter, CurrentMonster);

        UI.PrintBattleLog(BattleResultData);

        if (BattleResultData.first == BattleResult::Lose)
        {
            std::cout << "\nTutorial Failed.\n";
            return;
        }

        ApplyBattleReward(CurrentMonster);

        std::cout << "Gold Reward: "
                  << CurrentMonster.GetDropGold() << '\n';
        std::cout << "Total Gold: "
                  << PlayerCharacter.GetGold() << "\n\n";

        PlayerCharacter.SetCurrentHp(
            PlayerCharacter.GetMaxHp()
        );
    }

    std::cout << "=== Tutorial Complete ===\n";

    UI.PrintInventory(PlayerCharacter.GetInventory());
}

Monster GameManager::CreateRandomTutorialMonster()
{
    std::uniform_int_distribution<int> MonsterDistribution(0, 2);
    const int MonsterIndex = MonsterDistribution(RandomEngine);

    return Monster(static_cast<MonsterType>(MonsterIndex));
}

void GameManager::ApplyBattleReward(const Monster& monster)
{
    PlayerCharacter.AddGold(monster.GetDropGold());
}

void GameManager::GameLoop()
{
    // TODO: Implement the main game loop.
}
