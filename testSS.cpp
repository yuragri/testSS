// testSS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "ScoreContainer.h"
#include "Parser.h"
using namespace std;



int main()
{
	std::unique_ptr<Parser> parser = std::make_unique<Parser>();
	std::unique_ptr<ScoreContainer> score = std::make_unique<ScoreContainer>();
	int res = 1;
	parser->PrintHelp();
	while(res)
	{
		string path;
		cout << "\nEnter request:" << endl;
		std::getline(cin, path);

		try 
		{
			res = parser->Parse(path, score.get());
		}
		catch (const std::invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	}
    return 0;
}

