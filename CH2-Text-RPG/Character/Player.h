#pragma once

#include "Character.h"
#include "../Inventory/Inventory.h"
#include "../Skill.h"
#include <vector>

class Player : public Character
{
public:
    Player();
    ~Player() override;

public:
    int GetExp() const;
    void SetExp(int Exp);
    int GetGold() const;
    void SetGold(int Gold);
    void AddGold(int Gold);
    Inventory& GetInventory();
    const Inventory& GetInventory() const;
    const Skill* GetSkillById(int Id) const;

protected:
private:
    int Exp = 0;
    int Gold = 0;
    Inventory PlayerInventory;
    std::vector<Skill> Skills;
};
