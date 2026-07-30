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
    void SetLevel(int level);

    int GetMaxHp() const; // HP
    void SetMaxHp(int maxHp);
     int GetCurrentHp() const;
    void SetCurrentHp(int currentHp);

    void TakeDamage(int damage);
    bool IsAlive() const;

    int GetMaxMp() const; // MP
    void SetMaxMp(int maxMp);
    int GetCurrentMp() const;
    void SetCurrentMp(int currentMp);

    int GetPower() const; // Power
    void SetPower(int power);

    int GetDefence() const; // Defence
    void SetDefence(int defence);

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
