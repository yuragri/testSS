#include "stdafx.h"
#include "Parser.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

Parser::Parser()
{
	InitMap();
}

//return 0 if we want to quit and 1 if we want to continue
int Parser::Parse(const std::string & command, ScoreContainer * obj)
{
	//break string on "words"
	std::istringstream iss(command);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
									 std::istream_iterator<std::string>{} };
	switch (_mapCommands[tokens[0]])
	{
	case Requests::cmUndefined:
	{
		throw std::invalid_argument("Wrong request!");
		return 1;
	}
	case Requests::cmQuit:
	{
		return 0;
	}
	case Requests::cmReadFile:
	{
		// we need only 1 argument for read_file command
		if (tokens.size() != 2)
		{
			throw std::invalid_argument("Wrong path to file!");
		}
		obj->ReadNamesFromFile(tokens[1]);
		return 1;
	}
	case Requests::cmNewItem:
	{
		//should be at least 1 name
		if (tokens.size() < 2)
		{
			throw std::invalid_argument("Write a name!");
		}
		for (size_t i = 1; i < tokens.size(); ++i)
		{
			if (!obj->AddName(tokens[i]))
			{
				throw std::invalid_argument("Wrong name!");
			}
		}
		return 1;
	}
	case Requests::cmClear:
	{
		obj->ClearNames();
		return 1;
	}
	case Requests::cmComputeScore:
	{
		obj->GetAllScores();
		return 1;
	}
	case Requests::cmPrintList:
	{
		obj->PrintList();
		return 1;
	}
	case Requests::cmPrintScores:
	{
		obj->PrintScores();
		return 1;
	}
	case Requests::cmHelp:
	{
		PrintHelp();
		return 1;
	}
	}

}

void Parser::InitMap()
{
	//add more Requests
	_mapCommands["q"] = Requests::cmQuit;
	_mapCommands["quit"] = Requests::cmQuit;
	_mapCommands["exit"] = Requests::cmQuit;
	_mapCommands["read_file"] = Requests::cmReadFile;
	_mapCommands["new_name"] = Requests::cmNewItem;
	_mapCommands["print_list"] = Requests::cmPrintList;
	_mapCommands["clear_list"] = Requests::cmClear;
	_mapCommands["compute_score"] = Requests::cmComputeScore;
	_mapCommands["print_scores"] = Requests::cmPrintScores;
	_mapCommands["help"] = Requests::cmHelp;
}

void Parser::PrintHelp()
{
	std::cout << "Available requsts:" << std::endl;
	std::cout << "\"q\" or \"quit\" or \"exit\" to quit the program." << std::endl;
	std::cout << "\"read_file file_name\" to add names from file to the list" << std::endl;
	std::cout << "\"new_name NAME1 NAME2...s\" to add one or more names" << std::endl;
	std::cout << "\"print_list: \" to show list of names" << std::endl;
	std::cout << "\"compute_score\" to show general score" << std::endl;
	std::cout << "\"print_scores\" to show list of names and scores" << std::endl;
	std::cout << "\"clear_list\" to clear the list of names" << std::endl;
	std::cout << "\"help\" to print available requsts" << std::endl;
}
