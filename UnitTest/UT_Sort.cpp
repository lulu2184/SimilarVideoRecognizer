#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//SimilarVideoRecognizer//EigenvectorExtracterForImage.h"

#include <vector>
#include <fstream>
#include <opencv2\\core\\core.hpp>
#include <opencv2\\highgui\highgui.hpp>
#include <opencv2\\imgproc\\imgproc.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace cv;


namespace UnitTest
{
	TEST_CLASS(UnitTest_CSort)
	{
	public:
		TEST_METHOD(TestMethod_CSort_Sort_Normal)
		{
			std::vector<int> UnorderNumbers = { 2, 5, 3, 0, 2, 3, 0, 3 };
			std::vector<int> expectedLabel = { 2, 7, 4, 0, 3, 5, 1, 6 };
			std::vector<int> &realLabel = UnorderNumbers;
			EigenvectorExtracterForImage::TransIntoOrdinal(UnorderNumbers);
			Assert::IsTrue(realLabel.size() == expectedLabel.size());
			Assert::IsTrue(std::equal(realLabel.begin(), realLabel.end(), expectedLabel.begin()));
		}

		TEST_METHOD(TestMethod_CSort_Sort_All_Zero)
		{
			std::vector<int> UnorderNumbers = { 0, 0, 0, 0, 0, 0, 0, 0 };
			std::vector<int> expectedLabel = { 0, 1, 2, 3, 4, 5, 6, 7 };
			std::vector<int> &realLabel = UnorderNumbers;
			EigenvectorExtracterForImage::TransIntoOrdinal(UnorderNumbers);
			Assert::IsTrue(realLabel.size() == expectedLabel.size());
			Assert::IsTrue(std::equal(realLabel.begin(), realLabel.end(), expectedLabel.begin()));
		}

		TEST_METHOD(TestMethod_CSort_Sort_All_MaxValue)
		{
			std::vector<int> vec = { 255, 255, 255, 255, 255, 255, 255, 255 };
			std::vector<int> expectedLabel = { 0, 1, 2, 3, 4, 5, 6, 7 };
			EigenvectorExtracterForImage::TransIntoOrdinal(vec);
			Assert::IsTrue(vec.size() == expectedLabel.size());
			Assert::IsTrue(std::equal(vec.begin(), vec.end(), expectedLabel.begin()));
		}

		TEST_METHOD(TestMethod_CSort_Sort_One_Elem)
		{
			std::vector<int> vec = { 1 };
			std::vector<int> expectedLabel = { 0 };
			EigenvectorExtracterForImage::TransIntoOrdinal(vec);
			Assert::IsTrue(vec.size() == expectedLabel.size());
			Assert::IsTrue(std::equal(vec.begin(), vec.end(), expectedLabel.begin()));
		}

		TEST_METHOD(TestMethod_CSort_Sort_Empty)
		{
			std::vector<int> vec = {};
			std::vector<int> expectedLabel = {};
			EigenvectorExtracterForImage::TransIntoOrdinal(vec);
			Assert::IsTrue(vec.size() == expectedLabel.size());
			Assert::IsTrue(std::equal(vec.begin(), vec.end(), expectedLabel.begin()));
		}

	};
}