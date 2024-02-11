#pragma once

#include "precomp.h"
#include <unordered_set>

class Bayes
{
public:

	struct Candidate
	{
		String m_Word = "";
		size_t m_Counter = 0;
		size_t m_Distance = INT_MAX;
	};

	Candidate GetMaxCandidate(const size_t maxEditDistance, const String& word, Dictionary& dictionary)
	{
		if (dictionary[word] > 0)
		{
			return Candidate{ word, dictionary[word], 0 };
		}

		Candidate candidate;
		Dictionary editWords;
		editWords[word] = 1;
		Dictionary previousEditDictionary = editWords;
		for (size_t currentDistance = 0; currentDistance < maxEditDistance; ++currentDistance)
		{
			for (const auto& currentWord : previousEditDictionary)
			{
				GetBaseEdits(currentWord.first, editWords, dictionary);
			}
			
			for (auto& currentWord : editWords)
			{
				if (candidate.m_Distance >= currentWord.second && dictionary[currentWord.first] > candidate.m_Counter)
				{
					candidate.m_Word = currentWord.first;
					candidate.m_Counter = dictionary[currentWord.first];
					candidate.m_Distance = GetDistance(word, currentWord.first);
				}
			}

			if (candidate.m_Distance != INT_MAX)
			{
				return candidate;
			}
			previousEditDictionary = editWords;
		}

		return candidate;
	}
	
private:
	void GetBaseEdits(const String& word, Dictionary& editWords, const Dictionary& dictionary) const
	{
		String currentWord;
		std::unordered_set<String> usedWords;
		
		// inserts
		for (size_t i = 0; i < word.size(); ++i)
		{
			for (const char letter : ALPHABET)
			{
				String currentWord = word;
				currentWord.insert(i, 1, letter);
				if (!usedWords.contains(currentWord))
				{
					editWords[currentWord]++;
					usedWords.insert(currentWord);
				}
			}
		}

		// deletes
		for (size_t i = 0; i < word.size(); ++i)
		{
			currentWord = word;
			currentWord.erase(i, 1);
			if (!usedWords.contains(currentWord))
			{
				editWords[currentWord]++;
				usedWords.insert(currentWord);
			}
		}

		// replacements
		for (size_t i = 0; i < word.size(); ++i)
		{
			for (const char letter : ALPHABET)
			{
				currentWord = word;
				currentWord[i] = letter;
				if (!usedWords.contains(currentWord))
				{
					editWords[currentWord]++;
					usedWords.insert(currentWord);
				}
			}
		}

		for (size_t i = 0; i < word.size() - 1; ++i)
		{
			currentWord = word;
			std::swap(currentWord[i], currentWord[i + 1]);
			if (!usedWords.contains(currentWord))
			{
				editWords[currentWord]++;
			}
		}
	}
};

