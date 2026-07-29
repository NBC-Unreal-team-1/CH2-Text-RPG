#pragma once

#include <string>

class Character
{
public:
    Character();
    virtual ~Character();

    const std::string& GetName() const;
    void SetName(const std::string& name);
    int GetLevel() const;
    void SetLevel(int level);
    int GetMaxHp() const;
    void SetMaxHp(int maxHp);
    int GetCurrentHp() const;
    void SetCurrentHp(int currentHp);
    int GetAttack() const;
    void SetAttack(int attack);

protected:
    std::string Name;
    int Level = 0;
    int MaxHp = 0;
    int CurrentHp = 0;
    int Attack = 0;

private:
};
