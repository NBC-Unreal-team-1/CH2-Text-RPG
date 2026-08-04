#include "UIManager.h"

#include <fstream>
#include <limits>
#include <sstream>

namespace
{
    constexpr int ScreenWidth = 174;
    constexpr int ScreenHeight = 59;
    constexpr int LeftWidth = 136;
    constexpr int TopHeight = 46;

    void WriteAt(int X, int Y, const std::string& Text)
    {
        MoveCursor(X, Y);
        std::cout << Text;
    }

    void WriteWideAt(int X, int Y, const std::wstring& Text)
    {
        MoveCursor(X, Y);
        DWORD Written = 0;
        WriteConsoleW(
            GetStdHandle(STD_OUTPUT_HANDLE),
            Text.c_str(),
            static_cast<DWORD>(Text.size()),
            &Written,
            nullptr
        );
    }

    void ConfigureConsoleWindow()
    {
        static bool IsConfigured = false;
        if (IsConfigured)
        {
            return;
        }

        const HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFOEX FontInfo = {};
        FontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        if (GetCurrentConsoleFontEx(OutputHandle, FALSE, &FontInfo))
        {
            FontInfo.dwFontSize.X = 0;
            FontInfo.dwFontSize.Y = 14;
            SetCurrentConsoleFontEx(OutputHandle, FALSE, &FontInfo);
        }

        CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
        if (!GetConsoleScreenBufferInfo(OutputHandle, &BufferInfo))
        {
            return;
        }

        COORD BufferSize = BufferInfo.dwSize;
        BufferSize.X = static_cast<SHORT>(
            (std::max)(static_cast<int>(BufferSize.X), ScreenWidth + 2)
        );
        BufferSize.Y = static_cast<SHORT>(
            (std::max)(static_cast<int>(BufferSize.Y), ScreenHeight + 2)
        );
        SetConsoleScreenBufferSize(OutputHandle, BufferSize);

        const COORD MaximumWindowSize = GetLargestConsoleWindowSize(OutputHandle);
        const SHORT WindowWidth = MaximumWindowSize.X > 0
            ? (std::min)(static_cast<SHORT>(ScreenWidth), MaximumWindowSize.X)
            : static_cast<SHORT>(ScreenWidth);
        const SHORT WindowHeight = MaximumWindowSize.Y > 0
            ? (std::min)(static_cast<SHORT>(ScreenHeight + 1), MaximumWindowSize.Y)
            : static_cast<SHORT>(ScreenHeight + 1);
        const SMALL_RECT WindowRect = {
            0,
            0,
            static_cast<SHORT>(WindowWidth - 1),
            static_cast<SHORT>(WindowHeight - 1)
        };
        SetConsoleWindowInfo(OutputHandle, TRUE, &WindowRect);
        IsConfigured = true;
    }

    void DrawHorizontal(
        int Y,
        wchar_t Left,
        wchar_t Center,
        wchar_t Right
    )
    {
        std::wstring Line;
        Line += Left;
        Line += std::wstring(LeftWidth - 1, L'━');
        Line += Center;
        Line += std::wstring(ScreenWidth - LeftWidth - 2, L'━');
        Line += Right;

        WriteWideAt(
            0,
            Y,
            Line
        );
    }

    void DrawFrame()
    {
        ConfigureConsoleWindow();

        DrawHorizontal(0, L'┏', L'┳', L'┓');
        DrawHorizontal(TopHeight, L'┣', L'╋', L'┫');
        DrawHorizontal(ScreenHeight, L'┗', L'┻', L'┛');

        for (int Y = 1; Y < ScreenHeight; ++Y)
        {
            WriteWideAt(0, Y, L"┃");
            WriteWideAt(LeftWidth, Y, L"┃");
            WriteWideAt(ScreenWidth - 1, Y, L"┃");
        }
    }

