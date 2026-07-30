#pragma once

#include <string>

struct BattleInfo
{
    int GetDamage = 0;
    int AttackDamage = 0;
    std::string SkillName;
 

    BattleInfo(int getDamage, int attackDamage, std::string skillName)
    {
        this->GetDamage = getDamage;
        this->AttackDamage = attackDamage;
        this->SkillName = skillName;
    }
};
