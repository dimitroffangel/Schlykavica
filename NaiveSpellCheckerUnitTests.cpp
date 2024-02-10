#include "NaiveSpellCheckerUnitTests.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "Bayes.h"

void NaiveSpellCheckerUnitTests::WordCheck(const String& filePath, const String& wordToCheck, const size_t editDistance, Dictionary& dictionary)
{
	std::ofstream outputFile(filePath, std::ofstream::app);

	Bayes bayes;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	Bayes::Candidate result = bayes.GetMaxCandidate(editDistance, wordToCheck, dictionary);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Naive Checker: " << wordToCheck <<  " Found word: "  << result.m_Word << " For Edit distance: " << result.m_Distance  << " -> Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << '\n';
	outputFile << "Naive Checker: " << wordToCheck << " Found word: " << result.m_Word  << " For Edit distance: " << result.m_Distance << " -> Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << '\n';
}
