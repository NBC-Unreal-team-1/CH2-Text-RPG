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
    Monster& monster
)
{
    // TODO: Run an automatic battle.
    return { BattleResult::Lose, {} };
}
