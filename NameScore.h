#pragma once
#include <string>

class NameScore
{
public:
	NameScore(std::string name);
	~NameScore();
	//getters 
	const std::string& GetName() const;
	const size_t& GetAlphabeticScore() const;
	//no setters!
private:
	std::string	_name;
	size_t		_alphabeticScore;
	void		ComputeAlphabeticScore();
};