    void WriteBlock(
        int X,
        int Y,
        int MaxRows,
        const std::vector<std::string>& Lines
    )
    {
        int Row = 0;
        for (const std::string& Text : Lines)
        {
            std::stringstream Stream(Text);
            std::string Line;
            while (Row < MaxRows && std::getline(Stream, Line))
            {
                WriteAt(X, Y + Row, Line);
                ++Row;
            }
            if (Row >= MaxRows)
            {
                break;
            }
        }
    }

    std::wstring Utf8ToWide(const std::string& Text)
    {
        if (Text.empty())
        {
            return {};
        }

        const int Length = MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            Text.data(),
            static_cast<int>(Text.size()),
            nullptr,
            0
        );
        if (Length <= 0)
        {
            return std::wstring(Text.begin(), Text.end());
        }

        std::wstring Result(Length, L'\0');
        MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            Text.data(),
            static_cast<int>(Text.size()),
            Result.data(),
            Length
        );
        return Result;
    }

    std::string WideToUtf8(const std::wstring& Text)
    {
        if (Text.empty())
        {
            return {};
        }

        const int Length = WideCharToMultiByte(
            CP_UTF8,
            0,
            Text.data(),
            static_cast<int>(Text.size()),
            nullptr,
            0,
            nullptr,
            nullptr
        );
        std::string Result(Length, '\0');
        WideCharToMultiByte(
            CP_UTF8,
            0,
            Text.data(),
            static_cast<int>(Text.size()),
            Result.data(),
            Length,
            nullptr,
            nullptr
        );
        return Result;
    }

    void WriteArtBlock(
        int X,
        int Y,
        int MaxRows,
        const std::vector<std::string>& Lines,
        int HorizontalOffset = 0
    )
    {
        const int RowCount = (std::min)(MaxRows, static_cast<int>(Lines.size()));
        const int ArtAreaWidth = LeftWidth - X;
        const int StartY = Y + (MaxRows - RowCount) / 2;
        int ArtWidth = 0;
        for (int Row = 0; Row < RowCount; ++Row)
        {
            ArtWidth = (std::max)(
                ArtWidth,
                static_cast<int>(Utf8ToWide(Lines[Row]).size())
            );
        }
        const int StartX = X + (std::max)(0, (ArtAreaWidth - ArtWidth) / 2) +
            HorizontalOffset;

        for (int Row = 0; Row < RowCount; ++Row)
        {
            const std::wstring WideLine = Utf8ToWide(Lines[Row]);
            WriteWideAt(StartX, StartY + Row, WideLine);
        }
    }

    void ClearArtBlock()
    {
        const std::wstring EmptyLine(LeftWidth - 2, L' ');
        for (int Row = 0; Row < TopHeight - 3; ++Row)
        {
            WriteWideAt(2, 2 + Row, EmptyLine);
        }
    }

    void AnimateMonsterHit(const std::vector<std::string>& ArtLines)
    {
        constexpr int HitOffsets[5] = { -5, 4, -3, 2, 0 };
        for (const int Offset : HitOffsets)
        {
            ClearArtBlock();
            WriteArtBlock(2, 2, TopHeight - 3, ArtLines, Offset);
            Sleep(75);
        }
    }

    void AnimateMonsterDefeat(const std::vector<std::string>& ArtLines)
    {
        constexpr int FlashFrameCount = 6;
        for (int Frame = 0; Frame < FlashFrameCount; ++Frame)
        {
            ClearArtBlock();
            if (Frame % 2 == 0)
            {
                WriteArtBlock(2, 2, TopHeight - 3, ArtLines);
            }
            Sleep(120);
        }
        ClearArtBlock();
        Sleep(250);
    }

    std::vector<std::string> LoadArtAsset(const std::string& AssetName)
    {
        const std::vector<std::string> CandidatePaths = {
            "Assets/" + AssetName,
            "CH2-Text-RPG/Assets/" + AssetName,
            "../../Assets/" + AssetName
        };

        std::ifstream File;
        for (const std::string& Path : CandidatePaths)
        {
            File.open(Path, std::ios::binary);
            if (File.is_open())
            {
                break;
            }
            File.clear();
        }

        if (!File.is_open())
        {
            return { "ASCII ART NOT FOUND: " + AssetName };
        }

        std::vector<std::string> Lines;
        std::string Line;
        while (std::getline(File, Line))
        {
            if (!Line.empty() && Line.back() == '\r')
            {
                Line.pop_back();
            }
            Lines.push_back(Line);
        }

        while (!Lines.empty() && Lines.front().empty())
        {
            Lines.erase(Lines.begin());
        }
        while (!Lines.empty() && Lines.back().empty())
        {
            Lines.pop_back();
        }

        std::size_t CommonIndent = std::string::npos;
        for (const std::string& CurrentLine : Lines)
        {
            if (CurrentLine.empty())
            {
                continue;
            }
            CommonIndent = (std::min)(CommonIndent, CurrentLine.find_first_not_of(' '));
        }
        if (CommonIndent != std::string::npos && CommonIndent > 0)
        {
            for (std::string& CurrentLine : Lines)
            {
                CurrentLine.erase(0, (std::min)(CommonIndent, CurrentLine.size()));
            }
        }
        return Lines;
    }

    std::vector<std::string> LoadUiArtAsset(const std::string& AssetName)
    {
        const std::vector<std::string> SourceLines = LoadArtAsset(AssetName);
        if (SourceLines.empty())
        {
            return SourceLines;
        }

        constexpr int TargetWidth = LeftWidth - 2;
        constexpr int TargetHeight = TopHeight - 3;
        std::vector<std::wstring> WideSourceLines;
        int SourceWidth = 0;
        for (const std::string& SourceLine : SourceLines)
        {
            WideSourceLines.push_back(Utf8ToWide(SourceLine));
            SourceWidth = (std::max)(
                SourceWidth,
                static_cast<int>(WideSourceLines.back().size())
            );
        }

        wchar_t Background = L' ';
        for (const wchar_t Character : WideSourceLines.front())
        {
            if (Character != L' ')
            {
                Background = Character;
                break;
            }
        }

        std::vector<std::string> Result;
        Result.reserve(TargetHeight);
        for (int TargetRow = 0; TargetRow < TargetHeight; ++TargetRow)
        {
            int SourceRow = 0;
            if (static_cast<int>(WideSourceLines.size()) > TargetHeight)
            {
                SourceRow = TargetRow * static_cast<int>(WideSourceLines.size()) /
                    TargetHeight;
            }
            else
            {
                const int TopPadding =
                    (TargetHeight - static_cast<int>(WideSourceLines.size())) / 2;
                if (TargetRow < TopPadding ||
                    TargetRow >= TopPadding + static_cast<int>(WideSourceLines.size()))
                {
                    Result.push_back(WideToUtf8(std::wstring(TargetWidth, Background)));
                    continue;
                }
                SourceRow = TargetRow - TopPadding;
            }

            std::wstring Canvas(TargetWidth, Background);
            const std::wstring& SourceLine = WideSourceLines[SourceRow];
            if (SourceWidth <= TargetWidth)
            {
                const int StartX = (TargetWidth - SourceWidth) / 2;
                for (std::size_t Index = 0;
                    Index < SourceLine.size() && StartX + Index < Canvas.size();
                    ++Index)
                {
                    Canvas[StartX + Index] = SourceLine[Index];
                }
            }
            else
            {
                for (int TargetColumn = 0; TargetColumn < TargetWidth; ++TargetColumn)
                {
                    const int SourceColumn = TargetColumn * SourceWidth / TargetWidth;
                    if (SourceColumn < static_cast<int>(SourceLine.size()))
                    {
                        Canvas[TargetColumn] = SourceLine[SourceColumn];
                    }
                }
            }
            Result.push_back(WideToUtf8(Canvas));
        }
        return Result;
    }

    std::vector<std::wstring> ScaleArtToCanvas(
        const std::vector<std::string>& SourceLines,
        int TargetWidth,
        int TargetHeight
    )
    {
        if (SourceLines.empty())
        {
            return std::vector<std::wstring>(
                TargetHeight,
                std::wstring(TargetWidth, L' ')
            );
        }

        std::vector<std::wstring> WideSourceLines;
        int SourceWidth = 0;
        for (const std::string& SourceLine : SourceLines)
        {
            WideSourceLines.push_back(Utf8ToWide(SourceLine));
            SourceWidth = (std::max)(
                SourceWidth,
                static_cast<int>(WideSourceLines.back().size())
            );
        }

        wchar_t Background = L' ';
        for (const wchar_t Character : WideSourceLines.front())
        {
            if (Character != L' ')
            {
                Background = Character;
                break;
            }
        }

        std::vector<std::wstring> Result(
            TargetHeight,
            std::wstring(TargetWidth, Background)
        );
        for (int TargetRow = 0; TargetRow < TargetHeight; ++TargetRow)
        {
            const int SourceRow = TargetRow *
                static_cast<int>(WideSourceLines.size()) / TargetHeight;
            const std::wstring& SourceLine = WideSourceLines[SourceRow];

            for (int TargetColumn = 0; TargetColumn < TargetWidth; ++TargetColumn)
            {
                const int SourceColumn = TargetColumn * SourceWidth / TargetWidth;
                if (SourceColumn < static_cast<int>(SourceLine.size()))
                {
                    Result[TargetRow][TargetColumn] = SourceLine[SourceColumn];
                }
            }
        }
        return Result;
    }

    std::string GetSkillTriggerText(const Skill& CurrentSkill)
    {
        switch (CurrentSkill.GetTriggerType())
        {
        case SkillTriggerType::EveryNthTurn:
            return std::to_string(CurrentSkill.GetTriggerValue()) + "턴마다 자동 사용";
        case SkillTriggerType::PlayerHpBelow:
            return "HP " + std::to_string(CurrentSkill.GetTriggerValue()) +
                "% 이하에서 자동 사용";
        default:
            return "자동 사용";
        }
    }
}

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::PrintTitleSplash() const
{
    constexpr int FullScreenHeight = ScreenHeight + 1;
    const std::vector<std::wstring> TitleArt = ScaleArtToCanvas(
        LoadArtAsset("BurgerQuestMain.txt"),
        ScreenWidth,
        FullScreenHeight
    );

    ClearConsole();
    ConfigureConsoleWindow();
    CONSOLE_CURSOR_INFO CursorInfo;
    const HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleCursorInfo(OutputHandle, &CursorInfo))
    {
        CursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(OutputHandle, &CursorInfo);
    }
    Sleep(5000);

    const DWORD FrameDelay = 3000 / FullScreenHeight;
    const std::wstring EmptyLine(ScreenWidth, L' ');
    for (int FrameLineCount = 1;
        FrameLineCount <= FullScreenHeight;
        ++FrameLineCount)
    {
        for (int Row = 0; Row < FullScreenHeight; ++Row)
        {
            WriteWideAt(0, Row, EmptyLine);
        }

        const int StartY = FullScreenHeight - FrameLineCount;
        for (int Row = 0; Row < FrameLineCount; ++Row)
        {
            WriteWideAt(0, StartY + Row, TitleArt[Row]);
        }
        Sleep(FrameDelay);
    }
    Sleep(1000);

    if (GetConsoleCursorInfo(OutputHandle, &CursorInfo))
    {
        CursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(OutputHandle, &CursorInfo);
    }
}

