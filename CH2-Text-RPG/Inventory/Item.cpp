#include "Item.h"
#include "Potion.h"
#include "Ingredient.h"
#include <vector>
#include <utility>
#include <algorithm>

namespace
{
    // 모든 아이템 공통 정보: id -> 이름
    const std::vector<std::pair<int, std::string>>& GetItemNameTable()
    {
        static const std::vector<std::pair<int, std::string>> table =
        {
            { 1, "체력 포션" },
            { 2, "마나 포션" },
            { 100, "양상추" },
            { 101, "양파" },
            { 102, "피클" },
            { 103, "토마토" },
            { 104, "케첩" },
            { 105, "마요네즈" },
            { 106, "베이컨" },
            { 107, "치즈" },
            { 108, "빵" },
            { 109, "패티" },
            { 110, "감자" }
        };
        return table;
    }
}

Item::Item(int Id)
    : Id(Id), Name("") 
{
    const auto& table = GetItemNameTable();

    //아이템 테이블 검색하여 위치 반환
    auto it = std::find_if(table.begin(), table.end(),
        [Id](const std::pair<int, std::string>& entry)
        {
            return entry.first == Id;
        });

    if (it != table.end())
        Name = it->second;
}

Item::~Item()
{
}

std::unique_ptr<Item> Item::CreateItem(int ItemId)
{
    if (auto potion = Potion::CreateById(ItemId))
        return potion; // unique_ptr<Potion> -> unique_ptr<Item> 암묵적 변환(상속 관계)

    if (auto ingredient = Ingredient::CreateById(ItemId))
        return ingredient;

    return nullptr; // 어떤 타입에도 해당 안 되면 nullptr
}

int Item::GetId() const
{
    return this->Id;
}

const std::string& Item::GetName() const
{
    return this->Name;
}

