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

std::vector<const Recipe*> GameManager::GetAvailableRecipes() const
{
    return Recipe.GetAllRecipes();
}

void GameManager::InitializePlayer()
{
    UI.SetupPlayerInfo(PlayerCharacter);
    PlayerCharacter.SetLevel(1);
    PlayerCharacter.SetMaxHp(300);
    PlayerCharacter.SetCurrentHp(300);
    PlayerCharacter.SetPower(60);
    PlayerCharacter.SetDefence(30);
    PlayerCharacter.SetMaxMp(30);
    PlayerCharacter.SetCurrentMp(30);
    PlayerCharacter.SetGold(0);
}

void GameManager::RunTutorial()
{
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
    bool IsRunning = true;

    while (IsRunning && !Recipe.IsFinalRecipeCompleted())
    {
        switch (UI.PrintMenu())
        {
        case 0:
            IsRunning = false;
            break;
        case 1:
            RunNextIngredientBattle();
            break;
        case 2:
            UI.PrintInventory(PlayerCharacter.GetInventory());
            break;
        case 3:
            HandleRecipeMenu();
            break;
        default:
            break;
        }
    }

    if (Recipe.IsFinalRecipeCompleted())
    {
        std::cout << "\n=== Game Clear ===\n";
        std::cout << "최종의 감자튀김을 획득했습니다!\n";
    }
}

void GameManager::RunNextIngredientBattle()
{
    const ::Recipe* TargetRecipe = FindNextRecipe();
    if (TargetRecipe == nullptr)
    {
        return;
    }

    const int MissingIngredientId = FindMissingIngredientId(*TargetRecipe);
    if (MissingIngredientId < 100 || MissingIngredientId > 109)
    {
        std::cout << "필요한 재료가 모였습니다. 레시피 메뉴에서 요리해주세요.\n";
        return;
    }

    Monster CurrentMonster(static_cast<MonsterType>(MissingIngredientId - 100));
    const auto BattleResultData = Battle.StartBattle(PlayerCharacter, CurrentMonster);
    UI.PrintBattleLog(BattleResultData);

    if (BattleResultData.first == BattleResult::Win)
    {
        ApplyBattleReward(CurrentMonster);
        PrintBattleReward(CurrentMonster);
    }

    PlayerCharacter.SetCurrentHp(PlayerCharacter.GetMaxHp());
    PlayerCharacter.SetCurrentMp(PlayerCharacter.GetMaxMp());
}

void GameManager::RunBossBattle()
{
    Monster Boss(MonsterType::PotatoBoss);
    std::cout << "\n궁극의 햄버거 완성! 감자 대왕과의 보스전이 시작됩니다.\n";

    const auto BattleResultData = Battle.StartBattle(PlayerCharacter, Boss);
    UI.PrintBattleLog(BattleResultData);

    if (BattleResultData.first != BattleResult::Win)
    {
        std::cout << "보스전에서 패배했습니다.\n";
        PlayerCharacter.SetCurrentHp(PlayerCharacter.GetMaxHp());
        PlayerCharacter.SetCurrentMp(PlayerCharacter.GetMaxMp());
        return;
    }

    ApplyBattleReward(Boss);
    PrintBattleReward(Boss);
    CookRecipe(12);
}

void GameManager::HandleRecipeMenu()
{
    const std::vector<const ::Recipe*> AvailableRecipes = Recipe.GetAllRecipes();
    const int RecipeSelection = UI.PrintRecipes(Recipe, PlayerCharacter.GetInventory());

    if (RecipeSelection <= 0 ||
        RecipeSelection > static_cast<int>(AvailableRecipes.size()))
    {
        return;
    }

    const int SelectedRecipeId = AvailableRecipes[RecipeSelection - 1]->Id;
    if (CookRecipe(SelectedRecipeId) && SelectedRecipeId == 11)
    {
        RunBossBattle();
    }
}

bool GameManager::CookRecipe(int RecipeId)
{
    const ::Recipe* TargetRecipe = Recipe.FindRecipeByID(RecipeId);
    if (TargetRecipe == nullptr)
    {
        return false;
    }

    std::vector<RecipeIngredient> OwnedIngredients;
    for (const InventorySlot& Slot : PlayerCharacter.GetInventory().GetItems())
    {
        if (Slot.ItemPtr != nullptr)
        {
            OwnedIngredients.push_back({ Slot.ItemPtr->GetId(), Slot.Count });
        }
    }

    if (!Recipe.CanCompleteRecipe(RecipeId, OwnedIngredients))
    {
        std::cout << "재료가 부족하거나 아직 잠긴 레시피입니다.\n";
        return false;
    }

    // 최종 진행 테스트 중에는 요리 재료를 소모하지 않습니다.
    // const std::vector<RecipeIngredient> RequiredIngredients = TargetRecipe->Ingredients;
    const int HpBonus = TargetRecipe->HpBonus;
    const int AttackBonus = TargetRecipe->AttackBonus;
    const int DefenseBonus = TargetRecipe->DefenseBonus;
    const std::string RecipeName = TargetRecipe->Name;

    // for (const RecipeIngredient& Ingredient : RequiredIngredients)
    // {
    //     PlayerCharacter.GetInventory().ReduceItem(Ingredient.ItemId, Ingredient.Count);
    // }

    if (!Recipe.CompleteRecipe(RecipeId))
    {
        return false;
    }

    PlayerCharacter.ApplyFoodBonus(HpBonus, AttackBonus, DefenseBonus);
    std::cout << RecipeName << " 제작 및 섭취 완료!\n";
    return true;
}

const ::Recipe* GameManager::FindNextRecipe() const
{
    const std::vector<const ::Recipe*> AllRecipes = Recipe.GetAllRecipes();
    for (const ::Recipe* CurrentRecipe : AllRecipes)
    {
        if (CurrentRecipe != nullptr &&
            CurrentRecipe->IsUnlocked &&
            !CurrentRecipe->IsEaten)
        {
            return CurrentRecipe;
        }
    }
    return nullptr;
}

int GameManager::FindMissingIngredientId(const ::Recipe& recipe) const
{
    for (const RecipeIngredient& Ingredient : recipe.Ingredients)
    {
        if (PlayerCharacter.GetInventory().GetItemCount(Ingredient.ItemId) < Ingredient.Count)
        {
            return Ingredient.ItemId;
        }
    }
    return 0;
}