void UIManager::RenderLayout(
    const std::string& Title,
    const std::vector<std::string>& ArtLines,
    const std::vector<std::string>& Options,
    const std::vector<std::string>& Logs,
    const std::string& Prompt
) const
{
    ClearConsole();
    DrawFrame();

    WriteAt(2, 0, "[ " + Title + " / ART ]");
    WriteAt(LeftWidth + 2, 0, "[ OPTIONS ]");
    WriteAt(2, TopHeight, "[ LOG ]");
    WriteAt(LeftWidth + 2, TopHeight, "[ INPUT ]");

    WriteArtBlock(2, 2, TopHeight - 3, ArtLines);
    WriteBlock(LeftWidth + 2, 2, TopHeight - 3, Options);
    WriteBlock(2, TopHeight + 2, ScreenHeight - TopHeight - 3, Logs);
    WriteBlock(
        LeftWidth + 2,
        TopHeight + 2,
        ScreenHeight - TopHeight - 3,
        { Prompt }
    );

    MoveCursor(LeftWidth + 2, TopHeight + 4);
}

int UIManager::ReadChoice(int Min, int Max) const
{
    while (true)
    {
        MoveCursor(LeftWidth + 2, TopHeight + 4);
        std::cout << "> " << std::string(ScreenWidth - LeftWidth - 6, ' ');
        MoveCursor(LeftWidth + 4, TopHeight + 4);

        std::string Input;
        std::getline(std::cin, Input);

        try
        {
            std::size_t ParsedLength = 0;
            const int Choice = std::stoi(Input, &ParsedLength);
            if (ParsedLength == Input.size() && Choice >= Min && Choice <= Max)
            {
                return Choice;
            }
        }
        catch (const std::exception&)
        {
        }

        WriteAt(
            LeftWidth + 2,
            TopHeight + 6,
            std::to_string(Min) + "~" + std::to_string(Max) +
                " 사이의 숫자를 입력하세요."
        );
    }
}

