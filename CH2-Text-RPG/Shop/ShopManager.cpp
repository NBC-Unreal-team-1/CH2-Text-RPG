#include "ShopManager.h"
#include "../Character/Player.h"
ShopManager::ShopManager()
    : ShopItems
    {
        { 1, 100 },
        { 2, 100 }
    }
{
}

ShopManager::~ShopManager()
{
    // TODO: Implement shop manager destruction.
}

//상점 아이템 목록 반환
const std::vector<ShopItem>& ShopManager::GetShopItems() const
{
    return ShopItems;
}


//아이템 찾기
const ShopItem* ShopManager::FindShopItem(int itemId) const
{
    for (const ShopItem& shopItem : ShopItems)
    {
        if (shopItem.id == itemId)
        {
            return &shopItem;
        }
    }

    return nullptr;
}



//구매 가능 여부 판단
bool ShopManager::CanPurchase(
    const Player& player,
    int itemId
) const 
{
    if(itemId <= 0)
    {
        return false;
    }
    const ShopItem* shopItem = FindShopItem(itemId);

    if (shopItem == nullptr || shopItem->price <= 0)
    {
        return false;
    }
    return player.GetGold() >= shopItem->price;
}


//구매
bool ShopManager::PurchaseItem
(
    Player& player,
    int itemId
) 
{   
	//구매 가능 여부 확인
    if (!CanPurchase(player, itemId))
    {
        return false;
	}


    const ShopItem* shopItem = FindShopItem(itemId);

    player.GetInventory().AddItem(itemId);

    if (!player.SpendGold(shopItem->price))
    {
        player.GetInventory().ReduceItem(itemId);
        return false;
    }
	return true;

}



