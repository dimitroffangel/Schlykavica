#pragma once

#include "precomp.h"

#include "BK_Tree.h"

struct BK_Tree_UnitTests
{
	static void CreateBK_Tree(const String& filePath, Dictionary& dictionary, BK_Tree& tree);
	static void WordCheck(const String& filePath, const String& wordToCheck, const BK_Tree& bk_Tree);
};

