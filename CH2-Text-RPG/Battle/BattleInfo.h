#pragma once
#include <string>

struct BattleInfo
{

    std::string SkillName;

    std::string MonsterName;

    int MonsterId = 0;

    int Turn = 0;

    int MonsterAttackDamage = 0;

    int PlayerAttackDamage = 0;

    int PlayerRemainingHP = 0;

    int MonsterRemainingHP = 0;

    BattleInfo(
        int turn,
        std::string skillName,
        std::string monsterName,
        int monsterId,
        int attackDamage,
        int getDamage,
        int playerHP,
        int monsterHP
    )
    {
        this->Turn = turn;

        this->SkillName = skillName;

        this->MonsterName = monsterName;

        this->MonsterId = monsterId;

        this->MonsterAttackDamage = getDamage;

        this->PlayerAttackDamage = attackDamage;

        this->PlayerRemainingHP = playerHP;

        this->MonsterRemainingHP = monsterHP;

    }
};
