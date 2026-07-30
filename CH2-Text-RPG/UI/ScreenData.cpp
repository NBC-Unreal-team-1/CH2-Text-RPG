#include "../UI/ScreenData.h"

Line::Line(std::string inText, LineType inType)
	:text(inText), type(inType)
{
}

std::string Line::GetText()
{
	return text;
}

void Line::SaveEndX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	endX = csbi.dwSize.X;
}

int Line::GetEndX() const
{
	return endX;
}

void ScreenData::AddLine(std::string inText, LineType inType)
{
	Line newLine(inText, inType);
	data.push_back(newLine);
	if (inType == LineType::in)
	{
		inputLine = data.size() - 1;
	}
}

int ScreenData::GetDataSize() const
{
	return data.size();
}

void ScreenData::PrintLine(int i)
{
	std::cout << data[i].GetText();
	data[i].SaveEndX();
	std::cout << std::endl;
}

bool ScreenData::GetHasInput() const
{
	if (inputLine == -1)
	{
		return false;
	}

	return true;
}

void ScreenData::MoveToInputPos() const
{
	MoveCursor(data[inputLine].GetEndX(), data.size() - 1);
}