void UIManager::WaitForContinue(const std::string& Prompt) const
{
    WriteAt(LeftWidth + 2, TopHeight + 4, Prompt);
    MoveCursor(LeftWidth + 2, TopHeight + 6);
    std::string Input;
    std::getline(std::cin, Input);
}

void UIManager::SetupPlayerInfo(Player& player)
{
    RenderLayout(
        "PLAYER SETUP",
        {},
        { "플레이어 생성" },
        { "세계 최고의 햄버거를 만들 여행을 준비합니다." },
        "플레이어 이름을 입력하세요."
    );

    std::string Name;
    std::getline(std::cin, Name);
    player.SetName(Name);
    player.SetMaxHp(30);
    player.SetCurrentHp(30);
    player.SetPower(7);
}

int UIManager::PrintMenu() const
{
    RenderLayout(
        "MAIN MENU",
        LoadUiArtAsset("UI/CampFire.txt"),
        {
            "1. 전투",
            "2. 인벤토리",
            "3. 요리",
            "4. 상점",
            "0. 게임 종료"
        },
        { "세계 최고의 햄버거를 만들기 위한 여정을 선택하세요." },
        "메뉴 번호를 입력하세요."
    );
    return ReadChoice(0, 4);
}

int UIManager::PrintInventory(const Inventory& inventory) const
{
    std::vector<std::string> Options;
    const std::vector<InventorySlot>& Items = inventory.GetItems();
    for (std::size_t Index = 0; Index < Items.size(); ++Index)
    {
        Options.push_back(
            std::to_string(Index + 1) + ". " + Items[Index].ItemPtr->GetName() +
            " (" + std::to_string(Items[Index].Count) + ")"
        );
    }
    Options.push_back("0. 돌아가기");

    RenderLayout(
        "INVENTORY",
        LoadUiArtAsset("UI/Inventory.txt"),
        Options,
        { "보유 중인 아이템과 수량입니다." },
        "확인할 아이템 번호를 입력하세요."
    );
    return ReadChoice(0, static_cast<int>(Items.size()));
}

