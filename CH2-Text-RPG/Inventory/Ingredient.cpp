#include "Ingredient.h"
#include "../Character/Player.h"
#include <vector>
#include <utility>
#include <algorithm>

Ingredient::Ingredient(int Id)
    : Item(Id){}

Ingredient::~Ingredient()
{
}

std::unique_ptr<Ingredient> Ingredient::CreateById(int Id)
{
    // TODO: 아이디를 받아서 재료를 유니크 포인터로 반환
    return nullptr;
}

void Ingredient::Use(Player& player)
{
    //사용 안함. 요리할 땐 Inventory 클래스의 RemoveItem()으로.
}

