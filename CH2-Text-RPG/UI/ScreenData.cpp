#include "../UI/ScreenData.h"

Line::Line(std::string inText, LineType inType)
	:text(inText), type(inType)
{
}

std::string Line::GetText()
{
	return text;
}

void Line::SaveEnds()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	endX = csbi.dwCursorPosition.X;
	endY = csbi.dwCursorPosition.Y;
}

int Line::GetEndX() const
{
	return endX;
}

int Line::GetEndY() const
{
	return endY;
}

LineType Line::GetType()
{
	return type;
}

void ScreenData::AddLine(std::string inText, LineType inType)
{
	Line newLine(inText, inType);
	data.push_back(newLine);
}

int ScreenData::GetDataSize() const
{
	return data.size();
}

void ScreenData::PrintLine(int i)
{
	std::cout << data[i].GetText();
	data[i].SaveEnds();
	if (data[i].GetType() == LineType::in)
	{
		inputLine = i;
		return;
	}
	std::cout << std::endl;
}

void ScreenData::ResetToCeiling()
{
	int resetPos = -1;

	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].GetType() == LineType::ceiling)
		{
			resetPos = i;
			break;
		}
	}

	if (resetPos == -1)
	{
		return;
	}

	ClearConsole();
	for (int i = 0; i <= resetPos; ++i)
	{
		PrintLine(i);
	}
}

bool ScreenData::GetHasInput() const
{
	if (inputLine == -1)
	{
		return false;
	}

	return true;
}

bool ScreenData::CheckIsWait(int i)
{
	if (data[i].GetType() != LineType::wait)
	{
		return false;
	}

	return true;
}

void ScreenData::MoveToInputPos() const
{
	MoveCursor(data[inputLine].GetEndX(), data[inputLine].GetEndY());
}

void ScreenData::ClearInput() const
{
	MoveToInputPos();
	std::cout << ClearToEndOfLine(data[inputLine].GetEndX());
	FlushInput();
	MoveToInputPos();
}