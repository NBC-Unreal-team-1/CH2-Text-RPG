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
}

std::unique_ptr<Potion> Potion::CreateById(int Id)
{
    const auto& table = GetPotionTable();

    //포션 테이블에서 Id를 통해 위치 찾기
    auto it = std::find_if(table.begin(), table.end(),
        [Id](const std::pair<int, PotionData>& entry)
        {
            return entry.first == Id;
        });

    if (it == table.end())
        return nullptr; // 이 Id는 포션이 아님

    return std::make_unique<Potion>(Id, it->second.Type, it->second.Amount); //유니크 포인터로 포션 객체 생성
}

void Potion::Use(Player& player)
{
    switch (Type)
    {
    case PotionType::Health:
    {
        int newHp = player.GetCurrentHp() + GetAmount();
        newHp = std::min(newHp, player.GetMaxHp()); // 최대치 초과 방지
        player.SetCurrentHp(newHp);
        break;
    }

    case PotionType::Mana:
        int newMp = player.GetCurrentMp() + GetAmount();
        newMp = std::min(newMp, player.GetMaxMp()); // 최대치 초과 방지
        player.SetCurrentHp(newMp);
        break;
        break;
    }
}

PotionType Potion::GetType() const
{
    return this->Type;
}

int Potion::GetAmount() const
{
    return this->Amount;
}
