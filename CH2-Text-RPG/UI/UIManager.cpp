#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
    // TODO: Implement UI manager destruction.
}

void UIManager::PrintMessage(const std::string& message) const
{
    // TODO: Print a message.
}

void UIManager::SetupPlayerInfo(Player& player)
{
    std::string name;
    int maxHp = 30;
    int power = 7;

    std::cout << "Name : ";
    std::getline(std::cin, name);
    ClearLine(0, 0);


    player.SetName(name);
    player.SetMaxHp(maxHp);
    player.SetCurrentHp(maxHp);
    player.SetPower(power);
}

void UIManager::PrintBattleLog(
    const std::pair<BattleResult, std::vector<BattleInfo>>& Result
) const
{
    const std::vector<BattleInfo>& BattleLogs = Result.second;

    for (std::size_t Index = 0; Index < BattleLogs.size(); ++Index)
    {
        const BattleInfo& CurrentLog = BattleLogs[Index];

        std::cout << "Turn " << Index + 1 << '\n';
        std::cout << "  Player Damage: "
                  << CurrentLog.AttackDamage << '\n';
        std::cout << "  Monster Damage: "
                  << CurrentLog.GetDamage << '\n';
        std::cout << "  Player HP: "
                  << CurrentLog.PlayerHP << '\n';
        std::cout << "  Monster HP: "
                  << CurrentLog.MonsterHP << '\n';
    }

    std::cout << '\n';
    std::cout << "Battle Result: "
              << (Result.first == BattleResult::Win ? "Win" : "Lose")
              << '\n';
}
