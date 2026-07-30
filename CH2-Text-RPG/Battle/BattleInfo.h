#pragma once
#include <string>

struct BattleInfo
{

    std::string SkillName;

    int Turn = 0;

    int MonsterAttackDamage = 0;

    int PlayerAttackDamage = 0;

    int PlayerRemainingHP = 0;

    int MonsterRemainingHP = 0;

    BattleInfo(int turn, std::string skillName,int attackDamage, int getDamage,int playerHP,int monsterHP)
    {
        this->Turn = turn;

        this->SkillName = skillName;

        this->MonsterAttackDamage = getDamage;

        this->PlayerAttackDamage = attackDamage;

        this->PlayerRemainingHP = playerHP;

        this->MonsterRemainingHP = monsterHP;

    }
};
