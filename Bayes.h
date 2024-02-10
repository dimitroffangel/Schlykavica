#pragma once

#include "precomp.h"
#include <unordered_set>

class Bayes
{
public:

	struct Candidate
	{
		String m_Word;
		size_t m_Counter = 0;
		size_t m_Distance = 1024;
	};

	Candidate GetMaxCandidate(const String& word, Dictionary& dictionary)
	{
		Dictionary editWords;
		editWords[word] = 1;
		Dictionary previousEditDictionary = editWords;
		for (size_t currentDistance = 0; currentDistance < 2; ++currentDistance)
		{
			for (const auto& currentWord : previousEditDictionary)
			{
				GetBaseEdits(currentWord.first, editWords, dictionary);
			}
			
			Candidate candidate;
			for (auto& word : editWords)
			{
				if (candidate.m_Distance >= word.second && dictionary[word.first] > candidate.m_Counter)
				{
					candidate.m_Word = word.first;
					candidate.m_Counter = dictionary[word.first];
					candidate.m_Distance = word.second;
				}
			}

			const auto& foo = editWords["spelling"];
			const auto & foo2 = dictionary["spelling"];
			if (candidate.m_Distance != 1024)
			{
				return candidate;
			}
			previousEditDictionary = editWords;
		}
	}
	
private:
	void GetCandidates(const String& word, Dictionary& candidates, const Dictionary& dictionary) const
	{
		
	}

	void GetEdits(const size_t editDistance, const String& word, Dictionary& editWords, const Dictionary& dictionary) const
	{

	}

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