int UIManager::PrintRecipes(
    const RecipeManager& recipes,
    const Inventory& inventory
) const
{
    std::vector<std::string> Options;
    const std::vector<const Recipe*>& Recipes = recipes.GetAllRecipes();
    for (std::size_t Index = 0; Index < Recipes.size(); ++Index)
    {
        Options.push_back(std::to_string(Index + 1) + ". " + Recipes[Index]->Name);
    }
    Options.push_back("0. 돌아가기");

    RenderLayout(
        "RECIPES",
        LoadUiArtAsset("UI/Cook.txt"),
        Options,
        { "제작할 요리를 선택하세요." },
        "레시피 번호를 입력하세요."
    );
    const int Choice = ReadChoice(0, static_cast<int>(Recipes.size()));
    if (Choice != 0 && PrintSelectedRecipe(Recipes[Choice - 1], inventory) != 1)
    {
        return 0;
    }
    return Choice;
}

int UIManager::PrintSelectedRecipe(
    const Recipe* recipe,
    const Inventory& inventory
) const
{
    std::vector<std::string> Logs = { "[필요 재료]" };
    for (const RecipeIngredient& Ingredient : recipe->Ingredients)
    {
        Logs.push_back(
            Item::GetNameById(Ingredient.ItemId) + " " +
            std::to_string(inventory.GetItemCount(Ingredient.ItemId)) + "/" +
            std::to_string(Ingredient.Count)
        );
    }
    Logs.push_back(
        "효과: HP +" + std::to_string(recipe->HpBonus) +
        ", 공격 +" + std::to_string(recipe->AttackBonus) +
        ", 방어 +" + std::to_string(recipe->DefenseBonus)
    );

    RenderLayout(
        recipe->Name,
        LoadUiArtAsset("UI/Cook.txt"),
        { "1. 제작", "0. 돌아가기" },
        Logs,
        "작업을 선택하세요."
    );
    return ReadChoice(0, 1);
}

