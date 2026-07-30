#include "Item.h"


Item::Item(int Id)
    : Id(Id), Name("") 
{
    // TODO: ID로 name 조회해서 채우기
}

Item::~Item()
{
}

int Item::GetId() const
{
    return this->Id;
}

const std::string& Item::GetName() const
{
    return this->Name;
}

