#include "stdafx.h"
#include "NameScore.h"
#include <cctype>

NameScore::NameScore(std::string name): _name(name)
{
	_alphabeticScore = 0;
	ComputeAlphabeticScore();
}

NameScore::~NameScore()
{
}

const std::string & NameScore::GetName() const
{
	return _name;
}

const size_t & NameScore::GetAlphabeticScore() const
{
	return _alphabeticScore;
}

void NameScore::ComputeAlphabeticScore()
{
	for (int i = 0; i < _name.length(); i++)
	{
		_alphabeticScore += std::tolower(_name[i]) - 96; //a in ascii table is 97
	}
}
