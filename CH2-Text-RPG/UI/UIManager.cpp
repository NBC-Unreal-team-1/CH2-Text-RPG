#include "UIManager.h"

#include "../Character/Monster.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
	// TODO: Implement UI manager destruction.
}

static void WaitOutputDelay(int time = 300, int count = 3)
{
	FlushInput();
	std::cout << "Wait";
	for (int i = 0; i < count; ++i)
	{
		std::cout << ". ";
		Sleep(time);
	}
	FlushInput();
	std::cout << std::endl << std::endl;
}

static int GetInt(ScreenData& screen)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	std::string in;
	std::getline(std::cin, in);

	try
	{
		if (stoi(in) < 0)
		{
			return -1;
		}
		if (!std::all_of(in.begin(), in.end(), ::isdigit))
		{
			return -1;
		}

		return stoi(in);
	}
	catch (const std::invalid_argument&)
	{
		screen.MoveToInputPos();
		std::cout << "숫자만 입력하세요.";
		Sleep(1000);
		screen.MoveToInputPos();
		screen.ClearInput();
		FlushInput();
		return -1;
	}
	catch (const std::out_of_range&)
	{
		screen.MoveToInputPos();
		std::cout << "수의 범위를 벗어났습니다.";
		std::cout << ClearToEndOfLine(csbi.dwCursorPosition.X);
		Sleep(1000);
		screen.MoveToInputPos();
		screen.ClearInput();
		FlushInput();
		return -1;
	}
}

int UIManager::GetInput(ScreenData& screen, int min, int max) const
{
	int result;
	while (true)
	{
		screen.MoveToInputPos();
		std::cout << min << "부터 " << max << " 사이의 값을 입력하세요.";
		Sleep(1000);
		screen.ClearInput();
		screen.MoveToInputPos();
		result = GetInt(screen);
		if (result <= max && result >= min)
		{
			break;
		}
	}
	ClearConsole();
	return result;
}

void UIManager::SetupPlayerInfo(Player& player)
{
	std::string name;
	int maxHp = 30;
	int power = 7;

	std::cout << "Name : ";
	std::getline(std::cin, name);
	ClearLine(0, 0);


	player.SetName(name);
	player.SetMaxHp(maxHp);
	player.SetCurrentHp(maxHp);
	player.SetPower(power);
}

