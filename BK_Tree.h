#pragma once

#include <algorithm>
#include <memory>
#include <queue>

#include "precomp.h"
#include <cassert>

class BK_Tree
{
public:
	BK_Tree() = default;
	BK_Tree(const String& word, const size_t distance = 0)
		: m_Word(word), m_Distance(distance)
	{

	}

	bool Insert(const String& word)
	{
		if (m_Word == "")
		{
			m_Word = word;
			return true;
		}

		BK_Tree* currentNode = this;
		const size_t distance = GetDistance(m_Word, word);

		if (distance == 0)
		{
			return true;
		}

		auto it = std::find_if(m_SubTrees.begin(), m_SubTrees.end(), [this, distance, &word](const auto& child)
		{
			const size_t currentDistance = GetDistance(child->m_Word, word);
			return currentDistance == distance;
		});

		if (it == m_SubTrees.end())
		{
			m_SubTrees.push_back(std::make_unique<BK_Tree>(word, distance));
			return true;
		}
		else
		{
			(*it)->Insert(word);
			return true;
		}

		assert("This should not be reached" && false);
		return false;
	}

	size_t GetClosestWord(const String& word, String& closestWord) const
	{
		if (m_Word == "")
		{
			return false;
		}

		int minDistance = INT_MAX;
		const BK_Tree* bestNode = nullptr;
		std::queue<const BK_Tree*> nodesToVisit;
		nodesToVisit.push(this);
		while (!nodesToVisit.empty())
		{
			const BK_Tree* currentNode = nodesToVisit.front();
			nodesToVisit.pop();
			const int currentDistance = GetDistance(currentNode->m_Word, word);
			if (currentDistance < minDistance)
			{
				bestNode = currentNode;
				minDistance = currentDistance;
			}

			for (const auto& adjacentNode : currentNode->m_SubTrees)
			{
				if (std::abs(currentDistance - adjacentNode->m_Distance) < minDistance)
				{
					nodesToVisit.push(adjacentNode.get());
				}
			}
		}

		if (minDistance != INT_MAX)
		{
			closestWord = bestNode->m_Word;
			return minDistance;
		}
	}

private:
	size_t GetDistance(const String& lhsWord, const String& rhsWord) const
	{
		if (lhsWord.empty())
		{
			return rhsWord.size();
		}
		if(rhsWord.empty())
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

	std::vector<std::unique_ptr<BK_Tree>> m_SubTrees;
	String m_Word;
	int m_Distance = 0;
};

