#pragma once

#include "Item.h"

enum class PotionType
{
    Health,
    Mana
};

//아이템 클래스 상속 받음
class Potion : public Item
{
public:
    Potion(int Id, PotionType Type, int Amount);
    virtual ~Potion();

    //포션 사용
    void Use(Player& player) override;

    //포션 종류와 수치 Get
    PotionType GetType() const;
    int GetAmount() const;

protected:
private:
    PotionType Type;
    int Amount;
};