int UIManager::PrintMenu() const
{
	int menuMin = 0;
	int menuMax = 4;
	ScreenData screen;
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("1: 여행을 떠나요 즐거운 마음으로 황금빛 태양 축제를 여는~", LineType::out);
	screen.AddLine("2: 빈손으로 여행을 떠난 나에게 남은 것이라곤...", LineType::out);
	screen.AddLine("3: 진정한 맛은 재료와 정성에서 시작된다.", LineType::out);
	screen.AddLine("4: 상점을 이용합니다.", LineType::out);
	screen.AddLine("0: 게임을 종료합니다.", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	if (!screen.GetHasInput())
	{
		return -1;
	}

	return GetInput(screen, menuMin, menuMax);
}

int UIManager::PrintInventory(const Inventory& inventory) const
{
	int menuMin = 0;
	int menuMax;
	ScreenData screen;
	screen.AddLine(border, LineType::out);
	screen.AddLine("아이템 목록", LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	for (int i = 0; i < inventory.GetItems().size(); ++i)
	{
		std::string itemName = inventory.GetItems()[i].ItemPtr->GetName();
		itemName = std::to_string(i + 1) + ": " + itemName +
			" (" + std::to_string(inventory.GetItemCount(inventory.GetItems()[i].ItemPtr->GetId())) + " ea)";
		screen.AddLine(itemName, LineType::out);
	}
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);
	menuMax = static_cast<int>(inventory.GetItems().size());

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	if (!screen.GetHasInput())
	{
		return -1;
	}

	return GetInput(screen, menuMin, menuMax);
}

int UIManager::PrintRecipes(const RecipeManager& recipes, const Inventory& inventory) const
{
	int menuMin = 0;
	int menuMax;
	ScreenData screen;
	screen.AddLine(border, LineType::out);
	screen.AddLine("레시피 목록", LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	for (int i = 0; i < recipes.GetAllRecipes().size(); ++i)
	{
		std::string text = recipes.GetAllRecipes()[i]->Name;
		text = std::to_string(i + 1) + ": " + text;
		screen.AddLine(text, LineType::out);
	}
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);
	menuMax = static_cast<int>(recipes.GetAllRecipes().size());

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	if (!screen.GetHasInput())
	{
		return -1;
	}

	int choice = GetInput(screen, menuMin, menuMax);
	if (choice != 0)
	{
		if (PrintSelectedRecipe(
			recipes.GetAllRecipes()[choice - 1],
			inventory
		) != 1)
		{
			return 0;
		}
	}

	return choice;
}

int UIManager::PrintSelectedRecipe(const Recipe* recipe, const Inventory& inventory) const
{
	ScreenData screen;
	int menuMin = 0;
	int menuMax = 1;
	std::string temp;
	int curQty;
	int reqQty;

	screen.AddLine(border, LineType::out);
	temp = "[" + recipe->Name + "의 레시피]";
	screen.AddLine(temp, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("---(필요한 것들)---", LineType::out);
	for (int i = 0; i < recipe->Ingredients.size(); ++i)
	{
		int curIngredientId = recipe->Ingredients[i].ItemId;
		temp = Item::GetNameById(curIngredientId);
		curQty = inventory.GetItemCount(curIngredientId);
		reqQty = recipe->Ingredients[i].Count;
		temp = std::to_string(i + 1) + ": " + temp
			+ "(" + std::to_string(curQty) + " / " + std::to_string(reqQty) + ")";
		screen.AddLine(temp, LineType::out);
	}
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("---(효과)---", LineType::out);
	temp = "체력 증가: " + std::to_string(recipe->HpBonus)
		+ "\n공격력 증가: " + std::to_string(recipe->AttackBonus)
		+ "\n방어력 증가: " + std::to_string(recipe->DefenseBonus);
	screen.AddLine(temp, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("1: 제작", LineType::out);
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}
	
	return GetInput(screen, menuMin, menuMax);
}

void UIManager::PrintInsufficientIngredients() const
{
	ClearConsole();
	std::cout << border << '\n';
	std::cout << "재료가 부족합니다." << '\n';
	std::cout << "레시피 선택 화면으로 돌아갑니다." << '\n';
	std::cout << border << '\n';
	WaitOutputDelay(500, 2);
}

void UIManager::PrintRecipeSuccess(
	const std::string& RecipeName,
	int HpBonus,
	int AttackBonus,
	int DefenseBonus,
	const Player& player,
	bool IsNextStageUnlocked
) const
{
	ClearConsole();
	std::cout << border << '\n';
	std::cout << "요리 성공!" << '\n';
	std::cout << RecipeName << "을(를) 즉시 섭취했습니다." << '\n';
	std::cout << border << '\n';
	std::cout << "최대 HP +" << HpBonus
		<< " (" << player.GetMaxHp() << ")" << '\n';
	std::cout << "공격력 +" << AttackBonus
		<< " (" << player.GetPower() << ")" << '\n';
	std::cout << "방어력 +" << DefenseBonus
		<< " (" << player.GetDefence() << ")" << '\n';

	if (IsNextStageUnlocked)
	{
		std::cout << border << '\n';
		std::cout << "다음 스테이지가 열렸습니다!" << '\n';
	}

	std::cout << border << '\n';
	WaitOutputDelay(500, 3);
}

int UIManager::PrintShop(const std::vector<ShopItem>& shopItems)
{
	int menuMin = 0;
	int menuMax;
	ScreenData screen;
	std::string temp;
	screen.AddLine(border, LineType::out);
	screen.AddLine("상점", LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	for (size_t i = 0; i < shopItems.size(); ++i)
	{
		temp = std::to_string(i + 1) + ". " + Item::GetNameById(shopItems[i].id) +
			" : " + std::to_string(shopItems[i].price) + "골드";
		screen.AddLine(temp, LineType::out);
	}
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);
	menuMax = static_cast<int>(shopItems.size());

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	if (!screen.GetHasInput())
	{
		return -1;
	}

	const int choice = GetInput(screen, menuMin, menuMax);
	if (choice == 0)
	{
		return 0;
	}

	const ShopItem& SelectedItem = shopItems[choice - 1];
	if (PrintSelectedShopItem(SelectedItem) != 1)
	{
		return 0;
	}

	return SelectedItem.id;
}

int UIManager::PrintSelectedShopItem(const ShopItem& shopItem)
{
	ScreenData screen;
	int menuMin = 0;
	int menuMax = 1;
	std::string temp;
	
	screen.AddLine(border, LineType::out);
	screen.AddLine("상점", LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	temp = Item::GetNameById(shopItem.id) + "\n가격: " + std::to_string(shopItem.price);
	screen.AddLine(temp, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("1: 구매", LineType::out);
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	return GetInput(screen, menuMin, menuMax);
}

void UIManager::PrintShopPurchaseResult(
	bool IsPurchased,
	const Player& player
) const
{
	ClearConsole();
	std::cout << border << '\n';
	std::cout << (IsPurchased
		? "구매가 완료되었습니다."
		: "구매할 수 없습니다. 골드를 확인해주세요.") << '\n';
	std::cout << "현재 골드: " << player.GetGold() << '\n';
	std::cout << border << '\n';
	WaitOutputDelay(500, 2);
}

int UIManager::PrintSkillSelection(
	const Player& player,
	const Monster& monster
) const
{
	const std::vector<Skill>& Skills = player.GetSkills();
	ScreenData screen;
	screen.AddLine(border, LineType::out);
	screen.AddLine("[" + monster.GetName() + "] 전투 스킬 선택", LineType::out);
	screen.AddLine(
		"현재 MP: " + std::to_string(player.GetCurrentMp()) +
		" / " + std::to_string(player.GetMaxMp()),
		LineType::out
	);
	screen.AddLine(border, LineType::out);
	screen.AddLine("0: 스킬을 사용하지 않음", LineType::out);

	for (std::size_t Index = 0; Index < Skills.size(); ++Index)
	{
		const Skill& CurrentSkill = Skills[Index];
		std::string TriggerText;

		switch (CurrentSkill.GetTriggerType())
		{
		case SkillTriggerType::EveryNthTurn:
			TriggerText = std::to_string(CurrentSkill.GetTriggerValue()) +
				"턴마다 자동 사용";
			break;
		case SkillTriggerType::PlayerHpBelow:
			TriggerText = "HP " +
				std::to_string(CurrentSkill.GetTriggerValue()) +
				"% 이하에서 자동 사용";
			break;
		default:
			TriggerText = "자동 사용";
			break;
		}

		screen.AddLine(
			std::to_string(Index + 1) + ": " + CurrentSkill.GetName() +
			" / 데미지 " + std::to_string(CurrentSkill.GetDamage()) +
			" / MP " + std::to_string(CurrentSkill.GetManaCost()) +
			" / " + TriggerText,
			LineType::out
		);
	}

	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int Index = 0; Index < screen.GetDataSize(); ++Index)
	{
		screen.PrintLine(Index);
	}

	const int Selection = GetInput(
		screen,
		0,
		static_cast<int>(Skills.size())
	);
	if (Selection == 0)
	{
		return 0;
	}

	return Skills[Selection - 1].GetId();
}

void UIManager::PrintBossIntroStory(const Monster& boss) const
{
	ClearConsole();
	std::cout << border << '\n';
	std::cout << "궁극의 햄버거가 완성되자, 주변의 공기가 무겁게 가라앉는다." << '\n';
	Sleep(1200);
	std::cout << "어둠 속에서 거대한 그림자가 천천히 다가온다..." << '\n';
	Sleep(1200);
	std::cout << border << '\n';
	std::cout << boss.GetName()
		<< ": \"용케도 햄버거를 완성했군, 일개 요리사여...\"" << '\n';
	Sleep(1500);
	std::cout << boss.GetName()
		<< ": \"하지만 그 햄버거는 아직 완전하지 않다.\"" << '\n';
	Sleep(1500);
	std::cout << boss.GetName()
		<< ": \"나를 넘어서야 비로소 마지막 한 조각을 얻을 수 있을 것이다!\"" << '\n';
	Sleep(1500);
	std::cout << border << '\n';
	std::cout << "최종 보스, " << boss.GetName() << "가 나타났다!" << '\n';
	std::cout << border << '\n';
	Sleep(1500);
}

void UIManager::PrintEndingStory() const
{
	ClearConsole();
	std::cout << border << '\n';
	std::cout << "감자 대왕이 남긴 감자로 마침내 최종의 감자튀김을 완성했다." << '\n';
	Sleep(1400);
	std::cout << "바삭한 감자튀김을 한 입 베어 물었다." << '\n';
	Sleep(1400);
	std::cout << "..." << '\n';
	Sleep(1200);
	std::cout << "\"무언가 부족하다...\"" << '\n';
	Sleep(1600);
	std::cout << "다시 한 입을 먹었지만, 허전함은 사라지지 않았다." << '\n';
	Sleep(1400);
	std::cout << "\"목이 마르다...\"" << '\n';
	Sleep(1800);
	std::cout << border << '\n';
	std::cout << "멀리서 톡 쏘는 기포 소리가 들려온다..." << '\n';
	Sleep(1800);
	std::cout << '\n' << "To be continued..." << '\n';
	std::cout << border << '\n';
	Sleep(2000);
}

void SetBattleLog(const BattleInfo& currentLog, ScreenData& data, std::string border, std::string emptyLine)
{
	std::string playerTurn;
	std::string monsterTurn;
	std::string resultText;
	std::string temp;

	playerTurn = "플레이어의 공격!\n" + currentLog.MonsterName +"에게 "
		+ std::to_string(currentLog.PlayerAttackDamage) + "의 데미지!";
	monsterTurn = currentLog.MonsterName + "의 공격!\n플레이어에게 "
		+ std::to_string(currentLog.MonsterAttackDamage) + "의 데미지!";
	resultText = "남은 체력\n플레이어: " + std::to_string(currentLog.PlayerRemainingHP)
		+ " / 몬스터: " + std::to_string(currentLog.MonsterRemainingHP);

	temp = ">" + std::to_string(currentLog.Turn) + "번째 턴!";
	data.AddLine(temp, LineType::out);
	data.AddLine(playerTurn, LineType::out);
	data.AddLine(monsterTurn, LineType::out);
	data.AddLine(emptyLine, LineType::out);
	data.AddLine(resultText, LineType::out);
	data.AddLine(emptyLine, LineType::wait);
}

int UIManager::PrintBattleLog(
	const std::pair<BattleResult, std::vector<BattleInfo>>& Result
) const
{
	const std::vector<BattleInfo>& BattleLogs = Result.second;
	ScreenData screen;
	int menuMin = 0;
	int menuMax = 0;

	screen.AddLine(border, LineType::out);
	screen.AddLine("세계 최고의 햄버거를 만들기 위하여.", LineType::out);
	screen.AddLine(border, LineType::out);
	if (!BattleLogs.empty())
	{
		const BattleInfo& FirstLog = BattleLogs.front();
		screen.AddLine("[" + FirstLog.MonsterName + "]", LineType::out);
		screen.AddLine(
			Monster::GetAsciiArtById(FirstLog.MonsterId),
			LineType::out
		);
		screen.AddLine(border, LineType::out);
	}
	screen.AddLine(emptyLine, LineType::ceiling);

	for (std::size_t Index = 0; Index < BattleLogs.size(); ++Index)
	{
		SetBattleLog(BattleLogs[Index], screen, border, emptyLine);
	}

	screen.AddLine(border, LineType::out);
	std::string resultText =
		(Result.first == BattleResult::Win) ?
		"싸웠더니 배가 고프다. 맛있는 거 먹으러 가자." : "나는 아직 네녀석을 요리할 자격이 없나보군...";
	screen.AddLine(resultText, LineType::out);
	screen.AddLine(border, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
		if (screen.CheckIsWait(i))
		{
			WaitOutputDelay(1000, 3);
			screen.ResetToCeiling();
		}
	}

	if (!screen.GetHasInput())
	{
		return -1;
	}

	return GetInput(screen, menuMin, menuMax);
}

int UIManager::PrintBattleResult(const Player& player, const Monster& monster) const
{
	ScreenData screen;
	int menuMin = 0;
	int menuMax = 0;
	std::string temp;

	screen.AddLine(border, LineType::out);
	screen.AddLine("재료를 손에 넣었다.", LineType::out);
	screen.AddLine(border, LineType::out);
	
	temp = "획득한 골드: " + std::to_string(monster.GetDropGold());
	screen.AddLine(temp, LineType::out);

	const int IngredientId = monster.GetDropIngredientId();
	const int IngredientAmount = monster.GetDropIngredientAmount();
	const InventorySlot* RewardSlot =
		player.GetInventory().FindSlot(IngredientId);

	if (RewardSlot != nullptr && RewardSlot->ItemPtr != nullptr)
	{
		temp = "획득한 " + RewardSlot->ItemPtr->GetName() + ": " + std::to_string(IngredientAmount) + "개";
		screen.AddLine(temp, LineType::out);
		temp = "총 " + RewardSlot->ItemPtr->GetName() + ": " + std::to_string(RewardSlot->Count) + "개";
		screen.AddLine(temp, LineType::out);
	}

	std::cout << "Total Gold: "
		<< player.GetGold() << "\n\n";
	temp = "총 골드: " + std::to_string(player.GetGold());
	screen.AddLine(temp, LineType::out);
	screen.AddLine(border, LineType::out);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	if (!screen.GetHasInput())
	{
		WaitOutputDelay(500, 4);
		return -1;
	}

	return GetInput(screen, menuMin, menuMax);
}
