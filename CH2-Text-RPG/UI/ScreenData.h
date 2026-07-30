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
};

class Line
{
public:
	Line(std::string inText, LineType inType);
	std::string GetText();
	void SaveEndX();
	int GetEndX() const;
protected:

private:
	std::string text;
	LineType type;
	int endX;
};

class ScreenData
{
public:
	void AddLine(std::string inText, LineType inType);
	int GetDataSize() const;
	void PrintLine(int i);
	bool GetHasInput() const;
	void MoveToInputPos() const;

protected:

private:
	std::vector<Line> data;
	int inputLine = -1;
};