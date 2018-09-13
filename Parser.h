#pragma once
#include <map>
#include <string>
#include <vector>
#include "ScoreContainer.h"

enum Requests
{
	cmUndefined,
	cmQuit,
	cmReadFile,
	cmNewItem,
	cmClear,
	cmComputeScore,
	cmPrintList,
	cmPrintScores,
	cmHelp
};
class Parser
{
public:
	Parser();
	~Parser() {};
	int Parse(const std::string& command, ScoreContainer* obj);
	void PrintHelp();
private:
	std::map<std::string, Requests> _mapCommands;
	void InitMap();
};