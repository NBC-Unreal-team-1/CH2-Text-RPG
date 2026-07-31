#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include "../UI/ConsoleUtils.h"

enum class LineType
{
	out,
	in,
	ceiling,
	wait,
};

class Line
{
public:
	Line(std::string inText, LineType inType);
	std::string GetText();
	void SaveEnds();
	int GetEndX() const;
	int GetEndY() const;
	LineType GetType();

protected:

private:
	std::string text;
	int endX = 0;
	int endY = 0;
	LineType type;
};

class ScreenData
{
public:
	void AddLine(std::string inText, LineType inType);
	int GetDataSize() const;
	void PrintLine(int i);
	void ResetToCeiling();
	bool GetHasInput() const;
	bool CheckIsWait(int i);
	void MoveToInputPos() const;
	void ClearInput() const;

protected:

private:
	std::vector<Line> data;
	int inputLine = -1;
};