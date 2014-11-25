#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//SimilarVideoRecognizer//TrieNodeContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UT_NodeContainer)
	{
	public:
		
		TEST_METHOD(Test1)
		{
			TrieNodeContainer<int> t;
			for (int i = 0; i <= 40; ++i)
			{
				t.add();
			}
		}

	};
}