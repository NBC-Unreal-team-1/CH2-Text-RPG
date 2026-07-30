#pragma once
#include "Item.h"
#include <memory>

class Ingredient : public Item
{
public:
    Ingredient(int Id);
    virtual ~Ingredient();

    //Id로 재료 생성
    static std::unique_ptr<Ingredient> CreateById(int Id);

    //순수가상함수 정의용
    void Use(Player& player) override;

};