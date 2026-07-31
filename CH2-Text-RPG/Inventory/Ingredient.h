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

    //재료 사용
    void Use(Player& player) override;

    //"내가 재료다"라고 알려줌
    ItemType GetItemType() const override { return ItemType::Ingredient; }

protected:
private:
};