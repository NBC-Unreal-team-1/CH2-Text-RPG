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
	int menuMax = 1;
	ScreenData menu;
	menu.AddLine(border, LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("1: 여행을 떠나요 즐거운 마음으로 황금빛 태양 축제를 여는~", LineType::out);
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
		menu.AddLine("??", LineType::out);
	}
	menu.AddLine("0 : exit", LineType::out);
	menu.AddLine(emptyLine, LineType::out);
	menu.AddLine("Enter : ", LineType::in);
	menuMax = menu.GetDataSize();

	ClearConsole();
	for (int i = 0; i < menu.GetDataSize(); ++i)
	{
		menu.PrintLine(i);
	}
	std::cout << inventory.GetItems().size() << "라니" << std::endl;

	if (!menu.GetHasInput())
	{
		return -1;
	}

	return GetInput(menu, menuMin, menuMax);
}

void UIManager::PrintBattleLog(
	const std::pair<BattleResult, std::vector<BattleInfo>>& Result
) const
{
	const std::vector<BattleInfo>& BattleLogs = Result.second;

	for (std::size_t Index = 0; Index < BattleLogs.size(); ++Index)
	{
		const BattleInfo& CurrentLog = BattleLogs[Index];

		std::cout << "Turn " << Index + 1 << '\n';
		std::cout << "  Player Damage: "
			<< CurrentLog.PlayerAttackDamage << '\n';
		std::cout << "  Monster Damage: "
			<< CurrentLog.MonsterAttackDamage << '\n';
		std::cout << "  Player HP: "
			<< CurrentLog.PlayerRemainingHP << '\n';
		std::cout << "  Monster HP: "
			<< CurrentLog.MonsterRemainingHP << '\n';
		WaitOutputDelay();
	}

	std::cout << '\n';
	std::cout << "Battle Result: "
		<< (Result.first == BattleResult::Win ? "Win" : "Lose")
		<< '\n';
}
