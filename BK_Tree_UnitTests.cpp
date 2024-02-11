#include "BK_Tree_UnitTests.h"

#include <chrono>
#include <fstream>
#include <iostream>

void BK_Tree_UnitTests::CreateBK_Tree(const String& filePath, Dictionary& dictionary, BK_Tree& tree)
{
	std::ofstream outputFile(filePath, std::ofstream::app);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	tree.Insert("fury");
	
	for (const auto& word : dictionary)
	{
		tree.Insert(word.first);
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	outputFile << "Created tree for " << "->Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << '\n';

}

void BK_Tree_UnitTests::WordCheck(const String& filePath, const String& wordToCheck, const BK_Tree& bk_Tree)
{
	std::ofstream outputFile(filePath, std::ofstream::app);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	String result;
	const size_t distance = bk_Tree.GetClosestWord(wordToCheck, result);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "BK_Tree Checker: " << wordToCheck << " Found word: " << result << " For Edit distance: " << distance << " -> Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << '\n';
	outputFile << "BK_Tree Checker: " << wordToCheck << " Found word: " << result << " For Edit distance: " << distance << " -> Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << '\n';

}
