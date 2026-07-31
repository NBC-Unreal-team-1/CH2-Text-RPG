#include "Skill.h"

Skill::Skill(
    int id,
    const std::string& name,
    int damage,
    int manaCost,
    SkillTriggerType triggerType,
    int triggerValue
)
    : Id(id)
    , Name(name)
    , Damage(damage)
    , ManaCost(manaCost)
    , TriggerType(triggerType)
    , TriggerValue(triggerValue)
{
}

int Skill::GetId() const
{
    return Id;
}

const std::string& Skill::GetName() const
{
    return Name;
}

int Skill::GetManaCost() const
{
    return ManaCost;
}

int Skill::GetDamage() const
{
    return Damage;
}

SkillTriggerType Skill::GetTriggerType() const
{
    return TriggerType;
}

int Skill::GetTriggerValue() const
{
    return TriggerValue;
}