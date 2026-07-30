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

void UIManager::PrintBattleLog(const std::pair<BattleResult, std::vector<BattleInfo>> Result) const
{
    // 전투 전체 정보 받아와서 분리 및 출력
}