#pragma once

#include "precomp.h"

struct UnitTests
{
public:
	static void Test();

private:
	static void ReadFileInput(Dictionary& dictionary);
	static void TestNaiveSpellChecker(Dictionary& dictionary);
	static void TestBK_TreeChecker(Dictionary& dictionary);
};

