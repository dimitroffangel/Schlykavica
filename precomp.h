#pragma once

#include <string>
#include <unordered_map>

using Dictionary = std::unordered_map<std::string, size_t>;
using String = std::string;

const String ALPHABET = "abcdefghijklmnopqrstuvwxyz";

static size_t GetDistance(const String& lhsWord, const String& rhsWord)
{
	if (lhsWord.empty())
	{
		return rhsWord.size();
	}
	if (rhsWord.empty())
	{
		return lhsWord.size();
	}

	std::vector<size_t> previousRow(rhsWord.size() + 1, 0);
	std::vector<size_t> currentRow(rhsWord.size() + 1, 0);

	for (size_t i = 0; i <= rhsWord.size(); ++i)
	{
		previousRow[i] = i;
	}

	for (size_t i = 0; i < lhsWord.size(); ++i)
	{
		currentRow[0] = i + 1;

		for (size_t j = 0; j < rhsWord.size(); ++j)
		{
			// calculating for A[i+1][j+1]
			const size_t deletionCost = previousRow[j + 1] + 1;
			const size_t insertionCost = currentRow[j] + 1;
			const size_t substituionCost = lhsWord[i] == rhsWord[j] ? previousRow[j] : previousRow[j] + 1;

			currentRow[j + 1] = std::min(deletionCost, insertionCost);
			currentRow[j + 1] = std::min(currentRow[j + 1], substituionCost);
		}

		std::swap(previousRow, currentRow);
	}

	return previousRow[rhsWord.size()];
}