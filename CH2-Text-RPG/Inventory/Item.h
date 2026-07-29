#pragma once
#include <string>

class Player;

//요리 재료 객체
class Item
{
public:
    Item(int id, std::string name);
    virtual ~Item();

    //ID와 이름 Get
    int GetId() const;
    const std::string& GetName() const;

    //아이템 사용 순수가상함수(재료 사용, 포션 사용)
    virtual void Use(Player& player) = 0;

protected:
    int id;
    std::string name;
};
