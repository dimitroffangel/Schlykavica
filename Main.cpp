#include <iostream>
#include <fstream>

#include "precomp.h"
#include "Bayes.h"

int main()
{
	std::fstream file("./words.txt", std::fstream::in);
	
	Dictionary dictionary;
	String line;
	const size_t bufferSize = 1024;
	char buffer[bufferSize];
	String incompleteWord;
	while (!file.eof())
	{
		file.read(buffer, bufferSize);
		std::streamsize bytesRead = file.gcount();

		String chunk{ buffer};
		if (!incompleteWord.empty())
		{
			chunk = incompleteWord + chunk;
		}

		size_t beginingOfWord = 0;
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
		if (lastSpaceIndex!= String::npos)
		{
			incompleteWord = chunk.substr(lastSpaceIndex);
		}
		else if (beginingOfWord < chunk.size())
		{
			String word{ chunk.begin() + beginingOfWord, chunk.end()};
			dictionary[word]++;
		}
	}

	Bayes bayes;

	while (true)
	{
		String word;
		std::cin >> word;
		auto candidate = bayes.GetMaxCandidate(word, dictionary);
		std::cout << candidate.m_Word << " it is found: " << candidate.m_Counter << '\n';
	}

	return 0;
}