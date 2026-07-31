#include "BattleManager.h"
#include <algorithm>
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
    int PlayerAttackDamage = std::max(player.GetPower() - monster.GetDefence(), 1);
    int PlayerTakeDamage = std::max(monster.GetPower() - player.GetDefence(), 1);
    int Turn = 0;
    while (player.GetCurrentHp() > 0 and monster.GetCurrentHp() > 0)
    {
        Turn += 1;
        if (player.GetPower() <= 0 or monster.GetPower() <= 0)
        {
            return { BattleResult::Lose, BattleInfos };
        }
        monster.TakeDamage(PlayerAttackDamage);
        if (monster.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerWin(Turn,"Attack", PlayerAttackDamage, 0, player.GetCurrentHp(), monster.GetCurrentHp());
            BattleInfos.push_back(PlayerWin);
            return { BattleResult::Win, BattleInfos};
        }

        player.TakeDamage(PlayerTakeDamage);
        if (player.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerLose(Turn, "Attack", PlayerAttackDamage, PlayerTakeDamage, player.GetCurrentHp(),monster.GetCurrentHp());
            BattleInfos.push_back(PlayerLose);
            break;
        }
        BattleInfo InBattle(Turn, "Attack", PlayerAttackDamage, PlayerTakeDamage, player.GetCurrentHp(), monster.GetCurrentHp());
        BattleInfos.push_back(InBattle);
    }
    return { BattleResult::Lose, BattleInfos};
}

