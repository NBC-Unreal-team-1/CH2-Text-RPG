#pragma once
#include <vector>
#include "ShopItem.h"

class Player;
class ShopManager
{
public:
    ShopManager();
    ~ShopManager();

	//상점 아이템 목록 반환
    const std::vector<ShopItem>& GetShopItems() const;

    //구매가능여부 확인
    bool CanPurchase
    (
        const Player& player,
        int itemId
    ) const;

    //아이템 구매
    bool PurchaseItem
    (
        Player& player,
        int itemId
    );
protected:
private:

	//아이템 찾기
    const ShopItem* FindShopItem(int itemId) const;
    std::vector<ShopItem> ShopItems;
};
