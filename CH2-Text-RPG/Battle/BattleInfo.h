#pragma once
#include <string>

struct BattleInfo
{
    int GetDamage = 0;
    int AttackDamage = 0;
    std::string SkillName;
    int PlayerHP = 0;
    int MonsterHP = 0;

    BattleInfo(std::string skillName,int attackDamage, int getDamage,int playerHP,int monsterHP)
    {
        this->SkillName = skillName;
        this->GetDamage = getDamage;
        this->AttackDamage = attackDamage;
        this->PlayerHP = playerHP;
        this->MonsterHP = monsterHP;

    }
};
