#include "GameManager.h"

#include "../Inventory/Inventory.h"
#include "../Inventory/Item.h"

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
        PrintBattleReward(CurrentMonster);

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

    Inventory& PlayerInventory = PlayerCharacter.GetInventory();
    const int IngredientId = monster.GetDropIngredientId();
    const int IngredientAmount = monster.GetDropIngredientAmount();

    if (IngredientId <= 0 || IngredientAmount <= 0)
    {
        return;
    }

    PlayerInventory.AddItem(
        IngredientId,
        IngredientAmount
    );
}

void GameManager::PrintBattleReward(const Monster& monster) const
{
    std::cout << "Gold Reward: "
              << monster.GetDropGold() << '\n';

    const int IngredientId = monster.GetDropIngredientId();
    const int IngredientAmount = monster.GetDropIngredientAmount();
    const InventorySlot* RewardSlot =
        PlayerCharacter.GetInventory().FindSlot(IngredientId);

    if (RewardSlot != nullptr && RewardSlot->ItemPtr != nullptr)
    {
        std::cout << "Ingredient Reward: "
                  << RewardSlot->ItemPtr->GetName()
                  << " x" << IngredientAmount << '\n';
        std::cout << "Ingredient Total: "
                  << RewardSlot->Count << '\n';
    }

    std::cout << "Total Gold: "
              << PlayerCharacter.GetGold() << "\n\n";
}

void GameManager::GameLoop()
{
    // TODO: Implement the main game loop.
}
