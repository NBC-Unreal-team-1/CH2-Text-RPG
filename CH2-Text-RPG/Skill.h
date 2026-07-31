#pragma once

#include <string>

enum class SkillTriggerType
{
	PlayerHpBelow,
	EveryNthTurn
};

class Skill
{
public: 
	Skill(
		int id,
		const std::string& name,
		int damage,
		int manaCost,
		SkillTriggerType triggerType,
		int triggerValue
	);

public:
	int GetId() const;
	const std::string& GetName() const;
	int GetDamage() const;
	int GetManaCost() const;
	SkillTriggerType GetTriggerType() const;
	int GetTriggerValue() const;


private:
	int Id = 0;
	std::string Name;
	int Damage = 0;
	int ManaCost = 0;
	SkillTriggerType TriggerType = SkillTriggerType::EveryNthTurn;
	int TriggerValue = 0;

};