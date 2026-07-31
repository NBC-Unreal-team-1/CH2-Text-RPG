#pragma once
#include <string>
#include <memory>

class Player;

enum class ItemType
{
    Potion,
    Ingredient
};

class Item
{
public:
    Item(int Id);
    virtual ~Item();

    //아이템 생성
    static std::unique_ptr<Item> CreateItem(int ItemId);

    //ID와 이름 Get
    int GetId() const;
    const std::string& GetName() const;

    //아이템 사용 순수가상함수(재료 사용, 포션 사용)
    virtual void Use(Player& player) = 0;

    //자식 클래스의 아이템 타입(포션, 재료) 알려줌
    virtual ItemType GetItemType() const = 0;
protected:
    int Id;
    std::string Name;
};
