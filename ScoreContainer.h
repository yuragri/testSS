#pragma once
#include <vector>
#include <string>
#include "NameScore.h"

class ScoreContainer
{
public:
	ScoreContainer();
	~ScoreContainer();
	void ReadNamesFromFile(std::string & path);
	bool AddName(std::string name);
	void ComputeScores();
	size_t GetAllScores();
	void PrintScores();
	void PrintList();
	void ClearNames();
private:
	//container for names
	std::vector<NameScore>		_names;
	//general score
	size_t						_allScores;
	//flag for compute: false, if need to re-compute scores
	bool						_computed;
	//sort the vector of names;
	void AlphabeticSort();
	bool IsLetters(std::string name);
};