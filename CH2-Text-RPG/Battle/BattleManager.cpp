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

std::pair<BattleResult, std::vector<BattleInfo>> BattleManager::StartBattle(
    Player& player,
    Monster monster
)
{
    while (player.GetCurrentHp() > 0 and monster.GetCurrentHp() > 0)
    {
        if (player.GetPower() <= 0)
        {
            return { BattleResult::Lose, BattleInfos };;
        }
        monster.TakeDamage(player.GetPower());
        if (monster.GetCurrentHp() <= 0)
        {
            BattleInfo a(0, player.GetPower(), "Attack");
            BattleInfos.push_back(a);
            return { BattleResult::Win, BattleInfos};
        }
        player.TakeDamage(monster.GetPower());
        if (player.GetCurrentHp() <= 0)
        {
            BattleInfo b(monster.GetPower(),player.GetPower(), "Attack");
            BattleInfos.push_back(b);
            break;
        }
        BattleInfo c(monster.GetPower(), player.GetPower(),"Attack");
        BattleInfos.push_back(c);
    }
    return { BattleResult::Lose, BattleInfos};
}

void BattleManager::CearBattleInfos()
{
    BattleInfos.clear();
}
