#pragma once

#include "Character.h"

class Monster : public Character
{
public:
    Monster();
    ~Monster() override;

    void GenerateStat();

protected:
private:
};
