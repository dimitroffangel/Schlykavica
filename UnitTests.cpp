#include "UnitTests.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "NaiveSpellCheckerUnitTests.h"
#include "BK_Tree_UnitTests.h"


void UnitTests::Test()
{
	Dictionary dictionary;
	ReadFileInput(dictionary);

	TestNaiveSpellChecker(dictionary);
	//TestBK_TreeChecker(dictionary);
}

void UnitTests::ReadFileInput(Dictionary& dictionary)
{
	std::fstream file("./words.txt", std::fstream::in);


	//String word;
	//while (file >> word)
	//{
	//	dictionary[word]++;
	//}
	String line;
	const size_t bufferSize = 1024;
	char buffer[bufferSize];
	String incompleteWord;
	while (!file.eof())
	{
		file.read(buffer, bufferSize);
		std::streamsize bytesRead = file.gcount();

		String chunk{ buffer };

		if (!incompleteWord.empty())
		{
			chunk = incompleteWord + chunk;
		}

		size_t beginingOfWord = 0;
		std::transform(chunk.begin(), chunk.end(), chunk.begin(), [](const char symbol) {return std::tolower(symbol); });
		for (size_t i = 0; i < chunk.size(); ++i)
		{
			if (chunk[i] == ' ')
			{
				String word{ chunk.begin() + beginingOfWord, chunk.begin() + i };
				dictionary[word]++;
			}

			while (i < chunk.size() && chunk[i] == ' ')
			{
				++i;
				beginingOfWord = i;
			}
		}

		size_t lastSpaceIndex = chunk.rfind(' ');
		if (lastSpaceIndex != String::npos)
		{
			incompleteWord = chunk.substr(lastSpaceIndex);
		}
		else if (beginingOfWord < chunk.size())
		{
			String word{ chunk.begin() + beginingOfWord, chunk.end() };
			dictionary[word]++;
		}
	}
}

void UnitTests::TestNaiveSpellChecker(Dictionary& dictionary)
{

	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "speling", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "speking", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "specking", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "speaking", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "kombat", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "futball", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "basketbal", 3, dictionary);
	NaiveSpellCheckerUnitTests::WordCheck("./naive.txt", "fussball", 3, dictionary);
}

void UnitTests::TestBK_TreeChecker(Dictionary& dictionary)
{
	BK_Tree tree;
	BK_Tree_UnitTests::CreateBK_Tree("/bk_tree.txt.", dictionary, tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "speling", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "speking", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "specking", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "speaking", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "kombat", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "futball", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "basketbal", tree);
	BK_Tree_UnitTests::WordCheck("./bk_tree.txt", "fussball", tree);
}
