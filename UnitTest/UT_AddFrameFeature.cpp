#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\\SimilarVideoRecognizer\\LayerOfEigenvector.h"
#include "..\\SimilarVideoRecognizer\\EigenvectorExtracterForImage.h"
#include "..\\SimilarVideoRecognizer\\OSIDGenerater.h"

#include <fstream>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//#pragma comment(lib, "..\\x64\\Debug\\CBVDLib.lib")

namespace UnitTest
{
	TEST_CLASS(UT_AddFrameFeature)
	{
	public:
		TEST_METHOD(FrameFeatureExtract_Black_Image)
		{
			//BuilderConfig builderConfig = CBuilderConfigLoader().Load("E:\\Chimera\\VideoDuplicateDetection\\UnitTest\\config.txt");
			//CFrameFeatureExtractor frameFeatureExtractor(builderConfig.cfgFrameFeatureExtract);
			Mat image = imread("D:\\programming\\TEST\\black.jpg");
			//cvtColor(image, image, CV_BGR2GRAY);
			//resize(image, image, Size(198, 198));
			//CFrameFeature frameFeature = frameFeatureExtractor.Extract(image);
			vector<double> frameFeature = EigenvectorExtracterForImage::GetEigenvector(image);
			vector<double> expectedFeature =
			{ 1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1 };
			Assert::IsTrue(frameFeature.size() == expectedFeature.size());
			Assert::IsTrue(std::equal(frameFeature.begin(), frameFeature.end(), expectedFeature.begin()));
		}

		TEST_METHOD(FrameFeatureExtract_White_Image)
		{
		//	BuilderConfig builderConfig = CBuilderConfigLoader().Load("E:\\Chimera\\VideoDuplicateDetection\\UnitTest\\config.txt");
		//	CFrameFeatureExtractor frameFeatureExtractor(builderConfig.cfgFrameFeatureExtract);
			Mat image = imread("D:\\programming\\TEST\\white.jpg");
			vector<double> frameFeature = EigenvectorExtracterForImage::GetEigenvector(image);
			//cvtColor(image, image, CV_BGR2GRAY);
			//resize(image, image, Size(198, 198));
			//CFrameFeature frameFeature = frameFeatureExtractor.Extract(image);
			vector<double> expectedFeature =
			{ 1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1 };
			Assert::IsTrue(frameFeature.size() == expectedFeature.size());
			Assert::IsTrue(std::equal(frameFeature.begin(), frameFeature.end(), expectedFeature.begin()));
		}

		TEST_METHOD(LayerCalculate_AllSameVector)
		{
			vector<double> singleFeature =
			{ 1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1 };
			vector<vector<double>> origin;
			for (int i = 0; i < 300; ++i)
			{
				origin.push_back(singleFeature);
			}
			vector<vector<double>> expected;
			for (int i = 0; i < 59; ++i)
			{
				expected.push_back(singleFeature);
			}
			LayerOfEigenvector originlayer(origin);
			LayerOfEigenvector feature = originlayer.GetLayer(10);
			vector<vector<double>> vec = feature.ExportVector();
			Assert::IsTrue(vec.size() == expected.size());
			for (auto it1 = vec.cbegin(), it2 = expected.cbegin(); it1 != vec.cend(); ++it1, ++it2)
			{
				Assert::IsTrue(it1->size() == it2->size());
				Assert::IsTrue(std::equal(it1->begin(), it1->end(), it2->begin()));
			}
		}

		TEST_METHOD(LayerCalculate_Increasing)
		{
			vector<vector<double>> origin;
			for (int i = 0; i < 300; ++i)
			{
				vector<double> singleFeature(27, i);
				origin.push_back(singleFeature);
			}
			vector<vector<double>> expected;
			for (int i = 0; i < 59; ++i)
			{
				vector<double> singleFeature(27, (i + 1) * 5 - 0.5);
				expected.push_back(singleFeature);
			}
			LayerOfEigenvector originlayer(origin);
			LayerOfEigenvector feature = originlayer.GetLayer(10);
			vector<vector<double>> vec = feature.ExportVector();
			Assert::IsTrue(vec.size() == expected.size());
			for (auto it1 = vec.cbegin(), it2 = expected.cbegin(); it1 != vec.cend(); ++it1, ++it2)
			{
				Assert::IsTrue(it1->size() == it2->size());
				Assert::IsTrue(std::equal(it1->begin(), it1->end(), it2->begin()));
			}
		}
		
	};
}