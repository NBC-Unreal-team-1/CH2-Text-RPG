#pragma once

#include <string>

class Character
{
public:
    Character();
    virtual ~Character();

    const std::string& GetName() const;
    void SetName(const std::string& name);

    int GetLevel() const; // Level
    void SetLevel(int Level);

    int GetMaxHp() const; // HP
    void SetMaxHp(int MaxHp);
    int GetCurrentHp() const;
    void SetCurrentHp(int CurrentHp);

    void TakeDamage(int Damage);
    bool IsAlive() const;

    int GetMaxMp() const; // MP
    void SetMaxMp(int MaxMp);
    int GetCurrentMp() const;
    void SetCurrentMp(int CurrentMp);

    int GetPower() const; // Power
    void SetPower(int Power);

    int GetDefence() const; // Defence
    void SetDefence(int Defence);

protected:
    std::string Name;
    int Level = 0;
    int MaxHp = 0;
    int CurrentHp = 0;
    int MaxMp = 0;
    int CurrentMp = 0;
    int Power = 0;
    int Defence = 0;

private:
};