void UIManager::PrintInsufficientIngredients() const
{
    RenderLayout(
        "COOKING",
        LoadUiArtAsset("UI/Cook.txt"),
        { "0. 레시피로 돌아가기" },
        { "재료가 부족합니다.", "레시피 선택 화면으로 돌아갑니다." },
        "계속하려면 Enter를 누르세요."
    );
    WaitForContinue();
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
    std::vector<std::string> Logs = {
        "요리 성공! " + RecipeName + "을(를) 즉시 섭취했습니다.",
        "최대 HP +" + std::to_string(HpBonus) + " (" + std::to_string(player.GetMaxHp()) + ")",
        "공격력 +" + std::to_string(AttackBonus) + " (" + std::to_string(player.GetPower()) + ")",
        "방어력 +" + std::to_string(DefenseBonus) + " (" + std::to_string(player.GetDefence()) + ")"
    };
    if (IsNextStageUnlocked)
    {
        Logs.push_back("다음 스테이지가 열렸습니다!");
    }

    RenderLayout(
        "COOKING COMPLETE",
        LoadUiArtAsset("UI/Cook.txt"),
        {},
        Logs,
        "계속하려면 Enter를 누르세요."
    );
    WaitForContinue();
}

int UIManager::PrintShop(const std::vector<ShopItem>& shopItems)
{
    std::vector<std::string> Options;
    for (std::size_t Index = 0; Index < shopItems.size(); ++Index)
    {
        Options.push_back(
            std::to_string(Index + 1) + ". " + Item::GetNameById(shopItems[Index].id) +
            " / " + std::to_string(shopItems[Index].price) + " Gold"
        );
    }
    Options.push_back("0. 돌아가기");

    RenderLayout(
        "SHOP",
        LoadUiArtAsset("UI/Shop.txt"),
        Options,
        { "구매할 아이템을 선택하세요." },
        "상품 번호를 입력하세요."
    );
    const int Choice = ReadChoice(0, static_cast<int>(shopItems.size()));
    if (Choice == 0 || PrintSelectedShopItem(shopItems[Choice - 1]) != 1)
    {
        return 0;
    }
    return shopItems[Choice - 1].id;
}

