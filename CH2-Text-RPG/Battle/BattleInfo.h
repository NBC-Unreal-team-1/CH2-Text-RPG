#pragma once
#include <iostream>
#include <string>



struct BattleInfo
{
	int GetDamage;
	int AttackDamage;
	std::string SkillName;


	BattleInfo(int getDamage, int attackDamage, std::string skillName)
	{
		this->GetDamage = getDamage;
		this->AttackDamage = attackDamage;
		this->SkillName = skillName;
	}
	

};






