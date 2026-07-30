#include "BattleManager.h"

#include "../Character/Monster.h"
#include "../Character/Player.h"

BattleManager::BattleManager()
{
}

BattleManager::~BattleManager()
{
    // TODO: Implement battle manager destruction.
}
void BattleManager::ClearBattleInfos()
{
    BattleInfos.clear();
}

std::pair<BattleResult, std::vector<BattleInfo>> BattleManager::StartBattle(
    Player& player,
    Monster& monster
)
{
    ClearBattleInfos();
    while (player.GetCurrentHp() > 0 and monster.GetCurrentHp() > 0)
    {
        if (player.GetPower() <= 0)
        {
            return { BattleResult::Lose, BattleInfos };
        }
        monster.TakeDamage(player.GetPower());
        if (monster.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerWin("Attack", player.GetPower(), 0, player.GetCurrentHp(), monster.GetCurrentHp());
            BattleInfos.push_back(PlayerWin);
            return { BattleResult::Win, BattleInfos};
        }
        player.TakeDamage(monster.GetPower());
        if (player.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerLose("Attack", player.GetPower(), monster.GetPower(), player.GetCurrentHp(),monster.GetCurrentHp());
            BattleInfos.push_back(PlayerLose);
            break;
        }
        BattleInfo InBattle("Attack", player.GetPower(), monster.GetPower(), player.GetCurrentHp(), monster.GetCurrentHp());
        BattleInfos.push_back(InBattle);
    }
    return { BattleResult::Lose, BattleInfos};
}

