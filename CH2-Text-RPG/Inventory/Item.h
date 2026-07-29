#pragma once

#include <string>

class Player;

class Item
{
public:
    Item();
    virtual ~Item();

    const std::string& GetName() const;
    void SetName(const std::string& name);
    int GetPrice() const;
    void SetPrice(int price);
    virtual void Use(Player& player) = 0;

protected:
    std::string Name;
    int Price = 0;

private:
};
