#pragma once

#include "precomp.h"

struct NaiveSpellCheckerUnitTests
{
	static void WordCheck(const String& filePath, const String& wordToCheck, const size_t editDistance, Dictionary& dictionary);
};

