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
    Monster& monster,
    const Skill* selectedSkill
)
{
    ClearBattleInfos();
    int PlayerTakeDamage = std::max(monster.GetPower() - player.GetDefence(), 1);
    int Turn = 0;
    bool TrrigerSetisfied = false;
    while (player.GetCurrentHp() > 0 and monster.GetCurrentHp() > 0)
    {
        int PlayerAttackDamage = std::max(player.GetPower() - monster.GetDefence(), 1);
        std::string SkillName = "Attack";
        Turn += 1;
        if (player.GetPower() <= 0 or monster.GetPower() <= 0)
        {
            return { BattleResult::Lose, BattleInfos };
        }

        if (selectedSkill != nullptr)
        {
            switch (selectedSkill->GetTriggerType())
            {
            case SkillTriggerType::EveryNthTurn:
                TrrigerSetisfied = selectedSkill->GetTriggerValue() > 0 && Turn % selectedSkill->GetTriggerValue() == 0;
                break;
            case SkillTriggerType::PlayerHpBelow:
                if (player.GetMaxHp() <= 0)
                {
                    break;
                }
                int HpPercent = player.GetCurrentHp() * 100 / player.GetMaxHp();
                TrrigerSetisfied = HpPercent <= selectedSkill->GetTriggerValue();
                break;
            }
        }
        if (TrrigerSetisfied && selectedSkill->GetManaCost() <= player.GetCurrentMp())
        {
            PlayerAttackDamage = std::max(selectedSkill->GetDamage() - monster.GetDefence(), 1);
            player.SetCurrentMp(player.GetCurrentMp() - selectedSkill->GetManaCost());
            SkillName = selectedSkill->GetName();
            TrrigerSetisfied = false;
        }
        monster.TakeDamage(PlayerAttackDamage);
        if (monster.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerWin(
                Turn,
                SkillName,
                monster.GetName(),
                monster.GetId(),
                PlayerAttackDamage,
                0,
                player.GetCurrentHp(),
                monster.GetCurrentHp()
            );
            BattleInfos.push_back(PlayerWin);
            return { BattleResult::Win, BattleInfos};
        }
        player.TakeDamage(PlayerTakeDamage);
   
        if (player.GetCurrentHp() <= 0)
        {
            BattleInfo PlayerLose(
                Turn,
                SkillName,
                monster.GetName(),
                monster.GetId(),
                PlayerAttackDamage,
                PlayerTakeDamage,
                player.GetCurrentHp(),
                monster.GetCurrentHp()
            );
            BattleInfos.push_back(PlayerLose);
            break;
        }
        BattleInfo InBattle(
            Turn,
            SkillName,
            monster.GetName(),
            monster.GetId(),
            PlayerAttackDamage,
            PlayerTakeDamage,
            player.GetCurrentHp(),
            monster.GetCurrentHp()
        );
        BattleInfos.push_back(InBattle);
    }
    return { BattleResult::Lose, BattleInfos};
}

