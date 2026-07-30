#include "Potion.h"
#include "../Character/Player.h"
#include <vector>
#include <utility>
#include <algorithm>
namespace
{
    struct PotionData
    {
        PotionType Type;
        int Amount;
    };

    // 포션 전용 테이블: id -> 타입, 수치
    const std::vector<std::pair<int, PotionData>>& GetPotionTable()
    {
        static const std::vector<std::pair<int, PotionData>> table =
        {
            { 1, { PotionType::Health, 30 } },
            { 2, { PotionType::Mana, 20 } },
        };
        return table;
    }
}

Potion::Potion(int Id, PotionType Type, int Amount)
    : Item(Id), Type(Type), Amount(Amount) {}

Potion::~Potion()
{
    // TODO: Implement potion destruction.
}

std::unique_ptr<Potion> Potion::CreateById(int Id)
{
    //TODO: ID로 포션 만들기
    return nullptr;
}

void Potion::Use(Player& player)
{
    // TODO: 포션 타입에 따라 다르게
}

PotionType Potion::GetType() const
{
    return this->Type;
}

int Potion::GetAmount() const
{
    return this->Amount;
}
