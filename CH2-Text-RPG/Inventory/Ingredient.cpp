#include "Ingredient.h"
#include "../Character/Player.h"
#include <vector>
#include <algorithm>

namespace
{
    // 재료로 존재하는 Id 목록
    const std::vector<int>& GetIngredientIdTable()
    {
        static const std::vector<int> table =
        {
            100, //양상추
            101, //양파
            102, //피클
            103, //토마토
            104, //케첩
            105, //마요네즈
            106, //베이컨
            107, //치즈
            108, //빵
            109  //패티
        };
        return table;
    }
}

Ingredient::Ingredient(int Id)
    : Item(Id){}

Ingredient::~Ingredient()
{
}

//Id로 재료 생성
std::unique_ptr<Ingredient> Ingredient::CreateById(int Id)
{
    const auto& table = GetIngredientIdTable();

    //Id로 재료 테이블 찾아서 위치 저장
    auto it = std::find(table.begin(), table.end(), Id);

    if (it == table.end())
    {
        return nullptr; // 이 Id는 재료가 아님
    }

    return std::make_unique<Ingredient>(Id);
}

void Ingredient::Use(Player& player)
{
    
}

