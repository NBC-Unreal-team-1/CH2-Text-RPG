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
            { 100, "" },
            { 101, "" },
            { 102, "" },
            { 103, "" },
            { 104, "" },
            { 105, "" },
            { 106, "" },
            { 107, "" },
            { 108, "" },
            { 109, "" },

        };
        return table;
    }
}

Item::Item(int Id)
    : Id(Id), Name("") 
{
    // TODO: 위 테이블로 아이템 초기화
}

Item::~Item()
{
}

std::unique_ptr<Item> Item::CreateItem(int Id)
{
    // TODO: ingredient, potion에 따라 조금 다르게 아이템 생성 후 유니크 포인터 반환
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

