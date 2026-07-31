#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
	// TODO: Implement UI manager destruction.
}

void WaitOutputDelay(int time = 300, int count = 3)
{
	FlushInput();
	std::cout << "Wait";
	for (int i = 0; i < count; ++i)
	{
		std::cout << ". ";
		Sleep(time);
	}
	FlushInput();
	std::cout << std::endl;
}

int GetInt(ScreenData& screen)
{
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
	int result;
	int menuMin = 1;
	int menuMax = 3;
	ScreenData menu;
	menu.AddLine(border, LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("1: 여행을 떠나요 즐거운 마음으로 황금빛 태양 축제를 여는~", LineType::out);
	menu.AddLine("2: 빈손으로 여행을 떠난 나에게 남은 것이라곤...", LineType::out);
	menu.AddLine("3: 진정한 맛은 재료와 정성에서 시작된다.", LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("Enter : ", LineType::in);


	for (int i = 0; i < menu.GetDataSize(); ++i)
	{
		menu.PrintLine(i);
	}

	if (!menu.GetHasInput())
	{
		return -1;
	}

	return GetInput(menu, menuMin, menuMax);
}

int UIManager::PrintInventory(const Inventory& inventory) const
{
	int result;
	int menuMin = 0;
	int menuMax;
	ScreenData menu;
	menu.AddLine(border, LineType::out);
	menu.AddLine("아이템 목록", LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	for (int i = 0; i < inventory.GetItems().size(); ++i)
	{
		std::string itemName = inventory.GetItems()[i].ItemPtr->GetName();
		itemName = std::to_string(i + 1) + ": " + itemName;
		menu.AddLine(itemName, LineType::out);
	}
	menu.AddLine("0 : exit", LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("Enter : ", LineType::in);
	menuMax = inventory.GetItems().size();

	ClearConsole();
	for (int i = 0; i < menu.GetDataSize(); ++i)
	{
		menu.PrintLine(i);
	}

	if (!menu.GetHasInput())
	{
		return -1;
	}

	return GetInput(menu, menuMin, menuMax);
}

int UIManager::PrintRecipes(const RecipeManager& recipes, const Inventory& inventory) const
{
	int result;
	int menuMin = 0;
	int menuMax;
	ScreenData menu;
	menu.AddLine(border, LineType::out);
	menu.AddLine("레시피 목록", LineType::out);
	menu.AddLine(emptyLine, LineType::in);
	for (int i = 0; i < recipes.GetAllRecipes().size(); ++i)
	{
		std::string text = recipes.GetAllRecipes()[i]->Name;
		text = std::to_string(i + 1) + ": " + text;
		menu.AddLine(text, LineType::out);
	}
	menu.AddLine("0 : exit", LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("Enter : ", LineType::in);
	menuMax = recipes.GetAllRecipes().size();

	ClearConsole();
	for (int i = 0; i < menu.GetDataSize(); ++i)
	{
		menu.PrintLine(i);
	}

	if (!menu.GetHasInput())
	{
		return -1;
	}

	int choice = GetInput(menu, menuMin, menuMax);
	if (choice != 0)
	{
		PrintSelectedRecipe(recipes.GetAllRecipes()[choice - 1], inventory);
	}

	return choice;
}

int UIManager::PrintSelectedRecipe(const Recipe* recipe, const Inventory& inventory) const
{
	ScreenData screen;
	int menuMin = 0;
	int menuMax = 0;
	std::string temp;
	int curQty;
	int reqQty;

	screen.AddLine(border, LineType::out);
	temp = "[" + recipe->Name + "의 레시피]";
	screen.AddLine(temp, LineType::out);
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
	screen.AddLine("0 : exit", LineType::out);
	screen.AddLine(emptyLine, LineType::out);
	screen.AddLine("Enter : ", LineType::in);

	ClearConsole();
	for (int i = 0; i < screen.GetDataSize(); ++i)
	{
		screen.PrintLine(i);
	}

	GetInput(screen, menuMin, menuMax);
	return -1;
}

void SetBattleLog(const BattleInfo& currentLog, ScreenData& data, std::string border, std::string emptyLine)
{
	std::string playerTurn;
	std::string monsterTurn;
	std::string resultText;

	playerTurn = "플레이어의 공격!\n몬스터에게 "
		+ std::to_string(currentLog.PlayerAttackDamage) + "의 데미지!";
	monsterTurn = "몬스터의 공격!\n플레이어에게 "
		+ std::to_string(currentLog.MonsterAttackDamage) + "의 데미지!";
	resultText = "남은 체력\n플레이어: " + std::to_string(currentLog.PlayerRemainingHP)
		+ " / 몬스터: " + std::to_string(currentLog.MonsterRemainingHP);

	data.AddLine(playerTurn, LineType::out);
	data.AddLine(monsterTurn, LineType::out);
	data.AddLine(emptyLine, LineType::out);
	data.AddLine(resultText, LineType::out);
	data.AddLine(emptyLine, LineType::out);
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
	screen.AddLine("싸운다. 그리고, 이긴다.", LineType::out);
	screen.AddLine(emptyLine, LineType::out);

	for (std::size_t Index = 0; Index < BattleLogs.size(); ++Index)
	{
		SetBattleLog(BattleLogs[Index], screen, border, emptyLine);
	}

	screen.AddLine(border, LineType::out);
	std::string resultText =
		(Result.first == BattleResult::Win) ?
		"싸웠더니 배가 고프다. 맛있는 거 먹으러 가자." : "나는 아직 네녀석을 요리할 자격이 없나보군...";
	screen.AddLine(resultText, LineType::out);
	screen.AddLine(emptyLine, LineType::out);
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