int UIManager::PrintSelectedShopItem(const ShopItem& shopItem)
{
    RenderLayout(
        "SHOP ITEM",
        LoadUiArtAsset("UI/Shop.txt"),
        { "1. 구매", "0. 돌아가기" },
        {
            "상품: " + Item::GetNameById(shopItem.id),
            "가격: " + std::to_string(shopItem.price) + " Gold"
        },
        "작업을 선택하세요."
    );
    return ReadChoice(0, 1);
}

void UIManager::PrintShopPurchaseResult(bool IsPurchased, const Player& player) const
{
    RenderLayout(
        "SHOP RESULT",
        LoadUiArtAsset("UI/Shop.txt"),
        {},
        {
            IsPurchased ? "구매가 완료되었습니다." : "구매할 수 없습니다. 골드를 확인해주세요.",
            "현재 골드: " + std::to_string(player.GetGold())
        },
        "계속하려면 Enter를 누르세요."
    );
    WaitForContinue();
}

int UIManager::PrintSkillSelection(const Player& player, const Monster& monster) const
{
    const std::vector<Skill>& Skills = player.GetSkills();
    std::vector<std::string> Options = { "0. 스킬 사용 안 함" };
    for (std::size_t Index = 0; Index < Skills.size(); ++Index)
    {
        const Skill& CurrentSkill = Skills[Index];
        Options.push_back(std::to_string(Index + 1) + ". " + CurrentSkill.GetName());
    }

    std::vector<std::string> Logs = {
        "상대: " + monster.GetName(),
        "MP: " + std::to_string(player.GetCurrentMp()) + "/" + std::to_string(player.GetMaxMp())
    };
    for (const Skill& CurrentSkill : Skills)
    {
        Logs.push_back(
            CurrentSkill.GetName() + " / 피해 " + std::to_string(CurrentSkill.GetDamage()) +
            " / MP " + std::to_string(CurrentSkill.GetManaCost()) +
            " / " + GetSkillTriggerText(CurrentSkill)
        );
    }

    RenderLayout(
        "SKILL SELECT",
        LoadUiArtAsset("UI/Skill.txt"),
        Options,
        Logs,
        "사용할 스킬을 선택하세요."
    );
    const int Selection = ReadChoice(0, static_cast<int>(Skills.size()));
    return Selection == 0 ? 0 : Skills[Selection - 1].GetId();
}

void UIManager::PrintBossIntroStory(const Monster& boss) const
{
    RenderLayout(
        "BOSS",
        {},
        {},
        {
            "궁극의 햄버거가 완성되자 주변의 공기가 무겁게 가라앉는다.",
            "어둠 속에서 거대한 그림자가 천천히 다가온다...",
            boss.GetName() + ": \"용케도 햄버거를 완성했군, 일개 요리사여...\"",
            boss.GetName() + ": \"나를 넘어야 마지막 한 조각을 얻을 수 있다!\"",
            "최종 보스, " + boss.GetName() + "가 나타났다!"
        },
        "계속하려면 Enter를 누르세요."
    );
    WaitForContinue();
}

