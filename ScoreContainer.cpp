#include "stdafx.h"
#include "ScoreContainer.h"
#include "NameScore.h"
#include <algorithm> 
#include <fstream>
#include <iostream>
#include <cctype>

ScoreContainer::ScoreContainer():_computed(false)
{
}

ScoreContainer::~ScoreContainer()
{
}

void ScoreContainer::ReadNamesFromFile(std::string & path)
{
	std::ifstream fin;
	fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fin.open(path);
		std::cout << "Reading file \"" << path << "\"" << std::endl;
		//check if the file is empty
		if (fin.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << "File \"" << path << "\" is empty!" << std::endl;
			fin.close();
			return;
		}
		size_t count = 0;
		std::string name = "";
		while (!fin.eof())
		{
			fin >> name;
			if (AddName(name))
			{
				++count;
			}
		}
		_computed = false;

		std::cout << "Added " << count << " names to the list from the file." << std::endl;
		fin.close();
	}
	catch (const std::ifstream::failure & ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << ex.code() << std::endl;
	}
}

bool ScoreContainer::AddName(std::string name)
{
	//add only names with letters
	if (!IsLetters(name))
	{
		return false;
	}
	_names.push_back(NameScore(name));
	_computed = false;
	return true;
}

// we should re-compute score after every change in vector
void ScoreContainer::ComputeScores()
{
	//compute allScores
	_allScores = 0;
	if (_names.empty())
	{
		return;
	}
	//re-sort names
	AlphabeticSort();
	
	for (size_t i = 0; i < _names.size(); ++i)
	{
		size_t nameScore = _names[i].GetAlphabeticScore();
		nameScore *= i + 1;
		_allScores += nameScore;
	}
	_computed = true;
}

size_t ScoreContainer::GetAllScores()
{
	if (!_computed)
	{
		ComputeScores();
	}
	std::cout << "Score for " << _names.size() << " names: " << _allScores << std::endl;
	return _allScores;
}

void ScoreContainer::PrintScores()
{
	if (!_computed)
	{
		ComputeScores();
	}

	for (size_t i = 0; i < _names.size(); ++i)
	{
		std::cout << _names[i].GetName() << " " << _names[i].GetAlphabeticScore() << "*" << i+1 << "=" << _names[i].GetAlphabeticScore()*(i + 1) << std::endl;
	}
	std::cout << "Score for " << _names.size() << " names: " << _allScores << std::endl;
}

void ScoreContainer::PrintList()
{
	if (!_computed)
	{
		ComputeScores();
	}

	for (size_t i = 0; i < _names.size(); ++i)
	{
		std::cout << _names[i].GetName() << std::endl;
	}
	std::cout << "Total  " << _names.size() << " names." << std::endl;
}

void ScoreContainer::ClearNames()
{
	_computed = false;
	_allScores = 0;
	_names.clear();
	std::cout << "Cleared the list." << std::endl;
}

std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);
	return s;
}

void ScoreContainer::AlphabeticSort()
{
	if (_names.empty())
	{
		return;
	}
	
	std::sort(_names.begin(), _names.end(), [](NameScore& a, NameScore& b)
	{
		return str_tolower(a.GetName()) < str_tolower(b.GetName());
	});
}

bool ScoreContainer::IsLetters(std::string name)
{
	for (int i = 0; i < name.size(); i++)
	{
		int letter = std::tolower(name[i]);
		if (letter < 'a' || letter > 'z')
		{
			return false;
		}
	}
	return true; 
}