void UIManager::PrintEndingStory() const
{
    const std::vector<std::string> StoryLines = {
        "감자 대왕이 남긴 감자로 최종의 감자튀김을 완성했다.",
        "바삭한 감자튀김을 한 입 베어 물었다.",
        "...",
        "\"무언가 부족하다...\"",
        "다시 한 입을 먹었지만, 허전함은 사라지지 않았다.",
        "\"목이 마르다...\"",
        "멀리서 톡 쏘는 기포 소리가 들려온다...",
        "To be continued..."
    };
    constexpr DWORD StoryDelays[] = {
        1400,
        1400,
        1200,
        1600,
        1400,
        1800,
        1800,
        0
    };

    RenderLayout(
        "ENDING",
        {},
        {},
        {},
        "이야기가 끝날 때까지 기다려주세요."
    );

    for (std::size_t Index = 0; Index < StoryLines.size(); ++Index)
    {
        WriteAt(2, TopHeight + 2 + static_cast<int>(Index), StoryLines[Index]);
        Sleep(StoryDelays[Index]);
    }

    WaitForContinue();
}

int UIManager::PrintBattleLog(
    const std::pair<BattleResult, std::vector<BattleInfo>>& Result
) const
{
    const std::vector<BattleInfo>& BattleLogs = Result.second;
    std::string MonsterName = "MONSTER";
    std::vector<std::string> ArtLines;
    if (!BattleLogs.empty())
    {
        MonsterName = BattleLogs.front().MonsterName;
        ArtLines = LoadArtAsset(
            Monster::GetAsciiArtAssetNameById(BattleLogs.front().MonsterId)
        );
    }

    for (const BattleInfo& Log : BattleLogs)
    {
        RenderLayout(
            "BATTLE - " + MonsterName,
            ArtLines,
            { "자동 전투 진행 중" },
            {
                std::to_string(Log.Turn) + "번째 턴",
                "플레이어 공격: " + std::to_string(Log.PlayerAttackDamage) + " 피해"
            },
            "몬스터를 공격했습니다."
        );
        AnimateMonsterHit(ArtLines);

        RenderLayout(
            "BATTLE - " + MonsterName,
            ArtLines,
            { "자동 전투 진행 중" },
            {
                std::to_string(Log.Turn) + "번째 턴",
                "플레이어 공격: " + std::to_string(Log.PlayerAttackDamage) + " 피해",
                MonsterName + " 공격: " + std::to_string(Log.MonsterAttackDamage) + " 피해",
                "플레이어 HP: " + std::to_string(Log.PlayerRemainingHP),
                MonsterName + " HP: " + std::to_string(Log.MonsterRemainingHP)
            },
            "전투가 자동으로 진행됩니다."
        );
        Sleep(650);
    }

    const bool IsVictory = Result.first == BattleResult::Win;
    if (IsVictory)
    {
        AnimateMonsterDefeat(ArtLines);
    }

    RenderLayout(
        "BATTLE RESULT",
        IsVictory ? std::vector<std::string>() : ArtLines,
        { "0. 계속" },
        {
            Result.first == BattleResult::Win
                ? "승리했습니다. 맛있는 재료를 찾으러 갑니다."
                : "패배했습니다. 아직 요리할 자격이 부족합니다."
        },
        "0을 입력하세요."
    );
    return ReadChoice(0, 0);
}

int UIManager::PrintBattleResult(const Player& player, const Monster& monster) const
{
    std::vector<std::string> Logs = {
        "재료를 손에 넣었습니다.",
        "획득 골드: " + std::to_string(monster.GetDropGold()),
        "총 골드: " + std::to_string(player.GetGold())
    };

    const int IngredientId = monster.GetDropIngredientId();
    const InventorySlot* RewardSlot = player.GetInventory().FindSlot(IngredientId);
    if (RewardSlot != nullptr && RewardSlot->ItemPtr != nullptr)
    {
        Logs.push_back(
            "획득: " + RewardSlot->ItemPtr->GetName() + " " +
            std::to_string(monster.GetDropIngredientAmount()) + "개"
        );
        Logs.push_back(
            "총 보유: " + RewardSlot->ItemPtr->GetName() + " " +
            std::to_string(RewardSlot->Count) + "개"
        );
    }

    RenderLayout("BATTLE REWARD", {}, {}, Logs, "계속하려면 Enter를 누르세요.");
    WaitForContinue();
    return 0;
}
